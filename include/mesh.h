// Class Mesh
//
//
// Authors: Alberto Manzano Herrero
// ATTRIBUTES:
// 	Nnodes: numer of points stored
// 	Nfinel: number of finite elements stored
// 	Lnode: list of stored points
// 	Lfinel: list of stored finite elements
// 	matriz_global: matrix A
// 	vector_global: vector b
//
// PUBLIC FUNCTIONS:
//
//	SPECIAL MEMBER FUNCTIONS
//		Mfinel: default constructor
//
//	CLASS FUNCTIONS
//		fill_mesh: fills the mesh by reading data from a list of points,
//			   a list of finite elements and a list of boundary nodes
//		print_nodes: print stored nodes
//		print_elements: prints the finite elements stored
//		boundary_conditions: inserts the boundary conditions into matrix A
//		solve: solves the linear system Ax = b 
//		construye_matriz_global: fills both A and b


#include"header.h"
#include <list>
#include <vector>
#include "point.h"
#include "qelfin.h" // Si quisiesemos usar Q1
#include "pelfin.h"
#include "dato.h"

using namespace std;
using namespace Eigen;

class dato;

template < typename T >
class Mfinel{


public :
    // ATTRIBUTES
    friend class dato;
    static int Nnodes;  
    static int Nfinel; 
    vector<point*> Lnode; 
    list<T> Lfinel; 
    MatrixXd matriz_global;
    VectorXd vector_global;
    
    // SPECIAL MEMBER FUNCTIONS
    Mfinel(); 
    
    // CLASS FUNCTIONS
    void fill_mesh(dato& datos); 
    void print_nodes();
    void print_elements(); 
    void solve();
    void boundary_conditions();
    void construye_matriz_global();  	
};


// SPECIAL MEMBER FUNCTIONS
template < typename T >
Mfinel<T>::Mfinel(){
  vector<point*> Lnode;
}


/*
 * Definicion de miebros estaticos
 */
template <typename T> int Mfinel<T>::Nnodes;  
template <typename T> int Mfinel<T>::Nfinel;

/*
 * Un metodo que rellena la malla a partir de datos provenientes
 * de un fichero generado por un mallador o a partir de nuestro propio código de mallado
 * 
 * El nombre de fichero debería estar almacenado en una estructura datos del problema
 * 
 * 
 */

// FUNCTIONS
template < typename T >
void Mfinel<T>::fill_mesh(dato& datos){
  // Rellenamos lista de nodos
  this->Nnodes=0;
  ifstream myfile (datos.mallado.nodos.c_str()); 
  while (myfile.good())
  {
       point *node=new point(); // creo nuevo nodo
       myfile>>node->x>>node->y; // leo datos del mallado
       if (!node->y) break;
       this->Nnodes++;       // incrementamos el numero de nodos
       this->Lnode.push_back(node); // insertamos nodo en lista-nodos
  }
  myfile.close();
  
  // Rellenamos la lista de elementos
  this->Nfinel=0;
  myfile.open("mesh/mesh_tnode.dat"); 
  bool control = 0;
  if (myfile.is_open()){
	while ( myfile.good() ){
		T Elmt=T();  // creamos nuevo elemento temporali
		for(int k=0;k<Elmt.N;k++){ // Leemos conectividades
			int conect;
			myfile>>conect;
			if (myfile.eof()){
				control = 1;
				break;
			}
			Elmt.V[k]=this->Lnode[conect-1]; // asigno REFERENCIA al punto correspondiente
			this->Nfinel++;
		}
		if (control==1) break;
		this->Lfinel.emplace_back(Elmt); // insertamos el elemento en la lista de elementos
	}
	myfile.close();
  }
 
  myfile.open("mesh/mesh_bnd_node.dat"); 
  int front = 0;
  if (myfile.is_open()){
	while (true){
		myfile>>front;
		if (myfile.eof()) break;
		this->Lnode[front-1]->front = 1;
		
	}
	myfile.close();
  }
  
}


// Impresion de lista de nodos de la malla
template < typename T >
void Mfinel<T>::print_nodes(){
   vector<point*>::iterator it; // iterator de lista de nodos
   for(it=this->Lnode.begin(); it != this->Lnode.end(); ++it){        
       (*it)->print_point(); // alternativamente  (*(*it)).print_points();
   }
   
}


// Impresion de lista de nodos de la malla
template < typename T >
void Mfinel<T>::print_elements(){
   cout<<"Imprimimos los elementos del mallado"<<endl;
   int i=0;
   typename list<T>::iterator it; // cuidado con el typename- si no lo ponemos no se entera en el iterador
   for(it=this->Lfinel.begin(); it != this->Lfinel.end(); ++it){  
       cout<<"ELEMENTO "<<i<<endl;
       it->print_finel(); // alternativamente  (*(*it)).print_points();
       i++;
   }
   
}
template <typename T>
void Mfinel<T>::construye_matriz_global(){
   int i=0;

   Matrix3d m;
   Vector3d v;

   matriz_global.resize(this->Nnodes,this->Nnodes);
   matriz_global.setZero();
   vector_global.resize(this->Nnodes);
   vector_global.setZero();

   // guardar puntos medios 
   point *p = new point[3];
   typename list<P1>::iterator it;
   for(it=this->Lfinel.begin(); it !=this->Lfinel.end(); ++it){  
       it->calcula_matriz_local(p,m);
       it->calcula_vector_local(p,v,f); 
       it->asigna_matriz_global(m,matriz_global);
       it->asigna_vector_global(v,vector_global);
       i++;
   }
}

template <typename T>
void Mfinel<T>::boundary_conditions(){
	for (int i=0;i<this->Nnodes;i++){
		if (this->Lnode[i]->front == 1){
			this->vector_global[i]=0;
			this->matriz_global.row(i).setZero();
			this->matriz_global(i,i) = 1;
		}
	}
}
template < typename T >
void Mfinel<T>::solve(){ 

   VectorXd x = (this->matriz_global.fullPivLu()).solve(this->vector_global);
   double relative_error = (this->matriz_global*x-this->vector_global).norm()/this->vector_global.norm();
   for (int i=0;i<this->Nnodes;i++) this->Lnode[i]->sol = x[i];
    
   ofstream outfile;
   outfile.open("prueba.txt");
   if (outfile.is_open()){
   for (int i = 0;i<this->Nnodes;i++)
   	outfile<<this->Lnode[i]->x<<" "<<this->Lnode[i]->y<<" "<<this->Lnode[i]->sol<<endl;
   }else{
	cout<<"Ha habido un problema"<<endl;
   }
}

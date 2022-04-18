#include "point.h"
#include "pelfin.h"
#include "math.h"

// SPECIAL MEMBER FUNCTIONS 
P1::P1(){    
 this->N=3;
 this->V=new point*[3];
 this->area=0; 
}

P1::P1(const P1 &triangulo){
	this->N = triangulo.N;
	this->V=new point*[3];
	this->V[0] = triangulo.V[0];
	this->V[1] = triangulo.V[1];
	this->V[2] = triangulo.V[2];
	this->calcula_area();
}

void P1::operator=(const P1 &triangulo){
	this->V[0] = triangulo.V[0];
	this->V[1] = triangulo.V[1];
	this->V[2] = triangulo.V[2];
	this->area = triangulo.area;
}

P1::~P1(){
	delete[] this->V;
}

// PRIVATE FUNCTIONS
void P1::calcula_area(){
	double det;
	det = determinante(*(this->V[0]),*(this->V[1]),*(this->V[2]));
	this->area = 0.5*det;
}

// CLASS FUNCTIONS
void P1::print_finel(){
    cout<<"---------------"<<endl;
    for (int k=0;k<(this->N);k++){
        this->V[k]->print_point();
    }
    cout<<"Area: "<<this->area<<endl;
    cout<<"---------------"<<endl;
}

void P1::calcula_gradientes(point* &p){
	p[0].x = -(this->V[2]->y-this->V[1]->y)/(2*this->area);
	p[0].y = (this->V[2]->x-this->V[1]->x)/(2*this->area);
	p[0].ind = this->V[0]->ind;

	p[1].x = -(this->V[0]->y-this->V[2]->y)/(2*this->area);
	p[1].y = (this->V[0]->x-this->V[2]->x)/(2*this->area);
	p[1].ind = this->V[1]->ind;

	p[2].x = -(this->V[1]->y-this->V[0]->y)/(2*this->area);
	p[2].y = (this->V[1]->x-this->V[0]->x)/(2*this->area);
	p[2].ind = this->V[2]->ind;
}



void P1::calcula_puntos_medios(point* &p){
	p[0].calcula_punto_medio(*(this->V[0]),*(this->V[1]));
	p[1].calcula_punto_medio(*(this->V[0]),*(this->V[2]));
	p[2].calcula_punto_medio(*(this->V[1]),*(this->V[2]));
}

void P1::calcula_vector_local(point* &p,Vector3d &v, double (*f)(const point&)){
	
	this->calcula_puntos_medios(p);
	v.setZero();

	for (int i=0;i<3;i++){
		v[0]+=f(p[i])*determinante(p[i],*(this->V[1]),*(this->V[2]))/(2*this->area);
	}
	v[0]*=abs(this->area)/3;
	
	for (int i=0;i<3;i++){
		v[1]+=f(p[i])*determinante(p[i],*(this->V[2]),*(this->V[0]))/(2*this->area);
	}
	v[1]*=abs(this->area)/3;
	
	for (int i=0;i<3;i++){
		v[2]+=f(p[i])*determinante(p[i],*(this->V[0]),*(this->V[1]))/(2*this->area);
	}
	v[2]*=abs(this->area)/3;
}

void P1::calcula_matriz_local(point* &p,Matrix3d &m){
	this->calcula_gradientes(p);
	for(int i=0;i<3;i++){
		for (int j=0;j<3;j++){
			m(i,j) = abs(this->area)*(p[i].producto_escalar(p[j]));
		}	
	}
}

void P1::asigna_vector_global(Vector3d &v,VectorXd &vector_global){
	for (int i = 0;i<3;i++){
		vector_global(this->V[i]->ind-1)+=v(i);
	}
}

void P1::asigna_matriz_global(Matrix3d &m,MatrixXd &matriz_global){
	for(int i=0;i<3;i++){
		for (int j=0;j<3;j++){
			matriz_global(this->V[i]->ind-1,this->V[j]->ind-1) += m(i,j);
		}	
	}
}


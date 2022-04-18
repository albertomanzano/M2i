// Class P1
//
//
// Authors: Alberto Manzano Herrero
// ATTRIBUTES:
//	N: number of points of the finite element
//	V: pointer to array of pointers storing the direction of the points
//	area: area of the given triangle
// 
// PRIVATE FUNCTIONS:
// 	calcula_area: calcula el area de un triangulo
//
// PUBLIC FUNCTIONS:
//	
//	SPECIAL MEMBER FUNCTIONS
//		P1: default constructor
//		P1: copy constructor
//		~P1: destructor
//
//	CLASS FUNCTIONS
//		print_finel: prints the points (using print_point) of the triangle
//		calcula_puntos_medios: used to compute the integral of matrix A 
//		calcula_gradientes: used to 
//
//		calcula_matriz_local: computes the contribution of the finite element
//			      to the global matrix A
//		calcula_vector_local: computes the contribution of the finite element
//			      to the vector b 
//		asigna_matriz_local: adds the computation performed by calcula_matriz_local
//			     to the global matrix
//		asigna_vector_local: adds the computation performed by calcula_vector_local
//			     to the global vector b
//			       


#include <Eigen/Dense>
using Eigen::Matrix3d;
using Eigen::MatrixXd;
using Eigen::Vector3d;
using Eigen::VectorXd;

#ifndef __P1_
#define __P1_

class P1{
	private:
	// PRIVATE FUNCTIONS
		void calcula_area();
   	public:
	// ATTRIBUTES
	    int N;
        point** V;
	double area;
        
	// SPECIAL MEMBER FUNCTIONS
	P1();
	P1(const P1 &triangulo);
	void operator=(const P1 &triangulo);
	~P1();

	// CLASS FUNCTIONS
        void print_finel();

	void calcula_puntos_medios(point* &p);
	void calcula_gradientes(point* &p);

	void calcula_vector_local(point* &p,Vector3d &v,double (*funcion)(const point&));
	void calcula_matriz_local(point* &p,Matrix3d &m);
	void asigna_vector_global(Vector3d &v,VectorXd &vector_global);
	void asigna_matriz_global(Matrix3d &m,MatrixXd &matriz_global);
};

#endif

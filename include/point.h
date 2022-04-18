// Class point
//
//
// Authors: Alberto Manzano Herrero
// ATTRIBUTES:
// 	x: first coordinate
// 	y: second coordinate
// 	ind: index of given point
// 	front: 1 if edge 0 otherwise
//	sol: stores the solution in (x,y)
// 
// PUBLIC FUNCTIONS:
// 	SPECIAL MEMBER FUNCTIONS
//	 	point: constructor of the class
//		point: copy constructor
//		operator+: sums two points
//
//	CLASS FUNCTIONS
//		print_point: prints the coordinates of the given point and it's global index
// 		calcula_punto_medio: computes the midpoint of the two given points
// 		producto_escalar: computes the scalar product of the two given points
// 	
//	FUNCTIONS
// 		determinante: computes the determinant of the three given  points
//		f: is the right side function of the PDE



#ifndef __POINT_
#define __POINT_

#include <iostream>
using namespace std;
extern int  puntos_creados;

class point{
    public:
	// ATTRIBUTES  
        double x;
        double y;
        int ind;
	int front;
	double sol;

	// SPECIAL MEMBER FUNCTIONS	
	point();
	point(double x,double y);
	point operator+(point const &punto);	

	// CLASS FUNCTIONS
	void print_point();
	double producto_escalar(point &punto2);
	void calcula_punto_medio(const point &punto1,const point &punto2);
};

// FUNCTIONS
double determinante(const point &p1,const point &p2,const point &p3);
double f(const point &p);

#endif

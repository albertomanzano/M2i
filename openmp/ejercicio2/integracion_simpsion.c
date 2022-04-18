

/*********************************************************************
* ejercicio2.c -- Integracion simpson
*
* DESCRIPCION: calcula la integral de una funcion entre los 
*intervalos a,b usando la regla de simpson compuesta 
*
* AUTOR: Alberto P Manzano Herrero, alberto.manzano.herrero@gmail.es
* FECHA: 23/01/2020
*
* INPUT: ninguno
* OUTPUT: integral
*
* FUNCIONES:
*simpson: calcula la integral de funcion hardcoded
*f: funcion de la que se calcula la integral
/**********************************************************************/

#include<stdio.h>
#include "omp.h"


void main(){
/*Calculates the integral of a hardcoded function*/

    double a; /*Left endpoint of the integral*/
    double b; /*Right endpoint of the integral*/
    long int n; /*Number of points*/

    double h; /*base length*/
    double integral; /*value of the integral for my process*/

    double simpson(double a,double b, long int n);

    b = 10;
    a = 0;
    n = 1000000000; //Enough to see the difference

    integral = simpson(a,b,n);
    printf("Total %lf\n",integral);

}
/****************************************************************************/
double simpson(  double a,//Left endpoint of the integral
		 double b,//Right endpoint of the integral
		 long int n//Number of points
		 ){
double integral;//value of the integral
double h = (b-a)/n;//simpson base length

double f(double x);//function
#pragma omp parallel 
{
double x;
long int i;
#pragma omp for reduction(+:integral)//even calculation for simpson rule
    for (i=1;i<(n/2-1);i++){
	x = a+2*i*h;
	integral += 2*f(x);
	}
#pragma omp for reduction(+:integral)//odd calculation for simpson rule
    for (i=1;i<(n/2);i++){
	x = a+(2*i-1)*h;
	integral += 4*f(x);
	}
}
    integral =(integral+f(a)+f(b))*h/3;//final calculation
    return integral;
}



double f(double x){
	double result;
	result = x*x*x*x*x;
	return result;

}


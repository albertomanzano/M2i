
/*********************************************************************
* ejercicio7.c -- Producto de wallis
*
* DESCRIPCION: calcula pi haciendo el producto de wallis
*
* AUTOR: Alberto P Manzano Herrero, alberto.manzano.herrero@gmail.es
* FECHA: 23/01/2020
*
*
* INPUT: ninguno
* OUTPUT: valor de pi
*
* FUNCIONES:
* Wallis: calcula un termino del producto de wallis.
/**********************************************************************/


#include <stdio.h>
#include "omp.h"

void main(){
long int n;//number of iterations
double pi;//value of pi

double wallis(long int n);

n = 1000000000;// long enough to see the difference when scaling

pi = wallis(n);
printf("pi: %lf\n",pi);

}

double wallis(long int n//number of iterations
	      ){
double pi=1;
long int i;

//parallel region
#pragma omp parallel for reduction(*:pi)
for (i=1;i<n;i++) pi *= (double) 4*i*i/(4*i*i-1);

pi*=2;
return pi;
}

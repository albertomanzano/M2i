
/*********************************************************************
* ejercicio5.c -- Norma del vector
*
* DESCRIPCION: calcula la norma2 de un vector
*
* AUTOR: Alberto P Manzano Herrero, alberto.manzano.herrero@gmail.es
* FECHA: 23/01/2020
*
* INPUT: ninguno
* OUTPUT: norma de un vector
*
* FUNCIONES:
/**********************************************************************/

#include <omp.h>
#include <stdio.h>
#include <math.h>


int main () {
long int  n = 500000;//Vector length
double a[n]; //Vector

long int i;
double norma;//norm2

//parallel region
#pragma omp parallel
{
//initialization of variables
#pragma omp for
for (i=0; i < n; i++) a[i] = 1.0;
//norm calculation
#pragma omp for reduction(+:norma)
for (i=0;i<n;i++) norma+=a[i]*a[i];

}
norma = sqrt(norma);

printf(" Norma2 = %lf\n",norma);

}



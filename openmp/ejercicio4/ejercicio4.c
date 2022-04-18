
/*********************************************************************
* ejercicio4.c -- Factorial
*
* DESCRIPCION: calcula el factorial de n
* 
* AUTOR: Alberto P Manzano Herrero, alberto.manzano.herrero@gmail.es
* FECHA: 23/01/2020
*      
* INPUT: ninguno
* OUTPUT: n!
*
* FUNCIONES:
*fac: calcula el factorial en paralelo
/**********************************************************************/

#include <stdio.h>
#include "omp.h"
#include <stdlib.h>
int main(){

int n = 5; //Numero del que calculamos el factorial
double factorial; //Resultado del factorial
double fac(int n);


factorial = fac(n);
printf("El factorial vale %lf\n",factorial);
}

double fac(int n//numero del que calculamos el factorial
	   ){
int i;
double factorial=1;//necesario inicializar en uno

//Seguridad
if (n==0 || n==1) return factorial;

if (n<0){
	printf("ERROR: is not possible to calculate negative factorial\n");
	exit(-1);
}

#pragma omp parallel for reduction(*:factorial)//usamos una reduccion multiplicando
for (i=n;i>0;i--) factorial*=i;

return factorial;
}


/*********************************************************************
* ejercicio2.c -- Integracion Simpson
*
* DESCRIPCION:
* Calculo de la integral de la funcion f(x) usando la regla de simpson compuesta
*
* AUTOR: Alberto P Manzano Herrero, alberto.manzano.herrero@gmail.es
* FECHA: 23/01/2020
*
*
* INPUT: ninguno
* OUTPUT: Valor de la integral.
*
* FUNCIONES:
* local_definition: define los extremos locales para el calculo de la integral
* simpson: dados los intervalos, el paso y el numero de iteraciones 
*	   calcula usando la regla de simpson
* f: funcion de la que calculamos la integral
/**********************************************************************/

#include<stdio.h>
#include "mpi.h"


void main(int argc, char** argv){
/*Calcula integral de la funcion f(x)*/
    int my_rank; /* Identificador del proceso*/
    int p; /*Numero de proceso*/

    float a; /*Extremo izquierdo de la integral*/
    float b; /*Extremo derecho de la integral*/
    int n; /*Numero de puntos*/
    float total; /*Resultado de la integracion*/

    float h; /*Paso*/
    float local_a; /*Extremo izquierdo para cada proceso*/
    float local_b; /*Extremo derecho para cada proceso*/
    int local_n; /*Numero de puntos para cada proceso*/
    float integral; /*Valor de la integral para cada proceso*/

    float simpson(int local_n,float local_a, float local_b, float h);
    void local_definition(int n,float a,float h,int *local_n,float *local_a,float *local_b, int p, int my_rank);

    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&p);
    MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);

    b = 10;
    a = 0;
    n = 1001;
    h = (b-a)/n;

    //Definicion de los limites de integracion para cada proceso
    local_definition(n,a,h,&local_n,&local_a,&local_b,p,my_rank);

    //Integral per se
    integral = simpson(local_n,local_a,local_b,h);

    // Suma de cada una de las integrales locales
    MPI_Reduce(&integral,&total,1,MPI_FLOAT,MPI_SUM,0,MPI_COMM_WORLD);
    if (my_rank ==0){
	printf("Total %f\n",total);
    }
    MPI_Finalize();
}
/*************************************************************************/
void local_definition(int n,     /* Numero de intervalos*/
			float a, /*Extrmo derecho*/
			float h, /*Paso*/
			int *local_n,/*Numero de intervalos por proceso*/
			float *local_a,/*Extremo izquierdo local*/
			float *local_b,/*Extremo derecho local*/
			int p, /*Numero de procesos*/
			int my_rank/*Rango del proceso*/
			){
	int aux;
	*local_n = n/p;
	aux = (n%p);
	/*Balancea la carga en los distintos procesos*/
	if ((my_rank)<aux){
		*local_n = *local_n+1;
		*local_a = a+(*local_n)*my_rank*h;
		*local_b = *local_a+(*local_n)*h;
	}	
	else{
		*local_a = a+(*local_n+1)*h*aux+h*(my_rank-aux)*(*local_n);
		(*local_b) = (*local_a)+(*local_n)*h;
	}
}

/*****************************************************************************/
float simpson(  int local_n,/*Numero de intervalos*/
		float local_a,/*Extremo izquierdo*/
		float local_b, /*Extremo derecho*/
		float h){/*Paso*/

	float integral;
	int i;
	float x;
	int limite;
	float suma_1=0;
	float suma_2=0;
	int parity = local_n%2;
	float f(float x);
	limite = (local_n-3*parity)/2;
	/*Un ajuste por si el intervalo es par*/
	for (i=1;i<=limite-1;i++){
		x = local_a+(2*i)*h;
		suma_1 = suma_1 + f(x);

	}
	for (i=1;i<=limite;i++){
		x = local_a+(2*i-1)*h;
		suma_2 = suma_2 + f(x);

	}
	integral = h*(f(local_a)+f(local_b-3*parity*h)+2*suma_1+4*suma_2)/3;
	if (parity != 0){
		integral = integral+(3*h/8)*(f(local_b-3*h) + 3*f(local_b-2*h) +3*f(local_b-h)+ f(local_b));
	}
	return integral;
}
/****************************************************************************/
float f(float x){
	float result;
	result = x*x*x*x*x;
	return result;

}


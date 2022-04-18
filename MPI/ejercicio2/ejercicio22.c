
/*********************************************************************
* ejercicio22.c -- Integracion Simpson
*
* DESCRIPCION:
* Calculo dela integral de la funcion f(x) usando la regla de simpson compuesta
* En esta ocasion se emplea una estrategia distinta para repartir la carga
* entre los distintos procesos
*
* AUTOR: Alberto P Manzano Herrero, alberto.manzano.herrero@gmail.es
* FECHA: 23/01/2020
*
*
* INPUT: ninguno
* OUTPUT: valor de la integral.
*
* FUNCIONES:
* simpson: reparte la carga computacional entre los procesos y realiza la integral
* f: funcion de la que calculamos la integral
/**********************************************************************/
#include<stdio.h>
#include "mpi.h"


void main(int argc, char** argv){
/*Calcula la integral de la funcion f(x)*/
    int my_rank; /*Identificador del proceso*/
    int p; /*Numero de procesos*/

    double a; /*Extremo izquierdo*/
    double b; /*Extremo derecho*/
    long int n; /*Numero de puntos*/
    double total; /*Resultado final*/

    double h; /*Paso*/
    double integral; /*Valor de la integral para cada proceso*/

    double simpson(int my_rank,int p, double a, double b,long int n);
    double f(double x);

    //Inicializacion de MPI
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&p);
    MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);

    b = 1.0;
    a = 0.0;
    n = 1000000000; //Numero suficiente para comparar la velocidad
    h = (b-a)/n;

    //Calculo de la integral local
    integral = simpson(my_rank,p,a,b,n);

    //Suma de las integrales locales
    MPI_Reduce(&integral,&total,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);

    //Calculo final e impresion por pantalla
    if (my_rank ==0){
	total = (total+f(a)+f(b))*h/3;
	printf("Total %lf\n",total);
    }
    MPI_Finalize();
}
/*************************************************************************/
double simpson(  int my_rank,/*Identificador del proceso*/
		int p,// Numero de procesos
		double a,/*Extremo izquierdo*/
		double b,// Extremo derecho
		long int n// Numero de puntos
		){

	double integral=0.0;
	long int i;
	double x;
	double h =(b-a)/n;//step

	double f(double x);
	for (i=my_rank;i<(n/2-1);i = i+p){//Puntos pares
		x = a+2*i*h;
		integral+= 2*f(x);
	}
	for (i=my_rank;i<(n/2);i=i+p){//Puntos impares
		x = a+(2*i-1)*h;
		integral += 4*f(x);
	}

	return integral;
}
/****************************************************************************/
double f(double x){
	double result;
	result = 4.0/(1+x*x);
	return result;
}


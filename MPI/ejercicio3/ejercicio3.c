/*********************************************************************
* ejercicio3.c -- Envio y recepcion
*
* DESCRIPCION:
* Envio de un numero real y una cadena, cada proceso imprime lo que le llega
*
* AUTOR: Alberto P Manzano Herrero, alberto.manzano.herrero@gmail.es
* FECHA: 23/01/2020
*
*
* INPUT: ninguno
* OUTPUT: Numero y cadena.
*
* FUNCIONES:

/**********************************************************************/

#include <stdio.h>
#include "mpi.h"
#include <string.h>

void main(int argc, char* argv[]) {
    int p;
    int my_rank;
    float a;
    char *ch;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &p);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	if (my_rank==0){
		a = 2;
		ch = "ejemplo de cadena";
	}
    MPI_Bcast(&a, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);
    MPI_Bcast(ch, 20, MPI_CHAR, 0, MPI_COMM_WORLD);
	if (my_rank != 0){
			printf("Proceso %d---a: %f, ch: %s\n",my_rank,a,ch);
	}
    MPI_Finalize();
}  /* main */


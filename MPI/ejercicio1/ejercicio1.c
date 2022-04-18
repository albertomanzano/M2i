
/*********************************************************************
* Ejercicio1.c -- Envio y suma
*
* DESCRIPCION:
* Todos los procesos con my_rank !=0 envian my_rank al proceso 0
* Proceso 0 suma los valores y lo imprime por pantalla
*
* AUTOR: Alberto P Manzano Herrero, alberto.manzano.herrero@gmail.es
* FECHA: 23/01/2020
*
* POSIBLES MEJORAS:
*
* INPUT: ninguno
* OUTPUT: numero del proceso que hace la impresion y suma.
*
* FUNCIONES:
*
/**********************************************************************/

#include <stdio.h>
#include "mpi.h"


void main(int argc, char** argv) {
    int         my_rank;   /* Rango del proceso           */
    int         p;         /* Numero de procesos   */
    int         source;    /* Direccion de la que se envia  */
    int         dest = 0;  /* Direccion a la que se envia      */
    int		tag=0; 	   /*tag*/
    MPI_Status  status;

    int i;
    int recep;
    int suma=0; /*Variable storing the sum*/


    /* Let the system do what it needs to start up MPI */
    MPI_Init(&argc, &argv);

    /* Get my process rank */
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    /* Find out how many processes are being used */
    MPI_Comm_size(MPI_COMM_WORLD, &p);

   // Envio
   if (my_rank != 0){
   	MPI_Send(&my_rank,1,MPI_INT,dest,tag,MPI_COMM_WORLD);
   }
   // Recepcion y suma
   else {
	for (i=1;i<p;i++){
		MPI_Recv(&recep,1,MPI_INT,i,tag,MPI_COMM_WORLD,&status);
		suma = suma+recep;
	}
   }
   // Impresion por pantalla
   if (my_rank==0)
	printf("En el proceso %d la suma es %d\n",my_rank,suma);
    /* Shut down MPI */
    MPI_Finalize();
} 


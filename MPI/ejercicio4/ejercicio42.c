

/*********************************************************************
* ejercicio4.c -- Factorial
*
* DESCRIPCION:calcula el factorial de n
* 
* AUTOR: Alberto P Manzano Herrero, alberto.manzano.herrero@gmail.es
* FECHA: 23/01/2020
*
*      
* INPUT: n
* OUTPUT: n!
*
* FUNCIONES:
/**********************************************************************/
#include <stdio.h>
#include "mpi.h"


void main(int argc, char* argv[]) {
    int    p;// Numero de procesos
    int    my_rank;// Identificador de cada proceso

    int n; //n!
    int local_product = 1;//Producto local
    int product; //Producto total
    int i;// Extremo izquierdo

    // Inicializacion MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &p);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    // Introduccion del numero por el usuario
    if (my_rank == 0) {
        printf("Enter number to calculate the factorial:\n");
        scanf("%d", &n);
    }

    // Envio al resto de procesos
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    //Calculo del producto local
    for (i=my_rank+1;i<=n;i=i+p)
	local_product=local_product*i;

   // Suma de productos locales
    MPI_Reduce(&local_product, &product, 1, MPI_INT,MPI_PROD, 0, MPI_COMM_WORLD);

    // Impresion por pantalla
    if (my_rank == 0)
        printf("The factorial is %d\n", product);

    MPI_Finalize();
}  /* main */
   






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
/*********************************************************************/

#include <stdio.h>
#include "mpi.h"


int main(int argc, char* argv[]) {
    long int    n;// Numero de iteraciones
    double  wallis;// Valor del prodcuto de wallis
    double  wallis_local=1;// Producto de wallis para cada proceso

    int    p;// Numero de procesos
    int    my_rank;// Identificador del proceso

    long int i:
    double Wallis(long int n);

    // Inicializamos MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &p);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    // Optativo para pedir el numero de iteraciones
    /*if (my_rank == 0) {
        printf("Enter number of iterations\n");
        scanf("%d", &n);
    }
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);*/

    // Numero de iteraciones significativo
    n = 10000000000;

    // Bucle para repartir y hacer los calculos
    for (i=my_rank+1;i<n;i = i+p)
    	wallis_local*=Wallis(i);

    // Suma de los productos locales
    MPI_Reduce(&wallis_local, &wallis, 1, MPI_DOUBLE,MPI_PROD, 0, MPI_COMM_WORLD);

    // Impresion por pantalla
    if (my_rank == 0)
        printf("The value of pi is: %lf\n", wallis*2);

    MPI_Finalize();
}  /* main */
   



/*****************************************************************/
double Wallis(long int  n  /* in */) {
    double wallis;
    wallis =(double) 4*n*n/(4*n*n-1);
    return wallis;
} /* Parallel_dot */
/******************************************************************/





/*********************************************************************
* ejercicio3.c -- Envio y recepcion
*
* DESCRIPCION:
* Envio de un numero real y una cadena mediante un tipo derivado
* Cada proceso imprime lo que le llega
*
* AUTOR: Alberto P Manzano Herrero, alberto.manzano.herrero@gmail.es
* FECHA: 23/01/2020
*
*      
* INPUT: ninguno
* OUTPUT: Numero y cadena.
*
* FUNCIONES:
* Build_derived_type: crea un tipo derivado
/**********************************************************************/

#include <stdio.h>
#include "mpi.h"

void Build_derived_type(
         float*         a_ptr           /* in   */,
         char*         b_ptr           /* in   */,
         MPI_Datatype*  mesg_mpi_t_ptr  /* out  */);

void main(int argc, char** argv) {
    int         my_rank;   /* Identificador proceso */
    int         p;         /* Numero de procesos   */
    float       a;         /* Numero a enviar     */
    char	*ch;	   /* Cadena a enviar*/
    MPI_Datatype  mesg_mpi_t; /* MPI type correspondiente a */
                              /* un float y una cadena *
/
    /* Inicializacion MPI */
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &p);
    if (my_rank == 0){
	a = 2;
	ch = "ejemplo de cadena";
    }

    //Creamos el tipo derivado
    Build_derived_type(&a,ch, &mesg_mpi_t);

    //Enviamos el tipo derivado
    MPI_Bcast(&a, 1, mesg_mpi_t, 0, MPI_COMM_WORLD);

    /* Imprimimos el resultado */
    if (my_rank != 0) {
        printf("Process %d a: %f, ch: %s\n",my_rank,a,ch);
    }

    /* Shut down MPI */
    MPI_Finalize();
} /*  main  */

/********************************************************************/
void Build_derived_type(
         float*         a_ptr           /* in   */,
         char*         b_ptr           /* in   */,
         MPI_Datatype*  mesg_mpi_t_ptr  /* out  */) {
                        /* pointer to the new MPI datatype*/

    /* The number of elements in each "block" of the   */
    /*     new type.  For us, 1 each.                  */
    int block_lengths[2];      

    /* Displacement of each element from start of new  */
    /*     type.  The "d_i's."                         */   
    /* MPI_Aint ("address int") is an MPI defined C    */
    /*     type.  Usually an int.                      */
    MPI_Aint displacements[2];

    /* MPI types of the elements.  The "t_i's."        */
    MPI_Datatype typelist[2];  
                              
    /* Use for calculating displacements               */
    MPI_Aint start_address; 
    MPI_Aint address;

    block_lengths[0] = 1;
    block_lengths[1] = 17;

    /* Build a derived datatype consisting of  */
    /* one float and a string                  */
    typelist[0] = MPI_FLOAT;
    typelist[1] = MPI_CHAR;

    /* First element, a, is at displacement 0      */
    displacements[0] = 0;

    /* Calculate other displacements relative to a */
    MPI_Address(a_ptr, &start_address);

    /* Find address of b and displacement from a   */
    MPI_Address(b_ptr, &address);
    displacements[1] = address - start_address;

    /* Build the derived datatype */
    MPI_Type_struct(2, block_lengths, displacements, 
        typelist, mesg_mpi_t_ptr);

    /* Commit it -- tell system we'll be using it for */
    /* communication.                                 */
    MPI_Type_commit(mesg_mpi_t_ptr);
} /* Build_derived_type */


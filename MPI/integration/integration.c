/* get_data3.c -- Parallel Trapezoidal Rule.  Builds a derived type
 *     for use with the distribution of the input data.
 *
 * Input: 
 *    a, b: limits of integration.
 *    n: number of trapezoids.
 * Output:  Estimate of the integral from a to b of f(x) 
 *    using the trapezoidal rule and n trapezoids.
 *
 * Notes:  
 *    1.  f(x) is hardwired.
 *    2.  the number of processes (p) should evenly divide
 *        the number of trapezoids (n).
 *
 * See Chap 6, pp. 90 & ff in PPMPI
 */
#include <stdio.h>

/* We'll be using MPI routines, definitions, etc. */
#include "mpi.h"


void main(int argc, char** argv) {
    int         my_rank;   /* My process rank           */
    int         p;         /* The number of processes   */
    float       a;         /* Left endpoint             */
    float	prueba;    /* Aquí es donde lo hacemos palmar*/
    float       b;         /* Right endpoint            */
    int         n;         /* Number of trapezoids      */
    float       h;         /* Trapezoid base length     */
    float       local_a;   /* Left endpoint my process  */
    float       local_b;   /* Right endpoint my process */
    int         local_n;   /* Number of trapezoids for  */
                           /* my calculation            */
    int         source;    /* Process sending integral  */
    int         dest = 0;  /* All messages go to 0      */
    MPI_Status  status;

    void Get_data3(float* a_ptr, float* b_ptr, int* n_ptr, int my_rank);

    /* Let the system do what it needs to start up MPI */
    MPI_Init(&argc, &argv);

    /* Get my process rank */
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    /* Find out how many processes are being used */
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    Get_data3(&a, &b, &n, my_rank);

if (my_rank==3){
	printf("Hasta aquí hemos llegado %f %f %d\n",a,prueba,n);
}

    /* Shut down MPI */
    MPI_Finalize();
} /*  main  */


/********************************************************************/
void Build_derived_type(
         float*         a_ptr           /* in   */,
         float*         b_ptr           /* in   */,
         int*           n_ptr           /* in   */,
         MPI_Datatype*  mesg_mpi_t_ptr  /* out  */) {
                        /* pointer to new MPI type */

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

    block_lengths[0] = 2;
    block_lengths[1] = 1;

    /* Build a derived datatype consisting of  */
    /* two floats and an int                   */
    typelist[0] = MPI_FLOAT;
    typelist[1] = MPI_INT;

    /* First element, a, is at displacement 0      */
    displacements[0] = 0;

    /* Calculate other displacements relative to a */
    MPI_Address(a_ptr, &start_address);

    /* Find address of b and displacement from a   */
    MPI_Address(n_ptr, &address);
    displacements[1] = address - start_address;


    /* Build the derived datatype */
    MPI_Type_struct(2, block_lengths, displacements, typelist, mesg_mpi_t_ptr);

    /* Commit it -- tell system we'll be using it for */
    /* communication.                                 */
    MPI_Type_commit(mesg_mpi_t_ptr);
} /* Build_derived_type */


/********************************************************************/
void Get_data3(
         float*  a_ptr    /* out */,
         float*  b_ptr    /* out */,
         int*    n_ptr    /* out */,
         int     my_rank  /* in  */) {
    MPI_Datatype  mesg_mpi_t; /* MPI type corresponding */
                              /* to 3 floats and an int */
    if (my_rank == 0){
        printf("Enter a, b, and n\n");
        scanf("%f %f %d", a_ptr, b_ptr, n_ptr);
    }

    Build_derived_type(a_ptr, b_ptr, n_ptr, &mesg_mpi_t);
    MPI_Bcast(a_ptr, 1, mesg_mpi_t, 0, MPI_COMM_WORLD);
} /* Get_data3 */


/********************************************************************/



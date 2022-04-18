/* parallel_dot.c -- compute a dot product of a vector distributed among
 *     the processes.  Uses a block distribution of the vectors.
 *
 * Input: 
 *     n: global order of vectors
 *     x, y:  the vectors
 *
 * Output:
 *     the dot product of x and y.
 *
 * Note:  Arrays containing vectors are statically allocated.  Assumes
 *     n, the global order of the vectors, is divisible by p, the number
 *     of processes.
 *
 * See Chap 5, pp. 75 & ff in PPMPI.
 */

#include <stdio.h>
#include "mpi.h"
#include <math.h>
#define MAX_LOCAL_ORDER 100

int main(int argc, char* argv[]) {
    int    i,n=2;//factorial
    double  x[2] = {1,1};
    double dot=0.0,final;
    int    p;
    int    my_rank;


    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &p);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    for (i=my_rank;i<n;i=i+p)
	dot+=x[i]*x[i];

    MPI_Reduce(&dot,&final,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
    if (my_rank == 0){
        printf("The dot product for process %d is %lf\n",my_rank, final);
	}
    MPI_Finalize();
}  /* main */


/*****************************************************************/
void Read_vector(
         char*  prompt     /* in  */,
         float  local_v[]  /* out */,
         int    n_bar      /* in  */,
         int    p          /* in  */,
         int    my_rank    /* in  */) {
    int i, q;
    float temp[MAX_LOCAL_ORDER];
    MPI_Status status;

    if (my_rank == 0) {
        printf("Enter %s\n", prompt);
        for (i = 0; i < n_bar*p; i++){
	    printf("vector[%d]:\n ",i);
            scanf("%f", &temp[i]);
	}
    }
    MPI_Scatter(temp,n_bar, MPI_FLOAT, local_v,n_bar, MPI_FLOAT, 0, MPI_COMM_WORLD);

}  /* Read_vector */


/*****************************************************************/
float Serial_dot(
          float  x[]  /* in */, 
          float  y[]  /* in */, 
          int    n    /* in */) {

    int    i; 
    float  sum = 0.0;

    for (i = 0; i < n; i++)
        sum = sum + x[i]*y[i];
    return sum;
} /* Serial_dot */


/*****************************************************************/
float Parallel_dot(
          float  local_x[]  /* in */,
          float  local_y[]  /* in */,
          int  n_bar        /* in */) {

    float  local_dot;
    float  dot = 0.0;
    float  Serial_dot(float x[], float y[], int m);

    local_dot = Serial_dot(local_x, local_y, n_bar);
    MPI_Reduce(&local_dot, &dot, 1, MPI_FLOAT,MPI_SUM, 0, MPI_COMM_WORLD);
    return dot;
} /* Parallel_dot */


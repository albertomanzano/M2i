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
    int    i,n=5;//factorial
    double  x[5] = {1,1,1,1,1};
    double final;
    int    p;
    int    my_rank;

    void Parallel_dot(int my_rank, int p, int n, double x[], double *final);
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &p);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    //MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    Parallel_dot(my_rank,p,n,x,&final);

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
void Parallel_dot(
          int my_rank  /* in */,
          int p  /* in */,
	  int n,
          double  x[],
	  double *final) {
	int i;
	double dot=0.0;
	for (i=my_rank;i<n;i=i+p){
		dot+=x[i]*x[i];
	printf("For process %d, element %d dot: %lf\n",my_rank,i,dot);}
	MPI_Reduce(&dot,final,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);

} /* Parallel_dot */


#include <stdio.h>
#include "omp.h"

static long num_steps = 1000000000; double step;
#define NUM_THREADS 8

void main(){
int i,nthreads; double pi = 0.0;
step = 1.0/(double)num_steps;
omp_set_num_threads(NUM_THREADS);
#pragma omp parallel
{
double x;
#pragma omp for reduction(+:pi)
for (i=0;i<num_steps;i++){
	x = (i+0.5)*step;
	pi += 4.0/(1.0+x*x);
 }
}
pi = pi*step;
printf("pi: %lf",pi);
}

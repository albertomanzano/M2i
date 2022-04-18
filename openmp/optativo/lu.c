#include <stdio.h>
#include <omp.h>

void main(){
int n = 2;
int i,j;
double a[n][n],lu[n][n];

void mat_display(int m, int n,double a[m][n]);

for (i=0;i<n;i++){
	for (j=0;j<n;j++){
		a[i][j]=1.0;
	}
}

for (j=0;j<n;j++){
  for (i=0;i<j;i++){
    u(i,j) = a(i,j) - dot_product(l(i,1:i-1), u(1:i-1,j));
  }
  l(j,j) = 1.0;
  for (i = j+1;i<n;i++){
    l(i,j) = (a(i,j) - dot_product(l(i,1:j-1), u(1:j-1,j))) / u(j,j);
}

}
void mat_display(int m,int n,double a[m][n]){
int i,j;
for (i=0;i<m;i++){
	printf("| ");
	for (j=0;j<n;j++){
	printf("%lf ",a[i][j]);
	}
	printf("|\n");
}
}


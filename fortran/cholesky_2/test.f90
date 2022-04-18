
! This program makes the prediction of the orbit of a planet
! from a tuple of points, which specify the position of the planet at 
! a given time.

! License: This code is distributed under license GNU GPL v3

! Authors: Francisco Pena Brage, Alberto Manzano Herrero, 
! Celia Navarro Montes de Oca, Jose Manuel Perales Fernández,
! Daniel Galera Nebot

program programa

use module_descomposition, only : cholesky_factorization, &
        matrix_generator,vector_generator,real64
use matrix_class
use module_functions, only: coseno,series
use module_resolution, only: descenso, remonte
use data_manage
implicit none
type(matrix) :: a, r !a-> input matrix, r decomposed matrix
integer, parameter :: data_length = 12, w_length = 10
real(real64), parameter :: pi = 3.1415
real(real64) :: x(data_length), y(data_length), d(w_length),&
	& b(w_length), c(w_length), z(1000),x_aux(1000)
real(real64) :: matriz(data_length,2), aux(1000,2)
integer :: i
real(real64) :: w(w_length)!=real(([(i, i=0,6,1)]),real64) !parameters of the base
call read_matrix_2("w.txt",w_length,1,w)
w=w*pi/180
call read_matrix_2("m.txt",data_length,2,matriz)!read the m.txt matrix with dimensions m = data_length n = 2
!and save it in matrix
x = matriz(:,1)!Segment in which we approximate the function
y = matriz(:,2)!Function values in the segment
call matrix_generator(coseno,w,x,a)!Generates the least squares matrix of a polynomial base
d = vector_generator(coseno,w,x,y)!Generates the least squares vector
!System resolution:
call cholesky_factorization(size(w),a,r)!Performs Cholesky factorization

b = descenso(r,d)
c = remonte(r,b)
print*, c
do i = 1,1000
	aux(i,1) = (x(12)-x(1))*i/1000+x(1)
end do

aux(:,2) = series(coseno,w,aux(:,1),c)!Values of the approximate function in x-segment 

call write_matrix_2("n.txt",1000,2,aux)

end program

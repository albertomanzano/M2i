
module module_descomposition
!
!Module to decompose a matrix in COO format
!
!
! License: This code is distributed under license GNU GPL v3
! Authors: Francisco Pena Brage, Alberto Manzano Herrero, 
! Celia Navarro Montes de Oca, Jose Manuel Perales Fernández,
! Daniel Galera Nebot
! 
!       PUBLIC PROCEDURES:
!   cholesky_factorization: decomposes a symmetric positive defined matrix 
!   matrix using cholesky's algorithm
!   matrix_generator: generates the matrix needed for least squares
!   vector_generator: generates the vector needed for least squares

use iso_fortran_env, only: real64
use matrix_class
implicit none
contains


!-------------------------------------
!cholesky_factorization: decomposes a symmetric positive defined matrix
!--------------------------------------

subroutine cholesky_factorization(m,matriz,cholesky)
! Function that descomposes into a matrix c
integer, intent(in) :: m !Dimensions of the input matrix mxm
type(matrix), intent(in) :: matriz ! Data entry matrix with dimensions mxm
type(matrix), intent(out) ::  cholesky !Output matrix

integer :: i,j,k
real(real64) :: aux1, aux2, aux3, aux4

do j=1,m
	do i=j,m
		if (i==j) then
		call set(cholesky,j,j,sqrt(get(matriz,j,j)-&
		dot_product(get(cholesky,j,[(k,k=1,j-1)]),get(cholesky,j,[(k,k=1,j-1)]))))
		else
		call set(cholesky,i,j,(get(matriz,i,j)-&
		dot_product(get(cholesky,i,[(k,k=1,j-1)]),get(cholesky,j,[(k,k=1,j-1)])))/(get(cholesky,j,j)))
			
		end if

		
	end do
end do
end subroutine

!-------------------------------------
!matrix_generator: generates the matrix needed for least squares
!--------------------------------------

subroutine matrix_generator(f,w,x,matriz)
!---------------------------------------
! f: function base
! w: function base coefficients
! x: segment in which the function is approximated
! matrix: matrix in which the result is saved
!---------------------------------------
real(real64), intent(in) :: w(:), x(:)
type(matrix) :: matriz
integer :: i,j
real(real64) :: val
interface
        function f(w,x) result(y)       ! nonlinear scalar function
             use iso_fortran_env, only: real64
             real(real64) :: x(:),w
             real(real64) :: y(size(x))
        end function
end interface
call alloc_by_size(matriz,size(w))

do j = 1,size(w)
	do i= j,size(w)
		val = dot_product(f(w(i),x),f(w(j),x))
		call set(matriz,i,j,val)
	end do
end do

end subroutine


!---------------------------------------------
!vector generator: generates the vector needed for least squares
!---------------------------------------------

function vector_generator(f,w,x,y) result(d)
!------------------------------------------
! f: function base
! w: function base parameters
! x: segment in which the approximation is calculated
! y: values of the function at x points 
! d: vector of least squares
!------------------------------------------

real(real64) :: w(:), d(size(w)), x(:), y(:), aux(size(x))

interface
        function f(w,x) result(z)       ! nonlinear scalar function
             use iso_fortran_env, only: real64
             real(real64) :: x(:),w
             real(real64) :: z(size(x))
        end function
end interface
integer :: i
do i = 1, size(w)
        d(i) = dot_product(f(w(i),x),y)
end do
end function
end module module_descomposition

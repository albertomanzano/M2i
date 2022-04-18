module module_resolution
!-----------------------------------------------------------------------
! Module to solve linear systems by ascent(remonte) and descent(descenso)
!
! License: This code is distributed under the GNU GPL license
! Authors: Francisco Pena Brage, Alberto Manzano Herrero, 
! Celia Navarro Montes de Oca, Jose Manuel Perales Fernández,
! Daniel Galera Nebot
!
! PUBLIC PROCEDURES:
! remonte: solve linear systems by ascent
! descenso: solve linear systems by descent
!-----------------------------------------------------------------------
use iso_fortran_env, only: real64
use matrix_class
implicit none

contains

!--------------------------------------
!remonte: solve linear systems by ascent 
!---------------------------------------

function remonte(a, b) result(x)
type(matrix), intent(in)  :: a
real(real64), intent(in)  :: b(:)
real(real64), allocatable :: x(:)
integer :: i, n, k

n = size(a,2)
allocate(x(n))
x(n) = b(n) / get(a, n, n)
do i = n-1, 1, -1
  x(i) = (b(i) - dot_product(get(a,[(k, k=i+1,n)],i), x(i+1:n))) / get(a, i, i)
end do
end function

!--------------------------------------
!descenso: solve linear systems by descent 
!---------------------------------------

function descenso(a, b) result(x)
type(matrix), intent(in)  :: a
real(real64), intent(in)  :: b(:)
real(real64), allocatable :: x(:)
integer :: i, n, k
n = size(a,2)
allocate(x(n))
x(1) = b(1) / get(a, 1, 1)
do i = 2, n
  x(i) = (b(i) - dot_product(get(a, i, [(k, k=1,i-1)]), x(1:i-1))) / get(a, i, i)
end do
end function

end module


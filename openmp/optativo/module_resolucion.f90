module module_resolucion
!-----------------------------------------------------------------------
! Modulo para resolver sistemas lineales por remonte y descenso
!
! Licencia: Este codigo esta distribuido bajo la licencia GNU GPL
! Autor: Francisco Pena, fran(dot)pena(at)usc(dot)es
! Ultima actualizacion: 15/10/2018
!
! PROCEDIMIENTOS PUBLICOS:
!   remonte: resuelve sistemas lineales por remonte (pag. 2 de 
!   los apuntes de teoria de MNP)
!   descenso: resuelve sistemas lineales por descenso (pag. 3 de 
!   los apuntes de teoria de MNP)
!-----------------------------------------------------------------------
use iso_fortran_env, only: real64
implicit none

contains
function remonte(a, b) result(x)
real(real64), intent(in) :: a(:,:), b(:)
real(real64), allocatable :: x(:)
integer :: i, n
n = size(a,2)
allocate(x(n))
x(n) = b(n) / a(n,n)
do i = n-1, 1, -1
  x(i) = (b(i) - dot_product(a(i,i+1:n), x(i+1:n))) / a(i,i)
end do
end function

function descenso(a, b) result(x)
real(real64), intent(in) :: a(:,:), b(:)
real(real64), allocatable :: x(:)
integer :: i, n
n = size(a,2)
allocate(x(n))
x(1) = b(1) / a(1,1)
do i = 2, n
  x(i) = (b(i) - dot_product(a(i,1:i-1), x(1:i-1))) 
end do
end function

end module


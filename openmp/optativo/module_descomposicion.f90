module module_descomposicion
!-----------------------------------------------------------------------
! Modulo para realizar la descomposicion de matrices
!
! Licencia: Este codigo esta distribuido bajo la licencia GNU GPL
! Autor: Francisco Pena, fran(dot)pena(at)usc(dot)es
! Ultima actualizacion: 26/09/2015
!
! PROCEDIMIENTOS PUBLICOS:
!   lu: realiza la descomposicion LU de una matriz llena (pag. 28 de 
!   los apuntes de teoria de MNP)
!
! POSIBLES MEJORAS:
!   - devolver U en la matriz de entrada
!   - comprobación de que la factorizacion LU es posible
!   - implementación de la permutacion
!   - introduccion de matrices dispersas
!-----------------------------------------------------------------------
use iso_fortran_env, only: real64
implicit none

contains

!-----------------------------------------------------------------------
! lu: realiza la descomposicion LU de una matriz llena
!-----------------------------------------------------------------------
subroutine lu (a, l, u)
real(real64), intent(in) :: a(:,:)
real(real64), allocatable, intent(out) :: l(:,:), u(:,:)
integer :: i, j

allocate(l(size(a,1),size(a,2)), u(size(a,1),size(a,2)))
do j = 1, size(a,2)

  do i = 1, j
    u(i,j) = a(i,j) - dot_product(l(i,1:i-1), u(1:i-1,j))
  end do
  do i = j+1, size(a,2)
    l(i,j) = (a(i,j) - dot_product(l(i,1:j-1), u(1:j-1,j))) / u(j,j)
  end do
end do
end subroutine

end module


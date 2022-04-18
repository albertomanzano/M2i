!Implementación del método de Gauss-Seidel


module module_resolucion

use iso_fortran_env, only: real64
implicit none

contains

subroutine gauss_seidel(a,b,x0,eps,M,conv,x,k)

!Definimos de manera distinta x y x0 para  evitar cierto tipo de problemas
!Primero definimos las variables de entrada del método
real(real64), intent(in) :: b(:)
real(real64), intent(in) :: a(:,:)
real(real64), intent(in) :: eps
real(real64), intent(in) :: x0(:)
integer, intent(in) :: M
real(real64), intent(out) :: x(:)
logical, intent(out) :: conv
integer, intent(out) :: k

!Definimos las variables auxiliares del método
integer :: i,j,n
real(real64) :: xk,norma

!Inicialización de las variables
x = x0
n=size(x)
print*,n
conv = .false.
!Algoritmo per se
do k=1,M
	print*, "Paso 1"

	norma = 0._real64
	print*, "Paso 2"

	do i=1,n
		print*, "Paso 3"

		xk = x(i) !Variable auxiliar para ir calculando la norma
		print*, "Paso 4"

		x(i) = ( b(i)-dot_product( A(i,1:i-1),x(1:i-1) )-dot_product( A(i,i+1:n),x(i+1:n) ))/a(i,i)
		print*, "Paso 5"
		print*, "Paso 6"
		norma = norma + (x(i)-x(k))*(x(i)-x(k))

	end do
	print*,x
	print*, "Paso 7"

	norma = sqrt(norma)
	print*, "Paso 8"

	if (norma < eps*norm2(x))  then
		conv = .true.
		return
	end if
end do

end subroutine

end module

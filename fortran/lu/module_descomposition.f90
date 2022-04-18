
!function [l,u] = lu(a) Matlab
!subroutine lu (a,l,u) Fortran
!void la(a,l,u) C
!function lu(a,u,l) result (error) Fortran Ojo también se están devolviendo la a y la u

!Recomendación: si quiero sacar varios argumentos, uso subrutinas. Si quiero sacar un argumento principal y otros secundarios uso funciones

!real(real64) :: l doble precisión, si no ponemos real64 sería precisión simple


module module_descomposition !fortran admite programación orinteada a objetos cuando usemos el modulo llamamos al nombre del modulo. Cuando compilemos usamos el nombre del fichero.
use iso_fortran_env, only: real64, int64, local_real32 => real32 !puede ocurrir que alguna varibale importada choque con una de las que hemos definido por eso empleamos only. También hemos definido
!un alias
implicit none !En el fortran antiguo no hacía falta declarar las variables, esto se indica para que TODAS las variables sean declaradas

!Por encima de contains introduciríamos los tipos de dato de las clases

contains !Indicamos los métodos que vamos a usat

subroutine lu(a,l,u)

!Declaramos las varibels al principio
real(real64), intent(in) :: a(:,:)!Indicamos que son argumentos de entrada: intent(in) de salida intent(out) o ambas: intent(inout)
!Ojo al haberlo declarado así, no te permite usar ni u ni l como argumentos ?
real(real64), allocatable, intent(out) :: l(:,:), u(:,:)!para indicar que es una matriz metemos los índices
integer :: i,j,n,m
logical :: alloc

n = size(a,1)
m = size(a,2)
if (.not. allocated(l)) then !.not. es un operador lógico, los operadores y valores lógicos se les coloca un punto delante y otro detrás. Es posible rsumir las líneas
	alloc = .true.
	allocate( l(n,m))
else
	print*,'ERROR',27 !El asterisco es para indicar formatos. Doy una lista de las cosas que quiero imprimir separado por comas
	stop 1 !Por convención en linux se devuelve uno cuando hay algún tipo de error y cero cuando no lo hay
end if
allocate(u(m,n))

do j=1, n !Vamos a ver si se compila
	do i=1,j

		u(i,j) = a(i,j)-dot_product(l(i,1:i-1),u(1:i-1,j))
		l(j,j) = 1._real64 !Matlab: trabaja por defecto en doble precision Fortran: por defecto en integer
			!Si pusiesemos 1. y lo guardásemos en uno de precisión doble, fortran se inventaría los siete últimos decimales
			!32 bits IEEE754 => 7,8 cifras decimales de precisión
	
		!64 bits IEEE754 => 15,16
	end do
	do i=j+1,n
		l(i,j) = (a(i,j) - dot_product( l(i,1:j-1),u(1:j-1,j) ))/u(j,j)
	end do
end do
end subroutine lu


subroutine DisplayMatrix(a,m,n)
integer, intent(in) :: m,n
real(real64), intent(in) :: a(m,n)
integer :: i
do i=1,m
	print*,'|', a(i,:),'|'
end do

end subroutine DisplayMatrix
end module module_descomposition
!Para usar el modulo se emplea la instrucción use module_descomposition


!Programa principal
!program test_lu
!real(real64), allocatable  ::  a(:,:), l(:,:), u(:,:) de esta manera paso de memoria estática a memoria dinámica
! a=...
! lu(a,l,u)

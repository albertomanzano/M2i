

module module_resolution 
use iso_fortran_env, only: real64, int64, local_real32 => real32 
!un alias
implicit none 


contains 

function remonte(a,b) result(x) !Nos damos cuenta que como sólo se devuelve una variable hacemos una funcion en vez de subrutina

!Declaramos las varibels al principio
real(real64), intent(in) :: a(:,:)!Indicamos que son argumentos de entrada: intent(in) de salida intent(out) o ambas: intent(inout)
real(real64), intent(in) :: b(:)!para indicar que es una matriz metemos los índices
real(real64), allocatable :: x(:) !Como ya es out (por ser funcion) no indicamos que es out, como vamos a definir su dimensión indicamos allocatable
integer :: i,n,m

n = size(a,1)
m = size(a,2)
allocate(x(n))
!Hay que añadir que si el tamaño es distinto pase algo


x(n) = b(n)/a(n,n) !Según se indica el método

do i=n-1, 1 ,-1 !El paso se indica al final del método

	x(i) = ( b(i)-dot_product(a(i,i+1:n),x(i+1:n)) )/a(i,i)

end do
end function

function descenso(a,b) result(x) !Nos damos cuenta que como sólo se devuelve una variable hacemos una funcion en vez de subrutina

!Declaramos las varibels al principio
real(real64), intent(in) :: a(:,:)!Indicamos que son argumentos de entrada: intent(in) de salida intent(out) o ambas: intent(inout)
real(real64), intent(in) :: b(:)!para indicar que es una matriz metemos los índices
real(real64), allocatable :: x(:) !Como ya es out (por ser funcion) no indicamos que es out, como vamos a definir su dimensión indicamos allocatable
integer :: i,n,m

n = size(a,1)
m = size(a,2)
allocate(x(n))
!Hay que añadir que si el tamaño es distinto pase algo


x(1) = b(1)/a(1,1) !Según se indica el método


do i=2,n !El paso se indica al final del método

        x(i) = ( b(i)-dot_product(a(i,1:i-1),x(1:i-1)) )/a(i,i)


end do
end function

end module module_resolution

!Módulo con el objetivo de escribir un fichero .m 

module escritura
use iso_fortran_env, only: real64

implicit none
contains

subroutine escribe(x,y,direccion)
real(real64), intent(in) :: x(:)
real(real64), intent(in) :: y(:)
character(len=9), intent(in) :: direccion

integer :: error_status
if (size(x) .ne. size(y) ) then
	print*, "ERROR: (escritura/dimensions), las dimensiones de x,y no coinciden"
end if 

open(11,file = direccion)
write(11,*) x
write(11,*) y

close(11)

end subroutine


end module escritura

program test
use escritura, only: real64, escribe
implicit none
real(real64) :: x(20),y(20)
x = [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20]
y = [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20]
call escribe(x,y,"datos.txt")

end program test

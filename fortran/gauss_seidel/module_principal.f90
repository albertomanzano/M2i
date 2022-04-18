program ejecutable
use module_resolucion, only: gauss_seidel, real64

implicit none
real(real64) :: a(3,3),b(3),x0(3),x(3)
real(real64) :: eps
integer :: M,k
logical :: conv

a = reshape(real([9,2,1,4,9,4,7,8,9],real64),[3,3],order = [2,1])
b = 1._real64
x0 = 0._real64
M = 1000
call gauss_seidel(a,b,x0,1.e-6_real64,M,conv,x,k)
print *, "Hasta aquí llegamos"

if (conv) then
	print*, "El programa ha convergido"
else
	print*, "El programa no ha convergido"
end if

end program

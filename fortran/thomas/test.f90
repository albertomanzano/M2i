program test
use data_manage, only: real64, read_matrix, display_matrix
use module_resolution, only: transpose_check, cholesky_factorization
implicit none

real(real64) :: a(3,3), l(3,3)
integer :: m,n,check
character (len=100) :: doc

m = 3
n = 3
doc = "data.txt"

call read_matrix(doc,m,n,a)
call display_matrix(m,n,a)
check = transpose_check(m,n,a)
if (check ==-1) then
	print*, "The matrix is not symetric"
else
	print*, "The matrix is symetric"
	call cholesky_factorization(n,a,l)
	call display_matrix(m,n,l)
end if
end program

!Factoriza matrices tridiagonales


module module_resolution
use data_manage, only: real64, read_matrix, display_matrix
implicit none
contains

function transpose_check(m,n,matriz) result (check)
integer :: m,n,i,j,check
real(real64) :: matriz(m,n)

check = 1

do i =1,n
	do j = i+1,n
		if (matriz(i,j) .ne. matriz(j,i)) then 
			check = -1
			exit
		end if
	end do
end do

end function

subroutine cholesky_factorization(n,a,L)
integer, intent(in) :: n
real(real64), intent(in) :: a(n,n)

real(real64), intent(out) :: L(n,n)

integer :: i,j

do i = 1,n
	do j = i,n
		if (i==j) then
			L(i,i) = sqrt(a(i,i)-dot_product(L(i,1:i-1),L(1:i-1,i)))
		else
			L(i,j) = (a(i,j)-dot_product(L(j,1:i-1),L(1:i-1,j)))/L(i,i)
		end if
	end do
end do

end subroutine

end module

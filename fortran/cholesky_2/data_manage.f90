module data_manage
use matrix_class
implicit none

contains
!-------------------------------------------------------
!read_matrix: read a matrix from a txt and saves it in a triangular matrix
!-------------------------------------------------------

subroutine read_matrix(direccion,m,n,triangular)
!Read data from a file and save it in a triangular matrix
!In advance, it is necessary to know the dimensions of the matrix

character (len=100), intent(in) :: direccion ! The address of the file it is going to read
integer, intent(in) :: m,n !Matrix dimensions, m rows, n columns
type(matrix), intent(out) :: triangular !Matrix in which the data is loaded

real(real64) :: matriz(m,n) !Matrix where the data is stored

integer :: i,j,error_status !Store 0 if there are no problems, -1 if it reads the entire document, 1 if it fails

open(unit = 11,file = direccion,status = "old",iostat = error_status)
if (error_status .ne. 0) then
	print*, "Error opening the document"
	stop
end if
do i=1,m
	read(11,*) matriz(i,:)
end do
!$OMP DO
do j=1,n
	do i=j,m
		if (matriz(i,j) == matriz(j,i)) then
			call set(triangular,i,j,matriz(i,j))
		else
			stop
		end if
	end do
!$OMP END DO
end do
close(11)
end subroutine

!-------------------------------------------------------
!read_matrix_2:reads from a txt and saves it in a standard matrix
!-------------------------------------------------------

subroutine read_matrix_2(direccion,m,n,matriz)
!Read data from a file and save it in the matrix.
!In advance, it is necessary to know the dimensions of the matrix


character (len=5), intent(in) :: direccion !The address of the file it is going to read
integer, intent(in) :: m,n !Matrix dimensions, m rows, n columns
real(real64), intent(out) :: matriz(m,n) !Matrix in which the data is loaded

integer :: i,error_status !Store 0 if there are no problems, -1 if it reads the entire document, 1 if it fails


open(unit = 11,file = direccion,status = "old",iostat = error_status)
if (error_status .ne. 0) then
	print*, "Error opening the document"
	stop
end if
do i=1,m
	read(11,*) matriz(i,:)
end do

close(11)
end subroutine
!----------------------------------------------------------------
!write_matrix_2: Write the matrix data to a file
!---------------------------------------------------------------
subroutine write_matrix_2(direccion,m,n,matriz)
!Read data from a file and save it in the direction.
!In advance, it is necessary to know the dimensions of the matrix


character (len=5), intent(in) :: direccion !The address of the file it is going to read
integer, intent(in) :: m,n !Matrix dimensions, m rows, n columns
real(real64), intent(out) :: matriz(m,n) !Matrix in which the data is loaded

integer :: i,error_status !Store 0 if there are no problems, -1 if it reads the entire document, 1 if it fails

open(unit = 11,file = direccion,status = "old",iostat = error_status)
if (error_status .ne. 0) then
	print*, "Error opening the document"
	stop
end if
 
do i=1,m
	write(11,*) matriz(i,:)
end do
close(11)
end subroutine

FUNCTION julian_date (yyyy, mm, dd) RESULT (julian)
! converts calendar date to Julian date
! cf Fliegel & Van Flandern, CACM 11(10):657, 1968
! example: julian_date(1970,1,1)=2440588
INTEGER,INTENT(IN) :: yyyy,mm,dd
real(real64) :: julian
julian = dd-32075+1461*(yyyy+4800+(mm-14)/12)/4 + &
367*(mm-2-((mm-14)/12)*12)/12- &
3*((yyyy + 4900 + (mm - 14)/12)/100)/4
END FUNCTION julian_date

SUBROUTINE get_ymd (jd, yyyy, mm, dd)
! expands a Julian date into a calendar date
! cf Fliegel & Van Flandern, CACM 11(10):657, 1968
real(real64),INTENT(IN) :: jd
INTEGER,INTENT(OUT) :: yyyy,mm,dd
INTEGER :: l,n
l = jd + 68569
n = 4*l/146097
l = l - (146097*n + 3)/4
yyyy = 4000*(l + 1)/1461001
l = l - 1461*yyyy/4 + 31
mm = 80*l/2447
dd = l - 2447*mm/80
l = mm/11
mm = mm + 2 - 12*l
yyyy = 100*(n - 49) + yyyy + l
END SUBROUTINE get_ymd

subroutine date_read(document,julian,length)
character(len=100), intent(in) :: document
integer, intent(in) :: length
real(real64), intent(out) :: julian(length)
integer :: d,m,y,i

open(11, file=document, status='old')

do i= 1,length
	read(11,"(i4,i2,i2)") y,m,d
	julian(i) =  julian_date(y,m,d)
end do

close(11)
end subroutine
end module 

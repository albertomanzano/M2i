module matrix_class
!-----------------------------------------------------------------------
! Module to manage matrices in COO format
!
! License: This code is distributed under license GNU GPL v3
! Authors: Francisco Pena Brage, Alberto Manzano Herrero, 
! Celia Navarro Montes de Oca, Jose Manuel Perales Fernández,
! Daniel Galera Nebot


! PUBLIC PROCEDURES:
!   dealloc: deallocates the matrix
!   alloc: allocates a matrix
!   size_matrix: gets the size of the matrix
!   get: gets a scalar value, sub_row or sub-column
!   set: sets a scalar value in the matrix
!   matmul: multiplies a matrix by a vector
!   show: show matrix in row order
!   read_matrix: reads from a txt and saves it in a triangular matrix
!   read_matrix_2: reads from a txt and saves it in a standard matrix
!   write_matrix_2: write in a txt data from a standard matrix
!-----------------------------------------------------------------------
use iso_Fortran_env, only: real64

type :: matrix
  private
  integer :: n, m
  integer, allocatable :: row(:), col(:)
  real(real64), allocatable :: val(:)
end type

interface get !public name outside this module 
  module procedure get_sca 
  module procedure get_row
  module procedure get_col
end interface

interface set
  module procedure set_sca
end interface

interface size
  module procedure size_matrix
end interface

interface matmul
  module procedure matmul_matrix
end interface


private :: get_sca, get_col, get_row, size_matrix,&
       set_sca, matmul_matrix  !this names are hidden outside this module
 
contains

!-----------------------------------------------------------------------
! dealloc: deallocates the matrix
!-----------------------------------------------------------------------
subroutine dealloc(this)
type(matrix) :: this
integer :: i, res
character(255) :: cad

if (allocated(this%row)) deallocate(this%row, stat = res, errmsg = cad) !the best way
if (res /= 0) then
  print*, 'ERROR (matrix/dealloc) Unable to deallocate row'
  stop 1
end if
if (allocated(this%col)) deallocate(this%col, stat = res, errmsg = cad)
if (res /= 0) then
	print*, 'ERROR  Unable to deallocate column'
end if

if (allocated(this%val)) deallocate(this%val, stat = res, errmsg = cad)
if (res /= 0) then
	print*, 'ERROR Unable to deallocate values'
end if
end subroutine

!-----------------------------------------------------------------------
! alloc: allocates a matrix
!-----------------------------------------------------------------------
subroutine alloc(this, row, col, val)
type(matrix)             :: this
integer,      intent(in) :: row(:), col(:)
real(real64), intent(in) :: val(:)
character(255) ::  cad
integer :: res

!check size
if (size(row,1) /= size(col,1) .or. size(row,1) /= size(val,1)) then
  print*, 'ERROR (matrix/alloc) The three input arrays have different size.'
  stop 1
end if
if (size(row,1) <= 0) then
  write(cad, *) size(row,1) 
  print*, 'ERROR (matrix/alloc) The input arrays have an invalid size: '//trim(adjustl(cad))
  stop 1
end if
!allocation
if (allocated(this%row) .or. allocated(this%col) .or. allocated(this%val)) call dealloc(this)
allocate(this%row(size(row,1)), stat = res)
if (res /= 0) then
	print*, 'ERROR, Unable to allocate row'
end if
allocate(this%col(size(row,1)), stat = res)
if (res /= 0) then
	print*, 'ERROR, Unable to allocate column'
end if
allocate(this%val(size(row,1)), stat = res)
if (res /= 0) then
	print*, 'ERROR, Unable to allocate value'
end if

!initial values
this%row = row
this%col = col
this%val = val
this%n = maxval(row)
this%m = maxval(col)
end subroutine

!-----------------------------------------------------------------------
! alloc_by_size: allocates by size a matrix
!-----------------------------------------------------------------------

subroutine alloc_by_size(this, m)
type(matrix), intent(out)             :: this
integer, intent(in)  :: m !Size of the matrix to be allocated

real(real64) :: auxiliar_row((m*m+m)/2), auxiliar_col((m*m+m)/2) 
character(255) ::  cad
integer :: res, length,k 

length = (m*m+m)/2

!check size
if (m <= 0) then
  write(cad, *) length 
  print*, 'ERROR (matrix/alloc) The input arrays have an invalid size: '//trim(adjustl(cad))
  stop 1
end if
!allocation
if (allocated(this%row) .or. allocated(this%col) .or. allocated(this%val)) call dealloc(this)
allocate(this%row(length), stat = res)
if (res /= 0) then
	print*, 'ERROR, Unable to allocate row'
end if
allocate(this%col(length), stat = res)
if (res /= 0) then
	print*, 'ERROR, Unable to allocate column'
end if
allocate(this%val(length), stat = res)
if (res /= 0) then
	print*, 'ERROR, Unable to allocate value'
end if

k = 0;
do j=1,m
	do i = j,m
                k =k+1;
		auxiliar_row(k) = j
		auxiliar_col(k) = i
	end do

end do


!initial values
this%row = auxiliar_row 
this%col = auxiliar_col
this%val = 0._real64
this%n = m
this%m = m
end subroutine

!-----------------------------------------------------------------------
! size_matrix: gets the size of the matrix
!-----------------------------------------------------------------------
function size_matrix(this, d) result(res)
type(matrix), intent(in) :: this
integer, intent(in)      :: d
integer :: res
character(255) :: cad

select case (d) 
!If 1 is chosen, it gives the number of rows. If 2 is chosen, it gives the number of columns. 
!Otherwise, it displays an error message on the screen.
case(1) 
  res = this%n
case(2)
  res = this%m
case default
  write(cad, *) d
  print*, 'ERROR (matrix/size_matrix) The requested dimension is invalid: '//trim(adjustl(cad))
  stop 1
end select
end function
  
!-----------------------------------------------------------------------
! get_sca: gets a scalar value
!-----------------------------------------------------------------------
function get_sca(this, i, j) result(val)
type(matrix), intent(in) :: this
integer,      intent(in) :: i, j
real(real64)             :: val
integer ::  k
character(255) :: cad

!check
if (.not. allocated(this%row) .or. .not. allocated(this%col) .or. .not. allocated(this%val)) then
  print*, 'ERROR (matrix/get_sca) Matrix is not allocated.'
  stop 1
end if
if (size(this%row,1) < 0) then !Assume that all arrays have the same size since the only way to change them is "set"
  write(cad, *) size(this%row, 1) 
  print*, 'ERROR (matrix/get_sca) The matrix arrays have an invalid size: '//trim(adjustl(cad))
  stop 1
end if

do k = 1, size(this%row,1)
  if (this%row(k) == i .and. this%col(k) == j) then
    val = this%val(k)
    return
  end if
end do
val = 0._real64
end function

!-----------------------------------------------------------------------
! get_col: get a sub-column
!-----------------------------------------------------------------------
function get_col(this, i, j) result(val)
type(matrix), intent(in)  :: this
integer,      intent(in)  :: i(:), j
real(real64)              :: val(size(i,1))

if (size(i,1) < 0) then
  print*, 'ERROR (matrix/get_col) Insufficient number of indices.'
  stop 1
end if
do k = 1, size(i,1)
  val(k) = get(this, i(k), j)
end do
end function


!-----------------------------------------------------------------------
! get_row: gets a sub-row
!-----------------------------------------------------------------------
function get_row(this, i, j) result(val)
type(matrix), intent(in)  :: this
integer,      intent(in)  :: i, j(:)
real(real64)              :: val(size(j,1))

if (size(j, 1) < 0) then
  print*, 'ERROR (matrix/get_row) Insufficient number of indices.'
  stop 1
end if
do k = 1, size(j,1)
  val(k) = get(this, i, j(k))
end do
end function

!-----------------------------------------------------------------------
! set_sca: sets a scalar value in the matrix
!-----------------------------------------------------------------------
subroutine set_sca(this, i, j, val)
type(matrix), intent(inout) :: this
integer,      intent(in)    :: i, j
real(real64), intent(in)    :: val
integer ::  k, s
integer, allocatable :: trow(:), tcol(:)
real(real64), allocatable :: tval(:)

!check
if (.not. allocated(this%row) .or. .not. allocated(this%col) .or. .not. allocated(this%val)) then
  call alloc(this, [i], [j], [val])
else
  s = size(this%row,1)
  do k = 1, s
    if (this%row(k) == i .and. this%col(k) == j) then
      this%val(k) = val
      return
    end if
  end do

  allocate(trow(s+1), tcol(s+1), tval(s+1))
  trow(1:s) =  this%row; trow(s+1) = i 
  tcol(1:s) =  this%col; tcol(s+1) = j
  tval(1:s) =  this%val; tval(s+1) = val
  call move_alloc(trow, this%row)
  call move_alloc(tcol, this%col)
  call move_alloc(tval, this%val)
  this%n = max(this%n, i)
  this%m = max(this%m, j)
end if
end subroutine

!-----------------------------------------------------------------------
! matmul: multiplies a matrix by a vector
!-----------------------------------------------------------------------
function matmul_matrix(this, x) result(y)
type(matrix), intent(in)  :: this
real(real64), intent(in)  :: x(:)
real(real64), allocatable :: y(:)
integer :: n, m, i, j, res
character(255) :: cad

!check
if (.not. allocated(this%row) .or. .not. allocated(this%col) .or. .not. allocated(this%val)) then
  print*, 'ERROR (matrix/matmul_matrix) Matrix is not allocated.'
  stop 1
end if
m = size(this, 2)
if (size(x, 1) /= m) then 
  print*, 'ERROR (matrix/matmul_matrix) The matrix is not compatible with x.'
  stop 1
end if
n = size(this, 1)
if (n < 0) then 
  write(cad, *) n
  print*, 'ERROR (matrix/matmul_matrix) The number of rows is invalid: '//trim(adjustl(cad))
  stop 1
end if
!allocate y
allocate(y(n), stat = res, errmsg = cad)
if (res /= 0) then
  print*, 'ERROR (matrix/matmul_matrix) Unable to allocate output variable.'
  stop 1
end if

do i = 1, n
  y(i) = dot_product(get(this, i, [(j, j = 1, m)]), x)
end do
end function


!-----------------------------------------------------------------------
! show: show matrix in row order
!-----------------------------------------------------------------------
subroutine show(this)
type(matrix), intent(in)  :: this
integer :: i, j
do i = 1, this%n
  print*, (get(this, i, j), j = 1, this%m)
end do
end subroutine

end module

!Module to manage data

module data_manage
use iso_fortran_env, only: real64
implicit none
contains

subroutine read_matrix(direccion,m,n,matriz)
!Lee los datos de un archivo y los guarda en la matriz.
!Hay que saber anticipadamente las dimensiones de la matriz

character (len=100), intent(in) :: direccion !La direccion del archivo que va a leer
integer, intent(in) :: m,n !Dimensiones de la matriz, m filas, n columnas
real(real64), intent(out) :: matriz(m,n) !Matriz donde se guardan los datos

integer :: error_status,i !Almacena 0 si no hay problemas, -1 si lee todo el documento, 1 si falla

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

subroutine display_matrix(m,n,matriz)
!Muestra por pantalla la matriz

integer, intent(in) :: m,n !Las dimensiones de la matriz (m=filas,n=columnas)
real(real64), intent(in) :: matriz(m,n) !Matriz de coeficientes reales

integer :: i

do i=1,m
	print*, matriz(i,:)
end do

end subroutine

end module data_manage

!module to manage data

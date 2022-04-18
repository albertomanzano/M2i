

!Las líneas tienen un tamaño máximo de 132 caracteres, si queremos ampliar 
!tenemos que introducir un &

program test_lu
use module_descomposition, only: lu, DisplayMatrix !Ojo nos estamos refiriendo al nombre del script
use module_resolution, only: remonte, descenso
use iso_fortran_env, only : real64
implicit none

real(real64) :: a(3,3), b(3)
real(real64), allocatable :: l(:,:), u(:,:), x(:), y(:)
print*, 'Programa test LU'

!Aquí la movida es que si le damos el vector sin más lo trabaja como enteros
a = reshape( real( [4,-2,1,20,-7,12,-8,13,17] ), &
[3,3],order=[2,1]) !Estamos diciendo que lo convierta en tres por tres y el orden para hacer la conversión
b = real([11,70,17]) !Indicamos que todos los valores valen uno

!Podiamos indicar que leyese con read*, a y cargar desde un .txt
call lu(a,l,u)
allocate(y,source=descenso(l,b))
!allocate(y,source=descenso(l,b)) Esta es la manera bien hecha, a mi me funciona porque uso el compilador GNU
x = remonte(u,y)

!Podíamos haber empleado el residuo usando
!residuo = norm2(b-matmul(a,x)) 
!En Matlab * es multiplicación matricial y .* es multiplicación componente a componente. Tanto norm2 como matmul son intrínsecas)

print*,x
end program

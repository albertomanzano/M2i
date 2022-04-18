program test_lu
!-----------------------------------------------------------------------
! Programa para testar los modulos de resolución de sistemas lineales por LU
!
! Licencia: Este codigo esta distribuido bajo la licencia GNU GPL
! Autor: Francisco Pena, fran(dot)pena(at)usc(dot)es
! Ultima actualizacion: 15/10/2018
!
! POSIBLES MEJORAS:
!   - comprobacion de que la descomposcion LU es posible
!   - implementacion del calculo del condicionamiento
!
! AVISO:
!   En Fortran 2003, si una función devuelve en su nombre un array alojable, se debe escribir:
!
!     integer, allocatable :: x(:)
!     allocate(x, source = fun(...))
!
!   gfortran permite ademas la forma no estandar:
!
!     integer, allocatable :: x(:)
!     x = fun(...) 
!-----------------------------------------------------------------------
use iso_Fortran_env, only: real64
use module_descomposicion, only: lu
use module_resolucion, only: remonte, descenso
implicit none
real(real64) :: a(3,3), b(3)
real(real64), allocatable :: l(:,:), u(:,:), x(:), y(:)

print *, 'Programa para testar los modulos de resolución de sistemas lineales por LU. Se resuelve el sistema:'
print *, ' / 9 2 1 \       / 1 \'
print *, ' | 4 9 4 | * X = | 1 |'
print *, ' \ 7 8 9 /       \ 1 /'
print*, ' '
a = reshape(real([9,2,1, 4,9,4, 7,8,9], real64), [3,3], order=[2,1]) !Iniciar con real64

b = 1._real64 !Iniciar con real64

call lu(a, l, u)
! ly = b; ux = y 
!x = remonte(u, descenso(l, b))
!Estandar de Fortran 2003:
allocate(y, source=descenso(l,b))
allocate(x, source=remonte(u,y))

print*, 'El residuo es: ', norm2(matmul(a,x)-b) !http://gcc.gnu.org/onlinedocs/gfortran/NORM2.html#NORM2

end program


module module_functions
!
!Module in which there are the functions of the base
!
!
! License: This code is distributed under license GNU GPL v3
! Authors: Francisco Pena Brage, Alberto Manzano Herrero, 
! Celia Navarro Montes de Oca, Jose Manuel Perales Fernández,
! Daniel Galera Nebot
! 
!       PUBLIC PROCEDURES:
!   seno:the base is composed of sine functions
!   polinomial:the functions of the base are polynomial
!   series:make a series based on the functions of the bases

use iso_fortran_env, only: real64
implicit none
contains
!--------------------------------------
!seno:the base is composed of sine functions 
!---------------------------------------

function seno(w,x) result(y)
	real(real64) :: w,x(:),y(size(x)) 
        y = sin(w*x)
end function
!--------------------------------------
!coseno:the base is composed of sine functions 
!---------------------------------------

function coseno(w,x) result(y)
	real(real64) :: w,x(:),y(size(x)) 
        y = cos(w*x)
end function
!--------------------------------------
!polinomial:the functions of the base are polynomial
!---------------------------------------
		   
function polinomial(w,x) result(y)
        real(real64) :: w,x(:), y(size(x))
        y = x**w
end function
!------------------------------------------
! series: build a series from other functions
!------------------------------------------

function series(f,w,x,c) result(y)
        real(real64) :: w(:),c(:),x(:),y(size(x))
        integer :: i
        interface 
                function f(w_f,x_f) result(y_f)
                use iso_fortran_env, only: real64
                        real(real64) :: w_f, x_f(:), y_f(size(x))
                end function
        end interface
        y = 0._real64
        do i=1,size(w)
                y = y + c(i)*f(w(i),x)
        end do
end function
end module

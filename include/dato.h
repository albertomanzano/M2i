// Class dato
//
//
// Authors: Alberto Manzano Herrero
// ATTRIBUTES:
//	fich_mesh: file containing the path for the list of points
//		   elements and boundary conditions in that specific
//		   order
// 
// PUBLIC FUNCTIONS:
//	
//	CLASS FUNCTIONS:
//		lee_datos: stores in a structure the paths
//
//
			       
#ifndef __DATO_
#define __DATO_

#include "header.h"

struct fich_mesh{
 
  string nodos;
  string conect;
  string boundary; 
  
};

class dato{
  public:
    //ATTRIBUTES
    fich_mesh mallado;

    // CLASS FUNCTIONS
    void leedatos();
  
};
#endif

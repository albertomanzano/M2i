
#include "header.h"
#include "dato.h"
#include <stdlib.h>

#include "point.h"

#include "pelfin.h"


#include "mesh.h"
#include "Eigen/Dense"
using Eigen::Matrix3d;
using Eigen::Vector3d;

int main() {
	dato datos;
	datos.leedatos();

	Mfinel <P1> malla; // Elijo EN ESTE MOMENTO el tipo de Elemento finito, P1
	malla.fill_mesh(datos); // lee los mallados desde fichero

	//malla.print_nodes(); // Imprimimos los nodos   
	//malla.print_elements(); // Imprimimos los elementos
	malla.construye_matriz_global();
        malla.boundary_conditions();	
	cout<<puntos_creados<<endl;
    	malla.solve();

}


                


#include "header.h"
#include "dato.h"

/*
 * Lectura de fichero de configuracion de la simulacion
 * En este caso solo leemos los ficheros que almacenan la malla
 */
void dato::leedatos(){
   string fichero = "datos.dat";
   ifstream fichdatos (fichero);
   if (fichdatos.is_open())
  {
      fichdatos>>this->mallado.nodos;
      cout<<"Fiechero de nodos: "<<this->mallado.nodos<<endl;
      fichdatos>>this->mallado.conect;
      fichdatos>>this->mallado.boundary;	    
  }
  else{
	cout<<"ERROR: No se ha podido abrir el fichero: "<<fichero<<endl;
  }
}




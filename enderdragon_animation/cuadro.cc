#include "aux.h"
#include "malla.h"
#include "cuadro.h"

Cuadro::Cuadro(float lado){
  v.clear();

  v.push_back( Tupla3f(-lado,-lado,0.0));
  v.push_back( Tupla3f(lado,-lado,0.0));
  v.push_back( Tupla3f(-lado,lado,0.0));
  v.push_back( Tupla3f(lado,lado,0.0));

  f.clear();
  f.push_back( Tupla3i(0,1,2));
  f.push_back( Tupla3i(1,3,2));
}
void Cuadro::asignarTextura(char *nombreImagen){
  textura = new Textura(nombreImagen);
  ct.clear();
  ct.push_back(Tupla2f(1.0,0.0));
  ct.push_back(Tupla2f(0.0,0.0));
  ct.push_back(Tupla2f(1.0,1.0));
  ct.push_back(Tupla2f(0.0,1.0));

}

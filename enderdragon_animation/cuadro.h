#ifndef CUADRO_H_INCLUDED
#define CUADRO_H_INCLUDED

#include "aux.h"

class Cuadro: public Malla3D
{
  public:
    Cuadro(float lado) ;
    void asignarTextura(char *nombreImagen) ;
} ;

#endif

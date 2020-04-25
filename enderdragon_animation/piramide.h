// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: piramide.h

//
// #############################################################################

#ifndef PIRAMIDE_H_INCLUDED
#define PIRAMIDE_H_INCLUDED

#include "aux.h"

// *****************************************************************************
//
// clases derivadas de Malla3D (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************
// Tetraedro con centro en el origen 

class Piramide: public Malla3D
{
   public:
      Piramide(float lado);

} ;




#endif

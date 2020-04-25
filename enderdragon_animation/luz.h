#ifndef _LUZ_H
#define _LUZ_H
#include "aux.h"

class Luz
{
	protected:
		Tupla4f posicion;
		GLenum id;
		Tupla4f colorAmbiente;
		Tupla4f colorDifuso;
		Tupla4f colorEspecular;
	public:
		void activar();
};

#endif


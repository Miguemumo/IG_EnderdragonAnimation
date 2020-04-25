#ifndef _MATERIAL_H
#define _MATERIAL_H

#include "aux.h"

class Material
{
	private:
		Tupla4f ambiente;
		Tupla4f especular;
		Tupla4f difuso;
		float brillo;

	public:
		void aplicar();
		Material();
		Material(Tupla4f ambiente, Tupla4f especular, Tupla4f difuso, float brillo);




};

#endif

#ifndef _LUZDIRECCIONAL_H
#define _LUZDIRECCIONAL_H
#include "aux.h"
#include "luz.h"

class LuzDireccional : public Luz
{
	protected:
		float alpha;
		float beta;
		float radio;
	public:
		//Inicializar la fuente de luz
		LuzDireccional( Tupla3f direccion, GLenum idLuzOpenGL, Tupla4f colorAmbiente, Tupla4f colorEspecular, Tupla4f colorDifuso);

		//Cambiar angulo
		void variarAnguloAlpha (float incremento);
		void variarAnguloBeta (float incremento);
		void calculaPosicion();
};
#endif

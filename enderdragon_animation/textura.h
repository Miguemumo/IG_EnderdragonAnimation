#ifndef TEXTURA_H_INCLUDED
#define TEXTURA_H_INCLUDED

#include "aux.h"

class Textura
{
	public:
		GLuint textura_id = 0;
		std::vector<unsigned char > data;
		int width,height;

		Textura(char * archivo);
		void activar();

} ;


#endif

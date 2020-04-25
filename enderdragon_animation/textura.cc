#include "textura.h"
#include "jpg_imagen.hpp"
#include <stdlib.h>
#include <GL/glew.h>

Textura::Textura(char * archivo){
	std::cout << "Cargando la textura " << archivo << "\n";

	jpg::Imagen * pimg = NULL;
	pimg = new jpg::Imagen(archivo);
	unsigned char * leido;


	width = pimg->tamX();
	height = pimg->tamY();

	for (int i=0; i< height; i++)
		for (int j=0; j<width; j++){

			leido = pimg->leerPixel(j, height -i -1);

			data.push_back(*leido);
			leido++;
			data.push_back(*leido);
			leido++;
			data.push_back(*leido);
		}

}

void Textura::activar(){
	if (textura_id == 0){
		glGenTextures( 1, &textura_id);
		glBindTexture( GL_TEXTURE_2D, textura_id );
		gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGB, width,
					height, GL_RGB, GL_UNSIGNED_BYTE, data.data());
	}else
		glBindTexture( GL_TEXTURE_2D, textura_id );


	/*glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glLightModeli( GL_LIGHT_MODEL_COLOR_CONTROL, GL_SINGLE_COLOR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);*/


}

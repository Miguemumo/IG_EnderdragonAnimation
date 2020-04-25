#ifndef DRAGON_DISPARO_H_INCLUDED
#define DRAGON_DISPARO_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "ply_reader.h"
#include "cubo.h"


class Dragon_disparo : public Malla3D
{
	public:
	Cubo * disparoi  = nullptr;
	Cubo * disparoc  = nullptr;
	Cubo * disparod  = nullptr;

	float desplazamientox = 0,desplazamientoy = 0;

	Dragon_disparo();
	void draw(bool inmediato, GLenum tipo, int color);
	void draw_ajedrez(bool inmediato) ;
	void setMaterial(Material * mat) ;
	void modificarDisparo(float valor) ;

} ;




#endif

#ifndef DRAGON_H_INCLUDED
#define DRAGON_H_INCLUDED

#include "aux.h"
#include "dragon_cuerpo.h"
#include "dragon_cuello.h"
#include "dragon_cabeza.h"
#include "dragon_cola.h"
#include "dragon_ala.h"
#include "dragon_disparo.h"




class Dragon
{
	public:

	float giro_cola, giro_ala, desplazamientoy, desplazamientoz, rotacionx;
	bool disparo_listo = false;

	Dragon_cuerpo * cuerpo = nullptr ;
	Dragon_cuello * cuello = nullptr ;
	Dragon_cabeza * cabeza = nullptr ;
	Dragon_cola * cola = nullptr ;
	Dragon_ala * ala = nullptr ;
	Dragon_disparo * disparo = nullptr;

	Dragon();

	void draw(bool inmediato, GLenum tipo, int color);
	void draw_ajedrez(bool inmediato) ;
	void setMaterial(Material * mat, Material * mat_disparo);

	void modificarGiroCola(float valor);
	void modificarGiroAlas(float valor);
	void modificarDesplazamiento(float valory, float valorz);
	void modificarRotacionx(float valor) ;
	void modificarDisparo(float valor) ;
	void is_disparo(bool estado) ;



} ;




#endif

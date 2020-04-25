#include "dragon_disparo.h"
#include "ply_reader.h"

Dragon_disparo::Dragon_disparo(){

	disparoi  = new Cubo(20);
	disparoc  = new Cubo(20);
	disparod  = new Cubo(20);
	desplazamientox = desplazamientoy = 0;

}

void Dragon_disparo::draw(bool inmediato, GLenum tipo, int color){
		glPushMatrix();
			glTranslatef(-desplazamientox, -desplazamientoy, 0.0);
			disparoi->draw(inmediato,tipo,color,false);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.0, -desplazamientoy, 0.0);
			disparoc->draw(inmediato,tipo,color,false);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(desplazamientox, -desplazamientoy, 0.0);
			disparod->draw(inmediato,tipo,color,false);
		glPopMatrix();
}

void Dragon_disparo::draw_ajedrez(bool inmediato){
		glPushMatrix();
			glTranslatef(-desplazamientox, -desplazamientoy, 0.0);
			disparoi->draw_ajedrez(inmediato);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.0, -desplazamientoy, 0.0);
			disparoc->draw_ajedrez(inmediato);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(desplazamientox, -desplazamientoy, 0.0);
			disparod->draw_ajedrez(inmediato);
		glPopMatrix();
}

void Dragon_disparo::setMaterial(Material * mat){
	disparoi->setMaterial(mat);
	disparoc->setMaterial(mat);
	disparod->setMaterial(mat);
}

void Dragon_disparo::modificarDisparo(float valor){
	desplazamientox += valor;
	desplazamientoy += valor;
}

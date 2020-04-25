#include "luzdireccional.h"
#include "aux.h"

LuzDireccional::LuzDireccional( Tupla3f direccion, GLenum idLuzOpenGL, Tupla4f colorAmbiente, Tupla4f colorEspecular, Tupla4f colorDifuso){
	/*alpha = direccion(0);
	beta = direccion(1);

	calculaPosicion();*/
	
	posicion = Tupla4f(direccion(0),direccion(1),direccion(2),0.0);
	
	alpha = atan( sqrt(direccion(0)*direccion(0) + direccion(1)*direccion(1) ) / direccion(2) );
	beta = atan( direccion(1)/direccion(0) );
	radio = sqrt( direccion(0)*direccion(0)+direccion(1)*direccion(1)+direccion(2)*direccion(2) );
	
	id = idLuzOpenGL;
	this->colorAmbiente = colorAmbiente;
	this->colorDifuso = colorDifuso;
	this->colorEspecular = colorEspecular;
}

void LuzDireccional::variarAnguloAlpha (float incremento)
{
	if (alpha+incremento >= 0 && alpha+incremento <= 360){
		alpha += incremento;
		calculaPosicion();
	}
}

void LuzDireccional::variarAnguloBeta (float incremento)
{
	if (beta+incremento >= -90 && beta+incremento <= 90){
		beta += incremento;
		calculaPosicion();
	}
}

void LuzDireccional::calculaPosicion(){
	float x,y,z;
	x = radio*sin(alpha)*cos(beta);
	y = radio*sin(alpha)*sin(beta);
	z = radio*cos(alpha);

	posicion = Tupla4f(x, y, z, 0.0);
}

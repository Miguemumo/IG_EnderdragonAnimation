#include "aux.h"
#include "malla.h"
#include "piramide.h"

Piramide::Piramide(float lado)
{

   // inicializar la tabla de vértices
	v.resize(5);
	v[0]= Tupla3f (lado,0,-lado);
	v[1]= Tupla3f (lado,0,lado);
	v[2]= Tupla3f (-lado,0,lado);
	v[3]= Tupla3f (-lado,0,-lado);
	v[4] = Tupla3f ( 0, sqrt(lado*lado+lado*lado),0);

   // inicializar la tabla de caras o triángulos:

	f.resize(6);
	f[0]= Tupla3i (0,1,2);
	f[1]= Tupla3i (0,2,3);
	f[2]= Tupla3i (0,4,1);
	f[3]= Tupla3i (0,3,4);
	f[4]= Tupla3i (3,2,4);
	f[5]= Tupla3i (2,1,4);

}

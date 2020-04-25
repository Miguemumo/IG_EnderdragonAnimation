#include "aux.h"
#include "malla.h"
#include "cubo.h"

Cubo::Cubo(float lado)
{

   // inicializar la tabla de vértices
	v.resize(8);
	v[0] = Tupla3f (0,0,0);
	v[1] = Tupla3f (0,0,lado);
	v[2] = Tupla3f (0,lado,0);
	v[3] = Tupla3f (0,lado,lado);
	v[4] = Tupla3f (lado,0,0);
	v[5] = Tupla3f (lado,0,lado);
	v[6] = Tupla3f (lado,lado,0);
	v[7] = Tupla3f (lado,lado,lado);

  // inicializar la tabla de caras o triángulos:

	f.resize(12);
	f[5] = Tupla3i (7,1,5);
	f[4] = Tupla3i (7,3,1);
	f[11] = Tupla3i (0,2,4);
	f[10] = Tupla3i (2,6,4);
	f[6] = Tupla3i (7,5,6);
	f[7] = Tupla3i (5,4,6);
	f[3] = Tupla3i (0,1,3);
	f[2] = Tupla3i (0,3,2);
	f[0] = Tupla3i (2,3,6);
	f[1] = Tupla3i (3,7,6);
	f[9] = Tupla3i (5,0,4);
	f[8] = Tupla3i (5,1,0);

}


void Cubo::asignarTextura(char *nombreImagen){

	/*v.push_back(v[1]);
	v.push_back(v[5]);
	v.push_back(v[3]);
	v.push_back(v[7]);
	f.push_back(Tupla3i(8,9,10));
	f.push_back(Tupla3i(10,9,11));

	v.push_back(v[0]);//12
	v.push_back(v[4]);
	v.push_back(v[2]);
	v.push_back(v[6]);
	f.push_back(Tupla3i(12,13,15));
	f.push_back(Tupla3i(12,15,14));

	v.push_back(v[3]);//16
	v.push_back(v[7]);
	v.push_back(v[2]);
	v.push_back(v[6]);
	f.push_back(Tupla3i(16,17,19));
	f.push_back(Tupla3i(16,19,18));

	v.push_back(v[0]);//20
	v.push_back(v[4]);
	v.push_back(v[1]);
	v.push_back(v[5]);
	f.push_back(Tupla3i(22,23,21));
	f.push_back(Tupla3i(22,21,20));*/

	ct.clear();
		textura = new Textura(nombreImagen);
		ct.push_back(Tupla2f(0,0));
		ct.push_back(Tupla2f(0,0.5));
		ct.push_back(Tupla2f(0.5,0));
		ct.push_back(Tupla2f(0.5,0.5));
		ct.push_back(Tupla2f(0.5,0.5));
		ct.push_back(Tupla2f(0.5,1));
		ct.push_back(Tupla2f(1,0.5));
		ct.push_back(Tupla2f(1,1));
		/*ct.push_back(Tupla2f(0,0));
		ct.push_back(Tupla2f(0,1));
		ct.push_back(Tupla2f(1,0));
		ct.push_back(Tupla2f(1,1));
		ct.push_back(Tupla2f(0,0));
		ct.push_back(Tupla2f(0,1));
		ct.push_back(Tupla2f(1,0));
		ct.push_back(Tupla2f(1,1));
		ct.push_back(Tupla2f(0,0));
		ct.push_back(Tupla2f(0,1));
		ct.push_back(Tupla2f(1,0));
		ct.push_back(Tupla2f(1,1));
		ct.push_back(Tupla2f(0,0));
		ct.push_back(Tupla2f(0,1));
		ct.push_back(Tupla2f(1,0));
		ct.push_back(Tupla2f(1,1));*/
	//}
}

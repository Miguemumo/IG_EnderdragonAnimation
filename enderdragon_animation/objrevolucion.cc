#include "aux.h"
#include "objrevolucion.h"
#include <cmath>
#include "ply_reader.h"




// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************


// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

ObjRevolucion::ObjRevolucion() {}

ObjRevolucion::ObjRevolucion(const std::string & archivo, int num_instancias, bool tapas) {
    ply::read_vertices(archivo,aux);
    this->num_instancias = num_instancias;
    this->tapas = tapas;


    crearMalla(aux,num_instancias);

    /*tapa_inferior = tapa_inf;
    if (tapa_inf){
        this->crearTapaInferior();
    }

    tapa_superior = tapa_sup;
    if (tapa_sup){
        this->crearTapaSuperior();
    }*/
}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)

void ObjRevolucion::crearTapaSuperior(){

    for (int i=0; i<num_instancias; i++){
        f.push_back( Tupla3i(v.size()-2,aux.size()*(i+1)-1,aux.size()*(((i+1)%num_instancias)+1)-1)) ;
    }

}

void ObjRevolucion::crearTapaInferior(){

    for (int i=0; i<num_instancias; i++){
        f.push_back( Tupla3i(v.size()-1,((i+1)%num_instancias)*aux.size(),i*aux.size()));
    }

}


ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool tapas) {
    crearMalla(archivo,num_instancias);
    this->tapas = tapas;
    if (tapas){
        this->crearTapaInferior();
        this->crearTapaSuperior();
    }
}

/*void ObjRevolucion::ponerTapas(int num_instancias, bool tapa_sup, bool tapa_inf){

    if (tapa_inf){
        v.push_back( Tupla3f (0,v[0](1),0));
        std::cout << v.size() << "\n";
        for (int i=0; i<num_instancias; i++){
            f.push_back( Tupla3i(v.size()-1,(i+1)*aux.size(),i*aux.size()));
        }
    }

    if (tapa_sup){
        v.push_back( Tupla3f (0,v[v.size()-2](1),0));
        std::cout << f.size() << "\n";
        for (int i=1; i<num_instancias; i++){

            f.push_back( Tupla3i(v.size()-1,i*aux.size()-1,(i+1)*aux.size()-1));
        }
    }


}*/

void ObjRevolucion::crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias) {
    float alpha;
    float eje_x, eje_z;
    bool primero=false, ultimo=false;
	Tupla3f primer_punto;
	Tupla3f ultimo_punto;

	primer_punto = perfil_original[0];
	if (primer_punto(0)==0 && primer_punto(2)==0){
		perfil_original.erase(perfil_original.begin());
		primero = true;
	}

	ultimo_punto = perfil_original[perfil_original.size()-1];
	if (ultimo_punto(0)==0 && ultimo_punto(2)==0){
		perfil_original.pop_back();
		ultimo = true;
	}

    for (int i=0; i<num_instancias; i++) {
        for (int j=0; j<perfil_original.size(); j++){
            alpha = 2 * M_PI * i /num_instancias;
            eje_x = cos(alpha) * perfil_original[j](0) + sin(alpha) * perfil_original[j](2);
            eje_z = - sin(alpha) * perfil_original[j](0) + cos(alpha) * perfil_original[j](2);

            v.push_back(Tupla3f (eje_x,perfil_original[j](1),eje_z));
        }
    }

    int a,b;
    for (int i=0; i<num_instancias; i++) {
        for (int j=0; j<perfil_original.size()-1;j++) {
            a = perfil_original.size()*i+j;
            b = perfil_original.size()*((i+1)%num_instancias) + j;

            f.push_back(Tupla3i (a,b,b+1));
            f.push_back(Tupla3i (a,b+1,a+1));
        }
    }

    figura_sin_tapas = f.size();

    if (ultimo)
		v.push_back(ultimo_punto);
	else
		v.push_back( Tupla3f (0,v[v.size()-1](1),0));

    if (primero)
		v.push_back(primer_punto);
	else
                v.push_back( Tupla3f (0,v[0](1),0));

        if (tapas){
        this->crearTapaSuperior();
		      this->crearTapaInferior();
    }







}

void ObjRevolucion::draw_ModoInmediato(bool seleccion)
{

  glEnableClientState( GL_VERTEX_ARRAY );
  glVertexPointer( 3, GL_FLOAT, 0, v.data() ) ;


  if (glIsEnabled(GL_LIGHTING)&& !seleccion){
    if (nv.size() == 0)
      calcular_normales();
    glNormalPointer( GL_FLOAT, 0, nv.data() );
    glEnableClientState( GL_NORMAL_ARRAY );
  }

  if (ct.size() != 0 && !seleccion){
    glEnable(GL_TEXTURE_2D);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY_EXT);
    glTexCoordPointer( 2,GL_FLOAT, 0, ct.data());
    textura->activar();
  }

  glPolygonMode( GL_FRONT, visualizacion);
  glPointSize(5.0);
  glEnableClientState(GL_COLOR_ARRAY);
  glColorPointer(3,GL_FLOAT,0, color_actual.data() );
  if (tapas){
    glDrawElements( GL_TRIANGLES, f.size()*3, GL_UNSIGNED_INT, f.data() );
  }else{
    glDrawElements( GL_TRIANGLES, figura_sin_tapas*3, GL_UNSIGNED_INT, f.data() );
  }

  glDisableClientState( GL_VERTEX_ARRAY );

  if (glIsEnabled(GL_LIGHTING)&& !seleccion){
    glDisableClientState( GL_NORMAL_ARRAY );
  }

  if (ct.size() != 0 && !seleccion){
    glDisableClientState( GL_TEXTURE_COORD_ARRAY_EXT );
    glDisable(GL_TEXTURE_2D) ;
  }

}

void ObjRevolucion::draw(bool inmediato, GLenum tipo, int color,bool seleccion)
{
   visualizacion = tipo;
   inicializa_colores();
   if (seleccionado && !seleccion){
     color_actual = color_seleccion;
   }else{
   switch (color){
	case 0:
		color_actual=c1;
		break;
	case 1:
		color_actual=c2;
		break;
	case 2:
		color_actual=c3;
		break;
  case 3:
  	color_actual=orange;
  	break;
  case 4:
    color_actual=cyan;
    break;
  }
}

if (seleccionado){
  material_seleccionado->aplicar();
}else{
  m->aplicar();
}

   if (inmediato){
	draw_ModoInmediato(seleccion);
   }else{
	draw_ModoDiferido();
   }
}

void ObjRevolucion::setTapas(bool tapas){
  this->tapas = tapas;
}
/*
void ObjRevolucion::cambioTapaSuperior(){
    if (tapa_superior){

    }else{
        this->crearTapaSuperior();
    }
}

void ObjRevolucion::cambioTapaInferior(){
    if (tapa_inferior){

    }else{
        this->crearTapaInferior();
    }
}*/

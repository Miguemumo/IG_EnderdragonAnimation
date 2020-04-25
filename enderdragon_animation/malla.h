// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Malla3D.h
// -- declaraciones de clase Malla3D (mallas indexadas) y derivados
//
// #############################################################################

#ifndef MALLA3D_H_INCLUDED
#define MALLA3D_H_INCLUDED

#include "aux.h"
#include "material.h"
#include "textura.h"

// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************

class Malla3D
{
   public:
	unsigned id_vbo_ver = 0;
	unsigned id_vbo_tri = 0;
  unsigned id_vbo_nor = 0;
  unsigned id_vbo_col = 0;
	Malla3D();
   // dibuja el objeto en modo inmediato
   void draw_ModoInmediato(bool seleccion);

   // dibuja el objeto en modo diferido (usando VBOs)
   void draw_ModoDiferido();

   // función que redibuja el objeto
   // está función llama a 'draw_ModoInmediato' (modo inmediato)
   // o bien a 'draw_ModoDiferido' (modo diferido, VBOs)
   void draw(bool inmediato, GLenum tipo, int color, bool seleccion) ;
   void draw_ajedrez(bool inmediato) ;
   void inicializa_colores() ;

   void setForma(GLenum vista) ;

   void setMaterial(Material * mat);
   void setMaterialSeleccionado(Material * mat);
   void asignarTextura(char *nombreImagen);

   void asignaCentro(float cord_centro[]);

   Tupla3f getCentro();
   void setSeleccionado(bool seleccionado);

   //Funcion VBO
   GLuint CrearVBO ( GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid * puntero_ram) ;

   protected:

   GLenum visualizacion;

   void calcular_normales() ; // calcula tabla de normales de vértices (práctica 3)

   std::vector<Tupla3f> v ;   // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
   std::vector<Tupla3i> f ; // una terna de 3 enteros por cada cara o triángulo
   std::vector<Tupla3f> nv ;
   std::vector<Tupla3f> c1 ; //tabla de colores
   std::vector<Tupla3f> c2 ;
   std::vector<Tupla3f> c3 ;
   std::vector<Tupla3f> orange ;
   std::vector<Tupla3f> cyan ;
   std::vector<Tupla3f> color_seleccion;
   std::vector<Tupla3f> color_actual;

   bool seleccionado = false;

   Tupla3f centro = {0,0,0};

   //Gestion de texturas
   std::vector<Tupla2f> ct ;
   Textura * textura = nullptr;


   Material * m;
   Material * material_seleccionado;

} ;


#endif

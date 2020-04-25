#ifndef _ESCENA_H
#define _ESCENA_H

#include "ejes.h"
#include "malla.h"
#include "cubo.h"
#include "cuadro.h"
#include "tetraedro.h"
#include "piramide.h"
#include "objply.h"
#include "objrevolucion.h"
#include "cono.h"
#include "cilindro.h"
#include "esfera.h"
#include "dragon.h"
#include "luz.h"
#include "luzposicional.h"
#include "luzdireccional.h"
#include "camara.h"

typedef enum {NADA, SELOBJETO,SELVISUALIZACION,SELDIBUJADO, SELUCES, GRADOSLIBERTAD, ANIMACION, CAMARA, SELECCIONAR} menu;
typedef enum {CUBO, TETRAEDRO} menu_figura;

class Escena
{

   private:



 // ** PARÁMETROS DE LA CÁMARA (PROVISIONAL)

       // variables que definen la posicion de la camara en coordenadas polares
   GLfloat Observer_distance;
   GLfloat Observer_angle_x;
   GLfloat Observer_angle_y;

   // variables que controlan la ventana y la transformacion de perspectiva
   GLfloat Width, Height, Front_plane, Back_plane;

    // Transformación de cámara
	void change_projection( const float ratio_xy );
	void change_observer();



   void clear_window();

//SELECTORES DE MENU
   menu modoMenu=NADA;
   menu_figura figura;
//SELECTOR DE MODO DE DIBUJADO
   bool inmediato = true;
//SELECTRO DE FORMA DE DIBUJADO
	bool ajedrez = false;
	bool luces = false;
	bool is_luz0 = false, is_luz1 = false;
	bool giro0=false, giro1=false, desplazamiento0 = false;
	bool variar_alfa = true;

   std::vector<bool> tipo_dibujado;
   GLenum tipo_dibujado_actual;
   // Objetos de la escena
   Ejes ejes;

	//Ambiente
   Cubo * suelo = nullptr ;
   Cubo * casa = nullptr ;
   Piramide * tejado= nullptr ;


   ObjPLY * hormiga = nullptr ;
   ObjPLY * montania = nullptr ;
   ObjRevolucion * peon_blanco = nullptr;
   ObjRevolucion * peon_negro = nullptr;
   Cono * con = nullptr;
   Esfera * esf = nullptr;
   Cilindro * cil = nullptr;
   Dragon * enderdragon;
   Cuadro * pintura = nullptr;
   Cubo * sol = nullptr;

   //Luces
   LuzPosicional * luz0 = nullptr;
   LuzDireccional * luz1 = nullptr;

   //Materiales
   Material * m0 = nullptr;
   Material * m1 = nullptr;
   Material * m2 = nullptr;
   Material * sol_material = nullptr;
   Material * pared_casa = nullptr;
   Material * suelo_tierra = nullptr;
   Material * suelo_tierra2 = nullptr;
   Material * disparo = nullptr;
   Material * oro = nullptr;

   float incremento_luz=-700;
   //Variables para la animacion del dragon
   bool activar_animacion = false;
   bool lanzar_disparo = false;
   bool tapas = true;
   int num_fase = 0;

   float incremento_alas = 0.9;
   int fase_alas = 0;

   float cola_speed = 0.5;
   float alas_speed = 0.5;
   float desplazamiento_speed = 5.5;

   float incremento_desplazamiento = 0.9;
   float fase_desplazamientoy = 1;
   float fase_desplazamientoz = 1;

   float incremento_giro = 0.3;

   size_t tope1 = 300, tope2 = 0, limtope2 = 30, incremento1 = 0, incremento2 = 0;

   std::vector<Camara> camaras;
   int camara_actual = 0;
   bool camara_raton = false;
   int x_anterior = 0, y_anterior = 0;
   bool zoom_raton_up = false, zoom_raton_down = false;

   Tupla3f centro_vista = Tupla3f(0,0,0);
   bool seleccion = false;
   bool fperson_camara = false;

   public:

    Escena();
	void inicializar( int UI_window_width, int UI_window_height );
	void redimensionar( int newWidth, int newHeight ) ;

	// Dibujar
	void dibujar() ;
  void dibujar_seleccion() ;

	// Interacción con la escena
	bool teclaPulsada( unsigned char Tecla1, int x, int y ) ;
	void teclaEspecial( int Tecla1, int x, int y );
	void animarModeloJerarquico();

  void clickRaton(int boton, int estado, int x, int y);
  void ratonMovido(int x, int y);

  void pintaMenu(menu tipo);

};
#endif



#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....

//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

Escena::Escena()
{
    Front_plane       = 50.0;
    Back_plane        = 2000.0;
    Observer_distance = 4*Front_plane;
    Observer_angle_x  = 0.0 ;
    Observer_angle_y  = 0.0 ;

    ejes.changeAxisSize( 5000 );
    tipo_dibujado.resize(3);

    // crear los objetos de la escena....
	suelo = new Cubo(50);
	casa = new Cubo(50);
    tejado = new Piramide(25);
    hormiga = new ObjPLY("plys/ant.ply");
    montania = new ObjPLY("plys/montania.ply");
    peon_blanco = new ObjRevolucion("plys/peon.ply", 20, true);
    peon_negro = new ObjRevolucion("plys/peon.ply", 20, true);
    enderdragon = new Dragon();
    //esf = new Esfera(20,20,1);
    //con = new Cono(10,5,1);
    cil = new Cilindro(20,20,3,2);
    pintura = new Cuadro(500);
    sol = new Cubo(20);

	//Crear las luces
    luz0 = new LuzPosicional( Tupla3f(0.0, 0.0, 0.0), GL_LIGHT0, Tupla4f(1.0, 1.0, 1.0, 1.0), Tupla4f(1.0, 1.0, 1.0, 1.0), Tupla4f(1.0, 1.0, 1.0, 1.0));
    luz1 = new LuzDireccional( Tupla3f(100.0, 100.0, 100.0), GL_LIGHT1, Tupla4f(0.2, 1.0, 0.2, 1.0), Tupla4f(0.2, 1.0, 0.2, 1.0), Tupla4f(0.2, 1.0, 0.2, 1.0));

	//Crea los materiales
    m0 = new Material(Tupla4f(0.3,0.3,0.3,1.0),Tupla4f(1.0,1.0,1.0,1.0),Tupla4f(1.0,1.0,1.0,1.0), 10.0);
    m1 = new Material(Tupla4f(0.0,0.0,0.0,1.0),Tupla4f(0.0,0.0,0.0,1.0),Tupla4f(0.0,0.0,0.0,1.0), 10.0);
    m2 = new Material(Tupla4f(0.4,0.0,0.0,1.0),Tupla4f(1.0,0.0,0.0,1.0),Tupla4f(1.0,0.0,0.0,1.0), 10.0);
    sol_material = new Material(Tupla4f(0.24725,0.1995,0.0745,1.0),Tupla4f(0.7516,0.60648,0.22648,1.0),Tupla4f(0.628281,0.555802,0.366065,1.0), 10.0);
	pared_casa = new Material(Tupla4f(0.6,0.6,0.6,1.0),Tupla4f(1.0,1.0,1.0,1.0),Tupla4f(1.0,1.0,1.0,1.0),10.0);
	suelo_tierra = new Material(Tupla4f(0.40, 0.26, 0.13,1.0),Tupla4f(0.40, 0.26, 0.13,1.0),Tupla4f(0.40, 0.26, 0.13,1.0),10.0);
	suelo_tierra2 = new Material(Tupla4f(1.0,1.0,1.0,1.0),Tupla4f(1.0,1.0,1.0,1.0),Tupla4f(1.0,1.0,1.0,1.0),100.0);
	disparo = new Material(Tupla4f(0.0,0.0,1.0,1.0),Tupla4f(0.0,0.0,1.0,1.0),Tupla4f(0.0,0.0,1.0,1.0), 50.0);
  oro = new Material(Tupla4f(0.24725,0.1995,0.0745,1.0),Tupla4f(0.75164,0.60648,0.22648,1.0),Tupla4f(0.628281,0.555802,0.366065,1.0), 10.0);


	suelo->setMaterial(suelo_tierra);
    casa->setMaterial(pared_casa);
    tejado->setMaterial(m2);
    pintura ->setMaterial(suelo_tierra2);
    peon_blanco->setMaterial(m0);
    peon_negro->setMaterial(m1);
	hormiga->setMaterial(m2);
    //esf->setMaterial(m2);
	cil->setMaterial(m2);
	//con -> setMaterial(m0);
    enderdragon->setMaterial(m0, disparo);
    sol -> setMaterial(sol_material);

    cil->setMaterialSeleccionado(oro);
    peon_blanco->setMaterialSeleccionado(oro);

    pintura -> asignarTextura("fondo.jpg");
    casa -> asignarTextura("pared.jpg");
    suelo -> asignarTextura("suelo.jpg");
    cil -> asignarTextura("cilindro.jpg");

    camaras.push_back(Camara(Tupla3f(500.0,200.0,500.0),Tupla3f(-30.0,70.0,-30.0),Tupla3f(0.0,1.0,0.0),0,-400.0,400.0,50.0,2000.0,400.0,-400.0));
    camaras.push_back(Camara(Tupla3f(0.0,150.0,200.0),Tupla3f(0.0,70.0,0.0),Tupla3f(0.0,1.0,0.0),1,-500.0,500.0,50.0,2000.0,400.0,-400.0));
    camaras.push_back(Camara(Tupla3f(-500.0,200.0,500.0),Tupla3f(-30.0,70.0,-100.0),Tupla3f(0.0,1.0,0.0),0,-400.0,400.0,50.0,2000.0,400.0,-400.0));


}

//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana, por
// tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//**************************************************************************
void Escena::inicializar( int UI_window_width, int UI_window_height )
{
	glEnable(GL_CULL_FACE);
	glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);


	glClearColor( 1.0, 1.0, 1.0, 1.0 );// se indica cual sera el color para limpiar la ventana	(r,v,a,al)

	glEnable( GL_DEPTH_TEST );	// se habilita el z-bufer


	Width  = UI_window_width/10;
	Height = UI_window_height/10;

  change_projection( float(UI_window_width)/float(UI_window_height) );
	glViewport( 0, 0, UI_window_width, UI_window_height );
  pintaMenu(modoMenu);
}



// **************************************************************************
//
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
//
// **************************************************************************

void Escena::animarModeloJerarquico(){
	if (activar_animacion){
		switch (num_fase){
			case 0:
				enderdragon->modificarDesplazamiento(incremento_desplazamiento, incremento_desplazamiento);
				enderdragon->modificarRotacionx(-incremento_giro);
				incremento1++;
				if (incremento1 > tope1){
					num_fase = 1;
					incremento1 = 0;
				}
				break;
			case 1:
				enderdragon->modificarDesplazamiento(incremento_desplazamiento, -incremento_desplazamiento);
				enderdragon->modificarRotacionx(-incremento_giro);
				incremento1++;
				if (incremento1 > tope1){
					num_fase = 2;
					incremento1 = 0;
				}
				break;
			case 2:
				enderdragon->modificarDesplazamiento(-incremento_desplazamiento, -incremento_desplazamiento);
				enderdragon->modificarRotacionx(-incremento_giro);
				incremento1++;
				if (incremento1 > tope1){
					num_fase = 3;
					incremento1 = 0;
					enderdragon->is_disparo(true);
				}

				break;
			case 3:
				enderdragon->modificarDesplazamiento(-incremento_desplazamiento,incremento_desplazamiento);
				enderdragon->modificarRotacionx(-incremento_giro);
				incremento1++;
				if (incremento1 > tope1){
					num_fase = 0;
					incremento1 = 0;
					enderdragon->is_disparo(false);
				}
				break;
		}

		switch(fase_alas){
			case 0:
				enderdragon->modificarGiroAlas(incremento_alas);
				enderdragon->modificarGiroCola(incremento_alas);
				tope2++;
				if (tope2 > limtope2){
					limtope2 = 60;
					fase_alas = 1;
					tope2 = 0;
				}
				break;
			case 1:
				enderdragon->modificarGiroAlas(-incremento_alas);
				enderdragon->modificarGiroCola(-incremento_alas);
				tope2++;
				if (tope2 > 60){
					fase_alas = 0;
					tope2 = 0;
				}
				break;
		}

		enderdragon->modificarDisparo(0.3);

	}
}

void Escena::dibujar()
{
  glDisable(GL_LIGHT0);
  glDisable(GL_LIGHT1);
	glDisable(GL_LIGHTING);

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
  glClear(GL_DEPTH_BUFFER);
	change_observer();
  ejes.draw();

  if (luces)
		glEnable(GL_LIGHTING);

  if (is_luz0){
    glPushMatrix();
      glTranslatef(incremento_luz,300,0);
        luz0->activar();
      if (ajedrez)
        sol->draw_ajedrez(inmediato);
      else
        sol ->draw(inmediato,GL_FILL,2,false);
    glPopMatrix();
    if (incremento_luz < 700)
      incremento_luz += 1;
    else
      incremento_luz = -700;

  }

  if (is_luz1)
    luz1->activar();

	if (ajedrez){
		//===============================================================
        glPushMatrix();
        glPushMatrix();
          glTranslatef(0,0,-500);
          pintura->draw_ajedrez(inmediato);
        glPopMatrix();
			//Creación del suelo
			glPushMatrix();
				glScalef(20,0.2,20);
				glTranslatef(-25,-80,-25);
				suelo->draw_ajedrez(inmediato);
			glPopMatrix();
			glPushMatrix();
				glScalef(200,200,200);
				glTranslatef(100,0,100);
				montania->draw_ajedrez(inmediato);
			glPopMatrix();

			//Creación de las casas
			glPushMatrix();
				glTranslatef(-400,0,-400);
				casa->draw_ajedrez(inmediato);
				glPushMatrix();
					glTranslatef(25,50,25);
					tejado->draw_ajedrez(inmediato);
				glPopMatrix();
				glTranslatef(80,0,0);
				casa->draw_ajedrez(inmediato);
				glPushMatrix();
					glTranslatef(25,50,25);
					tejado->draw_ajedrez(inmediato);
				glPopMatrix();
				glTranslatef(80,0,0);
				casa->draw_ajedrez(inmediato);
				glPushMatrix();
					glTranslatef(25,50,25);
					tejado->draw_ajedrez(inmediato);
				glPopMatrix();
			glPopMatrix();

			//Peones de ajedrez
			glPushMatrix();
				glScalef(20,20,20);
				glTranslatef(1.1,1.4,0);
				peon_blanco->draw_ajedrez(inmediato);
				glTranslatef(-2.2,0,0);
				peon_negro->draw_ajedrez(inmediato);
			glPopMatrix();
			glScalef(20,20,20);
			glTranslatef(5,0,0);
                        //esf->draw_ajedrez(inmediato);
			glTranslatef(-10,0,0);
                        //con->draw_ajedrez(inmediato);
			glTranslatef(5,5,0);
			glPushMatrix();
				glTranslatef(-2,-5,-7);
				cil->draw_ajedrez(inmediato);
            glPopMatrix();
			glTranslatef(-6,-4,0);
			glScalef(0.1,0.1,0.1);
			hormiga->draw_ajedrez(inmediato);
        glPopMatrix();
        glPushMatrix();
			glTranslatef(0,130,0);
			enderdragon->draw_ajedrez(inmediato);
        glPopMatrix();
        //===============================================================

	}else{
		for (int i=0;i<tipo_dibujado.size();i++){
			if (tipo_dibujado[i]){
                                int color;
				switch(i){
					case 0:
						tipo_dibujado_actual = GL_POINT;
                                                color = 0;
						break;
					case 1:
						tipo_dibujado_actual = GL_LINE;
                                                color = 1;
						break;
					case 2:
						tipo_dibujado_actual = GL_FILL;
                                                color = 2;
						break;
				}

		//===============================================================
        glPushMatrix();
          glPushMatrix();
            glTranslatef(0,490,-500);
            glScalef(2,1,1);
            pintura->draw(inmediato, tipo_dibujado_actual,color,false);
          glPopMatrix();
          glPushMatrix();
            glTranslatef(-500,490,0);
            glRotatef(90,0,1,0);
            glScalef(2,1,1);
            pintura->draw(inmediato, tipo_dibujado_actual,color,false);
          glPopMatrix();
          glPushMatrix();
            glTranslatef(500,490,0);
            glRotatef(-90,0,1,0);
            glScalef(2,1,1);
            pintura->draw(inmediato, tipo_dibujado_actual,color,false);
          glPopMatrix();
			//Creación del suelo
			glPushMatrix();
				glScalef(20,0.2,20);
				glTranslatef(-25,-80,-25);
				suelo->draw(inmediato, tipo_dibujado_actual,color,false);
			glPopMatrix();

			//Creación de las casas
			glPushMatrix();
				glTranslatef(-400,0,-400);
				casa->draw(inmediato, tipo_dibujado_actual,color,false);
				glPushMatrix();
					glTranslatef(25,50,25);
					tejado->draw(inmediato, tipo_dibujado_actual,color,false);
				glPopMatrix();
				glTranslatef(80,0,0);
				casa->draw(inmediato, tipo_dibujado_actual,color,false);
				glPushMatrix();
					glTranslatef(25,50,25);
					tejado->draw(inmediato, tipo_dibujado_actual,color,false);
				glPopMatrix();
				glTranslatef(80,0,0);
				casa->draw(inmediato, tipo_dibujado_actual,color,false);
				glPushMatrix();
					glTranslatef(25,50,25);
					tejado->draw(inmediato, tipo_dibujado_actual,color,false);
				glPopMatrix();
			glPopMatrix();

			//Peones de ajedrez
			glPushMatrix();
				glScalef(20,20,20);
				glTranslatef(1.1,1.4,0);
				peon_blanco->draw(inmediato, tipo_dibujado_actual,color,false);
				glTranslatef(-2.2,0,0);
				peon_negro->draw(inmediato, tipo_dibujado_actual,color,false);
			glPopMatrix();
			glScalef(20,20,20);
			glTranslatef(5,0,0);
                        //esf->draw(inmediato, tipo_dibujado_actual,color,true);
			glTranslatef(-10,0,0);
                        //con->draw(inmediato, tipo_dibujado_actual,color,true);
			glTranslatef(5,5,0);
			glPushMatrix();
				glTranslatef(-2,-5,-7);
				cil->draw(inmediato, tipo_dibujado_actual,color,false);
            glPopMatrix();
			glTranslatef(-6,-4,0);
			glScalef(0.1,0.1,0.1);
			hormiga->draw(inmediato, tipo_dibujado_actual,color,false);
        glPopMatrix();
        glPushMatrix();
			glTranslatef(0,130,0);
			enderdragon->draw(inmediato, tipo_dibujado_actual,color);
        glPopMatrix();
        //===============================================================

			}
		}
	}



}

//**************************************************************************
//
// función que se invoca cuando se pulsa una tecla
// Devuelve true si se ha pulsado la tecla para terminar el programa (Q),
// devuelve false en otro caso.
//
//**************************************************************************

bool Escena::teclaPulsada( unsigned char tecla, int x, int y )
{
   using namespace std ;
   bool salir=false;
   switch( toupper(tecla) )
   {
      case 'Q' :
         if (modoMenu!=NADA)
            modoMenu=NADA;
         else {
            salir=true ;
         }
         break ;
      case 'O' :
         // ESTAMOS EN MODO SELECCION DE OBJETO
         modoMenu=SELOBJETO;
         break ;
        case 'V' :
         // ESTAMOS EN MODO SELECCION DE MODO DE VISUALIZACION
         if (modoMenu != SELVISUALIZACION){
			 modoMenu=SELVISUALIZACION;
		 }else{
			 modoMenu = GRADOSLIBERTAD;
		 }
		 break ;
       case 'D' :
         // ESTAMOS EN MODO SELECCION DE DIBUJADO
         modoMenu=SELDIBUJADO;
         break ;


	//SELECCION DE DIBUJADO
	case '1' :
	 if (modoMenu == SELDIBUJADO){
		inmediato = true;
	 }

	 if (modoMenu == SELUCES){
		 if (!is_luz1){
				is_luz1 = true;
			}else{
				is_luz1 = false;
			}
	 }

	 if (modoMenu == GRADOSLIBERTAD){
			giro1 = !giro1;
	}

  if (modoMenu == CAMARA){
    camara_actual = 1;
  }

	 break;
	case '2' :
	 if (modoMenu == SELDIBUJADO){
		inmediato = false;
	 }
	 if (modoMenu == GRADOSLIBERTAD){
		desplazamiento0 = !desplazamiento0;
	}
  if (modoMenu == CAMARA){
    camara_actual = 2;
  }
	 break;

	//MODO DE VISUALIZACION
	case 'P' :
	 if (modoMenu == SELVISUALIZACION){
		ajedrez = false;
		if (tipo_dibujado[0] == false)
			tipo_dibujado[0] = true;
		else
			tipo_dibujado[0] = false;
	}
	 break;
	case 'L' :
	 if (modoMenu == SELVISUALIZACION){
		ajedrez = false;
		if (tipo_dibujado[1] == false)
			tipo_dibujado[1] = true;
		else
			tipo_dibujado[1] = false;
	}
	 break;
	case 'S' :
	 if (modoMenu == SELVISUALIZACION){
		ajedrez = false;
		if (tipo_dibujado[2] == false)
			tipo_dibujado[2] = true;
		else
			tipo_dibujado[2] = false;
	}
	 break;
	case 'A' :
	 if (modoMenu == SELVISUALIZACION){
		if (!ajedrez)
			ajedrez = true;
		else
			ajedrez = false;
	}
	if (modoMenu == SELUCES){
			variar_alfa = true;
	}
	break;

	case 'I' :
	 if (modoMenu == SELVISUALIZACION || modoMenu == SELUCES){
		if (luces){
			modoMenu = SELVISUALIZACION;
			luces = false;
		}else{
			modoMenu = SELUCES;
			luces = true;
		}
	}
	 break;

	 case '0':
		if (modoMenu == SELUCES){
			if (!is_luz0){
				is_luz0 = true;
			}else{
				is_luz0 = false;
			}
		}

		if (modoMenu == GRADOSLIBERTAD){
			giro0 = !giro0;
		}

    if (modoMenu == CAMARA){
      camara_actual = 0;
    }

	 break;


	 case 'B':
		if (modoMenu == SELUCES){
			variar_alfa = false;
		}
	 break;

	 case '<':
		if (modoMenu == SELUCES){
			if (variar_alfa){
				luz1->variarAnguloAlpha(-0.1);
				glDisable(GL_LIGHT1);
			}else{
				luz1->variarAnguloBeta(-0.1);
				glDisable(GL_LIGHT1);
			}
			luz1->activar();
		}
	 break;

	 case '>':
		if (modoMenu == SELUCES){
			if (variar_alfa){
				luz1->variarAnguloAlpha(0.1);
				glDisable(GL_LIGHT1);
			}else{
				luz1->variarAnguloBeta(0.1);
				glDisable(GL_LIGHT1);
			}

			luz1->activar();
		}
	 break;

	 case '+':
		if (modoMenu == GRADOSLIBERTAD){

			if (giro0){
				enderdragon->modificarGiroCola(cola_speed);
			}
			if (giro1){
				enderdragon->modificarGiroAlas(alas_speed);
			}
			if (desplazamiento0){
				enderdragon->modificarDesplazamiento(desplazamiento_speed,desplazamiento_speed);
			}
		}else if (modoMenu == ANIMACION){
			incremento_alas += 0.2;
			incremento_desplazamiento += 0.2;
			incremento_giro += 0.07;

			tope1 -= 45;
		}
	 break;

	 case '-':
		if (modoMenu == GRADOSLIBERTAD){

			if (giro0){
				enderdragon->modificarGiroCola(-cola_speed);
			}
			if (giro1){
				enderdragon->modificarGiroAlas(-alas_speed);
			}
			if (desplazamiento0){
				enderdragon->modificarDesplazamiento(-desplazamiento_speed,-desplazamiento_speed);
			}
		}else if (modoMenu == ANIMACION){
			incremento_alas -= 0.2;
			incremento_desplazamiento -= 0.2;
			incremento_giro -= 0.07;

			tope1 += 90;
		}
	 break;

	 case 'J':
	 if (!activar_animacion){
		 modoMenu = ANIMACION;
	 }else{
		 modoMenu = NADA;
	 }
	 activar_animacion = !activar_animacion;
	 break;

   case 'C':
   modoMenu = CAMARA;
   break;
   case 'T':
   if (modoMenu == SELVISUALIZACION){
    tapas = !tapas;
    peon_blanco->setTapas(tapas);
    cil->setTapas(tapas);
   }
   break;
   case 'M':
   if (giro0){
     cola_speed += 0.1;
   }
   if (giro1){
     alas_speed += 0.1;
   }
   if (desplazamiento0){
     desplazamiento_speed += 0.1;
   }
   break;
   case 'N':
   if (giro0){
     cola_speed -= 0.1;
   }
   if (giro1){
     alas_speed -= 0.1;
   }
   if (desplazamiento0){
     desplazamiento_speed -= 0.1;
   }
   break;
   }



   pintaMenu(modoMenu);
   return salir;
}
//**************************************************************************

void Escena::teclaEspecial( int Tecla1, int x, int y )
{
   switch ( Tecla1 )
   {
	   case GLUT_KEY_LEFT:
         camaras[camara_actual].rotarYExaminar(M_PI/16);
         break;
	   case GLUT_KEY_RIGHT:
         camaras[camara_actual].rotarYExaminar(-M_PI/16);
         break;
	   case GLUT_KEY_UP:
         camaras[camara_actual].rotarXExaminar(M_PI/16);
         break;
	   case GLUT_KEY_DOWN:
         camaras[camara_actual].rotarXExaminar(-M_PI/16);
         break;
	   case GLUT_KEY_PAGE_UP:
         camaras[camara_actual].zoom(1.2);
         change_projection(1);
         break;
	   case GLUT_KEY_PAGE_DOWN:
         camaras[camara_actual].zoom(1/1.2);
         change_projection(1);
         break;
	}

	//std::cout << Observer_distance << std::endl;
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//
// ratio_xy : relacción de aspecto del viewport ( == ancho(X) / alto(Y) )
//
//***************************************************************************

void Escena::change_projection( const float ratio_xy )
{
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   const float wx = float(Height)*ratio_xy ;
   camaras[camara_actual].setProyeccion();
   //glFrustum( -wx, wx, -Height, Height, Front_plane, Back_plane );
}
//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar( int newWidth, int newHeight )
{
   Width  = newWidth/10;
   Height = newHeight/10;
   camaras[camara_actual].setLeft(camaras[camara_actual].getBottom()*(Width/Height));
   camaras[camara_actual].setRight(camaras[camara_actual].getTop()*(Width/Height));
   change_projection( float(newHeight)/float(newWidth) );
   glViewport( 0, 0, newWidth, newHeight );
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void Escena::change_observer()
{
   // posicion del observador
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   /*glTranslatef( 0.0, 0.0, -Observer_distance );
   glRotatef( Observer_angle_y, 0.0 ,1.0, 0.0 );
   glRotatef( Observer_angle_x, 1.0, 0.0, 0.0 );*/
   camaras[camara_actual].setObserver();
}

void Escena::clickRaton(int boton, int estado, int x, int y){
  if (boton == GLUT_LEFT_BUTTON){
    GLfloat pixels[3];
    GLint viewport[4];
    if (estado ==  GLUT_DOWN){

      seleccion = true;
      dibujar_seleccion();
      seleccion = false;
      glGetIntegerv(GL_VIEWPORT,viewport);
      glReadPixels(x,viewport[3]-y,1,1,GL_RGB,GL_FLOAT,pixels);

      if (pixels[0] == 0 && pixels[1] == 1 && pixels[2] == 1){
        camaras[camara_actual].setAt(Tupla3f(-30,15,-150));

        peon_blanco->setSeleccionado(false);
        cil->setSeleccionado(true);
        fperson_camara = false;
      }else if (pixels[0] == 1 &&  pixels[2] == 0){
        camaras[camara_actual].setAt(Tupla3f(5,0,5));
        peon_blanco->setSeleccionado(true);
        cil->setSeleccionado(false);
        fperson_camara = false;
      }else{
        if (!fperson_camara){
          camaras[camara_actual].setAt(Tupla3f(0,70,0));
          camaras[camara_actual].setEye(Tupla3f(0,70,300));
          peon_blanco->setSeleccionado(false);
          cil->setSeleccionado(false);
          fperson_camara = true;
        }
      }
    }

  }
  if (boton == GLUT_RIGHT_BUTTON){
    if (estado ==  GLUT_DOWN){
      camara_raton = true;
      x_anterior = x;
      y_anterior = y;
    }else{
      camara_raton = false;
    }
  }
  if (boton == 3)
    zoom_raton_up = true;
  else if (boton == 4)
    zoom_raton_down = true;
}
void Escena::ratonMovido(int x, int y){
  if (camara_raton == true){
    std::cout << x-x_anterior << std::endl;
    if (fperson_camara){
      camaras[camara_actual].rotarYFirstPerson(-1*((x-x_anterior)*M_PI)/128);
      camaras[camara_actual].rotarXFirstPerson(-1*((y-y_anterior)*M_PI)/128);
    }else{
      camaras[camara_actual].rotarYExaminar(-1*((x-x_anterior)*M_PI)/128);
      camaras[camara_actual].rotarXExaminar(-1*((y-y_anterior)*M_PI)/128);
    }
    x_anterior = x;
    y_anterior = y;
    change_observer();
  }
  if (zoom_raton_up){
    camaras[camara_actual].zoom(1.2);
    change_projection(1);
    zoom_raton_up = false;
  }else if (zoom_raton_down){
    camaras[camara_actual].zoom(1/1.2);
    change_projection(1);
    zoom_raton_down = false;
  }
}

void Escena::dibujar_seleccion(){
  GLfloat mat[16];
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
change_observer();
  glDisable(GL_DITHER);
  glDisable(GL_LIGHT0);
  glDisable(GL_LIGHT1);
  glDisable(GL_LIGHTING);
  //ejes.draw();

glPushMatrix();
  glScalef(20,20,20);
  glTranslatef(1.1,1.4,0);
  peon_blanco->draw(true, GL_FILL,3,true);
  glGetFloatv(GL_MODELVIEW_MATRIX, mat);
  peon_blanco->asignaCentro(mat);
glPopMatrix();
glPushMatrix();
glScalef(20,20,20);
glTranslatef(5,0,0);

glTranslatef(-10,0,0);

glTranslatef(5,5,0);
glPushMatrix();
  glTranslatef(-2,-5,-7);
  cil->draw(true, GL_FILL,4,true);
  glGetFloatv(GL_MODELVIEW_MATRIX, mat);
  cil->asignaCentro(mat);
glPopMatrix();
glPopMatrix();
glEnable(GL_DITHER);
}

void Escena::pintaMenu(menu tipo){
  std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";

  switch (tipo){
    case (NADA):
    std::cout << "V -> Tipo de visualizacion\n";
    std::cout << "J -> Animación automática\n";
    std::cout << "C -> Seleccionar cámaras\n";
    std::cout << "D -> Modo de dibujado\n";
    std::cout << "Q -> Cerrar el programa\n";
    break;
    case (SELVISUALIZACION):
    std::cout << "S -> Visualización en sólido\n";
    std::cout << "L -> Visualización en líneas\n";
    std::cout << "P -> Visualización en puntos\n";
    std::cout << "A -> Visualización en ajedrez\n";
    std::cout << "I -> Activar iluminación\n";
    std::cout << "V -> Movimiento grados de libertad\n";
    std::cout << "T -> Gestión de tapas: " << tapas << std::endl;
    std::cout << "Q -> Salir del menú\n";
    break;
    case (SELDIBUJADO):
    std::cout << "1 -> Modo inmediato\n";
    std::cout << "2 -> Modo diferido\n";
    if (inmediato){
      std::cout << "Seleccionado el modo inmediato\n";
    }else{
      std::cout << "Seleccionado el modo diferido\n";
    }
    std::cout << "Q -> Salir del menú\n";
    break;
    case (SELUCES):
    std::cout << "0 -> Encender luz posicional\n";
    std::cout << "1 -> Encender luz direccional\n";
    std::cout << "A -> Seleccionar ángulo alfa de luz 1\n";
    std::cout << "B -> Seleccionar ángulo beta luz 1\n";
    if (variar_alfa){
      std::cout << "Variando el ángulo alfa\n";
    }else{
      std::cout << "Variando el ángulo beta\n";
    }
    std::cout << "> -> Incrementar ángulo seleccionado\n";
    std::cout << "< -> Decrementar ángulo seleccionado\n";
    std::cout << "I -> Desactivar iluminación\n";
    std::cout << "Q -> Salir del menú\n";
    break;
    case (GRADOSLIBERTAD):
    std::cout << "0 -> Activar giro cola (" << giro0 << ")\n";
    std::cout << "1 -> Activar giro alas (" << giro1 << ")\n";
    std::cout << "2 -> Activar desplazamiento (" << desplazamiento0 << ")\n";
    std::cout << "+ -> Aumentar grados de libertad\n";
    std::cout << "- -> Disminuir grados de libertad\n";
    std::cout << "M -> Aumentar velocidad de partes seleccionadas\n";
    std::cout << "N -> Disminuir velocidad partes seleccionadas\n";
    std::cout << "Q -> Salir del menú\n";
    break;
    case (ANIMACION):
    std::cout << "La animación ha comenzado\n";
    std::cout << "J -> Detener la animación\n";
    std::cout << "Q -> Salir del menú\n";
    break;
    case (CAMARA):
    std::cout << "Cámara actual: " << camara_actual << std::endl;
    std::cout << "0 -> Selección cámara 0\n";
    std::cout << "1 -> Selección cámara 1\n";
    std::cout << "2 -> Seleccion cámara 2\n";
    std::cout << "Q -> Salir del menú\n";
    break;
  }
}

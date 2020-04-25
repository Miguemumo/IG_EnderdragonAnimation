#include "aux.h"
#include "malla.h"
#include <stdlib.h>


// *****************************************************************************
//
// Clase Malla3D
//
// *****************************************************************************

Malla3D::Malla3D(){}

// Visualización en modo inmediato con 'glDrawElements'

void Malla3D::draw_ModoInmediato(bool seleccion)
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
  glDrawElements( GL_TRIANGLES, f.size()*3, GL_UNSIGNED_INT, f.data() );

  glDisableClientState( GL_VERTEX_ARRAY );

  if (glIsEnabled(GL_LIGHTING)&& !seleccion){
    glDisableClientState( GL_NORMAL_ARRAY );
  }

  if (ct.size() != 0 && !seleccion){
    glDisableClientState( GL_TEXTURE_COORD_ARRAY_EXT );
    glDisable(GL_TEXTURE_2D) ;
  }

}
// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

void Malla3D::draw_ModoDiferido()
{

        if (glIsEnabled(GL_LIGHTING))
            calcular_normales();

        if (id_vbo_ver == 0 || id_vbo_tri == 0 || id_vbo_nor == 0 || id_vbo_col == 0)
	{
		            id_vbo_ver = CrearVBO (GL_ARRAY_BUFFER, (3*v.size())*sizeof(float), v.data() );
                id_vbo_tri = CrearVBO (GL_ELEMENT_ARRAY_BUFFER, (3*f.size())*sizeof(int), f.data() );
                id_vbo_col = CrearVBO (GL_ARRAY_BUFFER, (3*color_actual.size())*sizeof(float), color_actual.data() );
                if (glIsEnabled(GL_LIGHTING))
                 id_vbo_nor = CrearVBO (GL_ARRAY_BUFFER, (3*nv.size())*sizeof(float), nv.data() );

	}

	glBindBuffer( GL_ARRAY_BUFFER, id_vbo_ver );
        glEnableClientState( GL_VERTEX_ARRAY );
        glVertexPointer( 3, GL_FLOAT, 0, 0 );
        glBindBuffer( GL_ARRAY_BUFFER, 0 );

        if (glIsEnabled(GL_LIGHTING)){
            glEnableClientState( GL_NORMAL_ARRAY );
            glBindBuffer( GL_ARRAY_BUFFER, id_vbo_nor );

            glNormalPointer( GL_FLOAT, 0, 0 );
            glBindBuffer( GL_ARRAY_BUFFER, 0 );

        }

        glEnableClientState( GL_COLOR_ARRAY );
        glBindBuffer( GL_COLOR_ARRAY, 0 );
        glColorPointer(3,GL_FLOAT,0, color_actual.data() );
        glBindBuffer( GL_ARRAY_BUFFER, 0 );


        if (ct.size() != 0){
          glEnable(GL_TEXTURE_2D);
          glEnableClientState(GL_TEXTURE_COORD_ARRAY_EXT);
          glTexCoordPointer( 2,GL_FLOAT, 0, ct.data());
          textura->activar();
          //glBindBuffer( GL_ARRAY_BUFFER, 0 );

        }


	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri );

	glPolygonMode( GL_FRONT, visualizacion);
        glPointSize(5.0);

        //glBindBuffer( GL_ARRAY_BUFFER, id_vbo_col );
        //glEnableClientState( GL_COLOR_ARRAY );

        //glBindBuffer( GL_ARRAY_BUFFER, 0 );

	glDrawElements( GL_TRIANGLES, 3* f.size(), GL_UNSIGNED_INT, 0 ) ;

	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );

	glDisableClientState( GL_VERTEX_ARRAY );
        //glDisableClientState( GL_COLOR_ARRAY) ;
        if (glIsEnabled(GL_LIGHTING)){
            glDisableClientState( GL_NORMAL_ARRAY );
        }

}
// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void Malla3D::draw(bool inmediato, GLenum tipo, int color,bool seleccion)
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

void Malla3D::draw_ajedrez(bool inmediato)
{

   std::vector<Tupla3i> par ;
   std::vector<Tupla3i> impar ;

   for (int i=0; i<f.size(); i++){
	if (i%2==0)
		par.push_back(f[i]);
	else
		impar.push_back(f[i]);
   }


  glColorPointer(3,GL_FLOAT,0, c2.data() );
  glEnableClientState( GL_VERTEX_ARRAY );
  glVertexPointer( 3, GL_FLOAT, 0, v.data() ) ;
  glPolygonMode( GL_FRONT, GL_FILL);
  glDrawElements( GL_TRIANGLES, par.size()*3, GL_UNSIGNED_INT, par.data() );
  glColorPointer(3,GL_FLOAT,0, c3.data() );
  glDrawElements( GL_TRIANGLES, impar.size()*3, GL_UNSIGNED_INT, impar.data() );
  glDisableClientState( GL_VERTEX_ARRAY );
}

GLuint Malla3D::CrearVBO ( GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid * puntero_ram)
{

	GLuint id_vbo ;
	glGenBuffers( 1, & id_vbo );
	glBindBuffer( tipo_vbo, id_vbo );
	glBufferData( tipo_vbo, tamanio_bytes, puntero_ram, GL_STATIC_DRAW );
	glBindBuffer( tipo_vbo, 0 );
	return id_vbo ;

}

void Malla3D::inicializa_colores()
{
	c1.resize(v.size()*2);
	c2.resize(v.size()*2);
	c3.resize(v.size()*2);
  orange.resize(v.size()*2);
  cyan.resize(v.size()*2);
  color_seleccion.resize(v.size()*2);

	//color_actual.resize(v.size());
	for (int i=0; i<v.size()*2; i++){
                c1[i] = Tupla3f (1.0f,0.0f,0.0f);
                c2[i] = Tupla3f (0.0f,0.0f,1.0f);
                c3[i] = Tupla3f (0.0f,1.0f,0.0f);
                orange[i] = Tupla3f (1.0f,0.501961f,0.0f);
                cyan[i] = Tupla3f (0.0f,1.0f,1.0f);
                color_seleccion[i] = Tupla3f (1.0f,0.0f,0.0f);
	}
}

void Malla3D::calcular_normales()
{
    Tupla3f a;
    Tupla3f b;
    Tupla3f mc;
    //std::vector<Tupla3f> nv;

	nv.resize(v.size());

    for (int i=0; i<nv.size(); i++){
        nv[i] = {0.0,0.0,0.0};
    }

    for (int i=0; i<f.size(); i++){

        a= v[f[i](1)] - v[f[i](0)];
        b= v[f[i](2)] - v[f[i](0)];

        mc = a.cross(b);

        nv[f[i](0)] = nv[f[i](0)] + mc.normalized();
        nv[f[i](1)] = nv[f[i](1)] + mc.normalized();
        nv[f[i](2)] = nv[f[i](2)] + mc.normalized();

    }

    for (int i=0; i<nv.size(); i++){
        nv[i] = nv[i].normalized();
    }




}

void Malla3D::setMaterial(Material * mat){
	m = mat;
}

void Malla3D::setMaterialSeleccionado(Material * mat){
  material_seleccionado = mat;
}


Tupla3f Malla3D::getCentro(){
  return centro;
}

void Malla3D::asignaCentro(float cord_centro[]){
  int x=0,y=0,z=0;
  for (int i=0; i < v.size(); i++){
    x+=v[i](0);
    y+=v[i](1);
    z+=v[i](2);
  }
  x = x/v.size();
  y = y/v.size();
  z = z/v.size();

  centro(0) = cord_centro[0] * x + cord_centro[4] * y + cord_centro[8] * z + cord_centro[12];
  centro(1) = cord_centro[1] * x + cord_centro[5] * y + cord_centro[9] * z + cord_centro[13];
  centro(2) = cord_centro[2] * x + cord_centro[6] * y + cord_centro[10] * z + cord_centro[14];
}

void Malla3D::setSeleccionado(bool selecc){
  seleccionado = selecc;
}

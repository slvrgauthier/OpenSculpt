#include "model/MCylinder.h"
#if defined(__APPLE__) && (__MACH__)
    #include <GLUT/glut.h>
#elif defined(__WIN32__)
    #define GLUT_DISABLE_ATEXIT_HACK
    #include <GL/glut.h>
#else
    #include <GL/glut.h>
#endif
#include "model/func.h"

MCylinder::MCylinder() : m_radius(5.0), m_height(5.0)
{
  // HalfEdges
  m_edges.reserve(96);
  for(int i=0 ; i < 96 ; ++i) { m_edges.push_back(new HalfEdge); }

  // Faces
  m_faces.reserve(32);
  for(int i=0 ; i < 32 ; ++i) { m_faces.push_back(new Face); m_faces.last()->edge = m_edges[3*i]; }

  // Vertices
  m_vertices.reserve(18);
  float angle=2*M_PI/8.; // !!! TU PEUX UTILISER MES FONCTIONS COSD ET SIND POUR UTILISER EN DEGRES ;-)

  for(int k =0;k<=8;k++){   // voir si = doit y etre
      float resultCos= m_radius*cosf(angle*k);// k 0 - > 8 pas de 1
      float resultSin= m_radius*sinf(angle*k);
      m_vertices.push_back(new Vertex);
      m_vertices.last()->coords =  QVector3D(resultCos, -m_height/2., resultSin);
      m_vertices.last()->index = k*2;

      m_vertices.push_back(new Vertex);
      m_vertices.last()->coords =  QVector3D(resultCos, m_height/2., resultSin);
      m_vertices.last()->index = k*2+1;
    }

  m_vertices[0]->outgoing = m_edges[50];
  m_vertices[1]->outgoing = m_edges[74];
  m_vertices[2]->outgoing = m_edges[1];
  m_vertices[3]->outgoing = m_edges[4];
  m_vertices[4]->outgoing = m_edges[7];
  m_vertices[5]->outgoing = m_edges[10];
  m_vertices[6]->outgoing = m_edges[13];
  m_vertices[7]->outgoing = m_edges[16];
  m_vertices[8]->outgoing = m_edges[19];
  m_vertices[9]->outgoing = m_edges[21];
  m_vertices[10]->outgoing = m_edges[24];
  m_vertices[11]->outgoing = m_edges[27];
  m_vertices[12]->outgoing = m_edges[30];
  m_vertices[13]->outgoing = m_edges[34];
  m_vertices[14]->outgoing = m_edges[37];
  m_vertices[15]->outgoing = m_edges[40];
  m_vertices[16]->outgoing = m_edges[43];
  m_vertices[17]->outgoing = m_edges[46];


  // HalfEdges
  for(int i=0 ; i < 96; ++i) {
      m_edges[i]->face = m_faces[i/3];
      m_edges[i]->next = (i%3 == 2)? m_edges[i-2] : m_edges[i+1];
      m_edges[i]->previous = (i%3 == 0)? m_edges[i+2] : m_edges[i-1];
  }


  //OPPOSITE

  // diagonale centrale
  for(int i=2;i<=42;i+=4){
      m_edges[i]->opposite=m_edges[i+2];
      m_edges[i+2]->opposite=m_edges[i];
    }
  //verticale centrale
  m_edges[0]->opposite=m_edges[47];
  m_edges[47]->opposite=m_edges[0];
  for(int i=5;i<=41;i+=6){
      m_edges[i]->opposite=m_edges[i+1];
      m_edges[i+1]->opposite=m_edges[i];
    }
  //Bas contour
  for(int i=1;i<=43;i+=6){
      int index_opposite=69-3*((int)(i-1)/6);
      m_edges[i]->opposite=m_edges[index_opposite];
      m_edges[index_opposite]->opposite=m_edges[i];
    }
   //Bas centre
  m_edges[50]->opposite=m_edges[70];
  m_edges[70]->opposite=m_edges[50];
  for(int i=49;i<=67;i+=3){
      m_edges[i]->opposite=m_edges[i+4];
      m_edges[i+4]->opposite=m_edges[i];
    }
  //Haut contour
  for(int i=3;i<=45;i+=6){
      int index_opposite=72-3*((int)(i-1)/6);
      m_edges[i]->opposite=m_edges[index_opposite];
      m_edges[index_opposite]->opposite=m_edges[i];
    }
  //Haut centre
  m_edges[94]->opposite=m_edges[74];
  m_edges[74]->opposite=m_edges[94];
  for(int i=73;i<=91;i+=3){
      m_edges[i]->opposite=m_edges[i+4];
      m_edges[i+4]->opposite=m_edges[i];
    }


  // Vertex

  //cote
  for(int i=2,j=0;j<=42;i+=2,j+=6){
      m_edges[j]->vertex = m_vertices[i];
      m_edges[j+1]->vertex = m_vertices[(i+2)%16];
      m_edges[j+2]->vertex = m_vertices[i+1];
      m_edges[j+3]->vertex = m_vertices[i+1];
      m_edges[j+4]->vertex = m_vertices[(i+2)%16];
      m_edges[j+5]->vertex = m_vertices[(i+3)%16];
    }

  //bas
  m_edges[48]->vertex = m_vertices[16];
  m_edges[49]->vertex = m_vertices[0];
  m_edges[50]->vertex = m_vertices[2];
  for(int i=16,j=53;j<=70;i-=2,j+=3){
      m_edges[j]->vertex = m_vertices[i-2];
      m_edges[j+1]->vertex = m_vertices[0];
      m_edges[j+2]->vertex = m_vertices[i];
    }

  //haut
  m_edges[93]->vertex = m_vertices[3];
  m_edges[94]->vertex = m_vertices[1];
  m_edges[95]->vertex = m_vertices[17];
  for(int i=3,j=72;j<=94;i+=2,j+=3){
      m_edges[j]->vertex = m_vertices[i+1];
      m_edges[j+1]->vertex = m_vertices[1];
      m_edges[j+2]->vertex = m_vertices[i];
    }

  TEST();
  convertToBuffer();
  update();
}
void MCylinder::initializeGL()
{

}

void MCylinder::setRadius(float radius){
  float angle=2*M_PI/8.; // !!! TU PEUX UTILISER MES FONCTIONS COSD ET SIND POUR UTILISER EN DEGRES ;-)
  if(radius != m_radius) {
      for(int i=0 ; i < m_vertices.size()/2 ; ++i) {
          float resultCos= m_radius*cosf(angle*i);
          float resultSin= m_radius*sinf(angle*i);

          m_vertices[i]->coords.setX(resultCos);
          m_vertices[i]->coords.setY(resultSin);
          m_vertices[i+1]->coords.setX(resultCos);
          m_vertices[i+1]->coords.setY(resultSin);

      }
      m_radius = radius;

      update();
  }


}

void MCylinder::setHeight(float height){
  if(height != m_height) {
      for(int i=0 ; i < m_vertices.size() ; ++i) {
          if(i%2 == 0){
              m_vertices[i]->coords.setY(-height/2.);
            }
          else{
               m_vertices[i]->coords.setY(height/2.);
            }
      }
      m_height = height;

      update();
  }
}

float MCylinder::getRadius() const{
  return m_radius;
}

float MCylinder::getHeight() const{
  return m_height;
}

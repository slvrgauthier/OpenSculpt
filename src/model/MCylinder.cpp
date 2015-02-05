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
  m_edges.reserve(88);
  for(int i=0 ; i < 88 ; ++i) { m_edges.push_back(new HalfEdge); }

  // Faces
  m_faces.reserve(32);
  for(int i=0 ; i < 32 ; ++i) { m_faces.push_back(new Face); m_faces.last()->edge = m_edges[3*i]; }

  // Vertices
  m_vertices.reserve(18);
  float angle=2*M_PI/8.; // !!! TU PEUX UTILISER MES FONCTIONS COSD ET SIND POUR UTILISER EN DEGRES ;-)

  /*for(int k =0;k<=8;k++){
      float resultCos= m_radius*cosf(angle*k);// k 0 - > 8 pas de 1
      float resultSin= m_radius*sinf(angle*k);
      m_vertices.push_back(new Vertex);
      m_vertices.last()->coords =  QVector3D(resultCos, resultSin, -m_height/2.);
      m_vertices.last()->index = k*2;

      m_vertices.push_back(new Vertex);
      m_vertices.last()->coords =  QVector3D(resultCos, resultSin, m_height/2.);
      m_vertices.last()->index = k*2+1;
    }

  m_vertices[0]->outgoing = m_edges[43];
  m_vertices[1]->outgoing = m_edges[66];
  m_vertices[2]->outgoing = m_edges[1];
  m_vertices[3]->outgoing = m_edges[3];
  m_vertices[4]->outgoing = m_edges[6];
  m_vertices[5]->outgoing = m_edges[8];
  m_vertices[6]->outgoing = m_edges[11];
  m_vertices[7]->outgoing = m_edges[13];
  m_vertices[8]->outgoing = m_edges[16];
  m_vertices[9]->outgoing = m_edges[18];
  m_vertices[10]->outgoing = m_edges[21];
  m_vertices[11]->outgoing = m_edges[23];
  m_vertices[12]->outgoing = m_edges[26];
  m_vertices[13]->outgoing = m_edges[28];
  m_vertices[14]->outgoing = m_edges[31];
  m_vertices[15]->outgoing = m_edges[33];
  m_vertices[16]->outgoing = m_edges[36];
  m_vertices[17]->outgoing = m_edges[38];


  // HalfEdges
  //Cote
  for(int i=0 ; i < 41 ; ++i) {
      m_edges[i]->face = m_faces[i/3];
      m_edges[i]->next = (i%3 == 2)? m_edges[i-2] : m_edges[i+1];
      m_edges[i]->previous = (i%3 == 0)? m_edges[i+2] : m_edges[i-1];
  }
  //bas

  //haut
*/

}

void MCylinder::initializeGL()
{

}

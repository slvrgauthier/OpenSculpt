#include "Mesh.h"

void Mesh::makeCone(float height, float radiusUp, float radiusDown) {
    this->clear();

    // HalfEdges
    m_edges.reserve(96);
    for(int i=0 ; i < 96 ; ++i) { m_edges.push_back(new HalfEdge); }

    // Faces
    m_faces.reserve(32);
    for(int i=0 ; i < 32 ; ++i) { m_faces.push_back(new Face); m_faces.last()->edge = m_edges[3*i]; }

    // Vertices
    m_vertices.reserve(18);
    float angle=360./8.;

    m_vertices.push_back(new Vertex);
    m_vertices.last()->coords =  QVector3D(0, -height/2., 0);
    m_vertices.last()->index = 0;
    m_vertices.push_back(new Vertex);
    m_vertices.last()->coords =  QVector3D(0, height/2., 0);
    m_vertices.last()->index = 1;



    for(int k =0;k<8;k++){
        float resultCos1= radiusDown*cosd(angle*k);//cos BAS
        float resultSin1= radiusDown*sind(angle*k);//sin BAS
        float resultCos2= radiusUp*cosd(angle*k);//cos HAUT
        float resultSin2= radiusUp*sind(angle*k);//sin HAUT
        m_vertices.push_back(new Vertex); //BAS
        m_vertices.last()->coords =  QVector3D(resultCos1, -height/2., resultSin1);
        m_vertices.last()->index = k*2+2;

        m_vertices.push_back(new Vertex); //HAUT
        m_vertices.last()->coords =  QVector3D(resultCos2, height/2., resultSin2);
        m_vertices.last()->index = k*2+3;
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
    m_vertices[9]->outgoing = m_edges[22];
    m_vertices[10]->outgoing = m_edges[25];
    m_vertices[11]->outgoing = m_edges[28];
    m_vertices[12]->outgoing = m_edges[31];
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
    for(int i=2;i<=44;i+=6){
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
        int index_opposite=72+3*((int)(i-1)/6);
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
    m_edges[42]->vertex = m_vertices[16];
    m_edges[43]->vertex = m_vertices[2];
    m_edges[44]->vertex = m_vertices[17];
    m_edges[45]->vertex = m_vertices[17];
    m_edges[46]->vertex = m_vertices[2];
    m_edges[47]->vertex = m_vertices[3];

    for(int i=2,j=0;j<42;i+=2,j+=6){
        m_edges[j]->vertex = m_vertices[i];
        m_edges[j+1]->vertex = m_vertices[i+2];
        m_edges[j+2]->vertex = m_vertices[i+1];
        m_edges[j+3]->vertex = m_vertices[i+1];
        m_edges[j+4]->vertex = m_vertices[i+2];
        m_edges[j+5]->vertex = m_vertices[i+3];
      }

    //bas
    m_edges[48]->vertex = m_vertices[16];
    m_edges[49]->vertex = m_vertices[0];
    m_edges[50]->vertex = m_vertices[2];
    for(int i=16,j=51;j<=70;i-=2,j+=3){
        m_edges[j]->vertex = m_vertices[i-2];
        m_edges[j+1]->vertex = m_vertices[0];
        m_edges[j+2]->vertex = m_vertices[i];
      }

    //haut
    m_edges[93]->vertex = m_vertices[3];
    m_edges[94]->vertex = m_vertices[1];
    m_edges[95]->vertex = m_vertices[17];
    for(int i=3,j=72;j<=90;i+=2,j+=3){
        m_edges[j]->vertex = m_vertices[i+2];
        m_edges[j+1]->vertex = m_vertices[1];
        m_edges[j+2]->vertex = m_vertices[i];
      }
}

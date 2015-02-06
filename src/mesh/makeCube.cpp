#include "Mesh.h"

void Mesh::makeCube(float width, float height, float depth) {
    this->clear();

    // HalfEdges
    m_edges.reserve(36);
    for(int i=0 ; i < 36 ; ++i) { m_edges.push_back(new HalfEdge); }

    // Faces
    m_faces.reserve(12);
    for(int i=0 ; i < 12 ; ++i) { m_faces.push_back(new Face); m_faces.last()->edge = m_edges[3*i]; }

    // Vertices
    m_vertices.reserve(8);
    float x = width / 2, y = height / 2, z = depth / 2;

    m_vertices.push_back(new Vertex); m_vertices.last()->coords = QVector3D(-x, -y, z); m_vertices.last()->index = 0; m_vertices.last()->outgoing = m_edges[0];
    m_vertices.push_back(new Vertex); m_vertices.last()->coords = QVector3D(x, -y, z);   m_vertices.last()->index = 1; m_vertices.last()->outgoing = m_edges[1];
    m_vertices.push_back(new Vertex); m_vertices.last()->coords = QVector3D(x, y, z);    m_vertices.last()->index = 2; m_vertices.last()->outgoing = m_edges[3];
    m_vertices.push_back(new Vertex); m_vertices.last()->coords = QVector3D(-x, y, z);   m_vertices.last()->index = 3; m_vertices.last()->outgoing = m_edges[4];
    m_vertices.push_back(new Vertex); m_vertices.last()->coords = QVector3D(-x, -y, -z); m_vertices.last()->index = 4; m_vertices.last()->outgoing = m_edges[7];
    m_vertices.push_back(new Vertex); m_vertices.last()->coords = QVector3D(x, -y, -z);  m_vertices.last()->index = 5; m_vertices.last()->outgoing = m_edges[6];
    m_vertices.push_back(new Vertex); m_vertices.last()->coords = QVector3D(x, y, -z);   m_vertices.last()->index = 6; m_vertices.last()->outgoing = m_edges[10];
    m_vertices.push_back(new Vertex); m_vertices.last()->coords = QVector3D(-x, y, -z);  m_vertices.last()->index = 7; m_vertices.last()->outgoing = m_edges[9];

    // HalfEdges
    for(int i=0 ; i < 36 ; ++i) {
        m_edges[i]->face = m_faces[i/3];
        m_edges[i]->next = (i%3 == 2)? m_edges[i-2] : m_edges[i+1];
        m_edges[i]->previous = (i%3 == 0)? m_edges[i+2] : m_edges[i-1];
    }

    // Front
    m_edges[0]->vertex = m_vertices[1];  m_edges[0]->opposite = m_edges[33];
    m_edges[1]->vertex = m_vertices[2];  m_edges[1]->opposite = m_edges[22];
    m_edges[2]->vertex = m_vertices[0];  m_edges[2]->opposite = m_edges[5];

    m_edges[3]->vertex = m_vertices[3];  m_edges[3]->opposite = m_edges[24];
    m_edges[4]->vertex = m_vertices[0];  m_edges[4]->opposite = m_edges[13];
    m_edges[5]->vertex = m_vertices[2];  m_edges[5]->opposite = m_edges[2];

    // Back
    m_edges[6]->vertex = m_vertices[4];  m_edges[6]->opposite = m_edges[30];
    m_edges[7]->vertex = m_vertices[7];  m_edges[7]->opposite = m_edges[16];
    m_edges[8]->vertex = m_vertices[5];  m_edges[8]->opposite = m_edges[11];

    m_edges[9]->vertex = m_vertices[6];  m_edges[9]->opposite = m_edges[27];
    m_edges[10]->vertex = m_vertices[5]; m_edges[10]->opposite = m_edges[19];
    m_edges[11]->vertex = m_vertices[7]; m_edges[11]->opposite = m_edges[8];

    // Left
    m_edges[12]->vertex = m_vertices[0]; m_edges[12]->opposite = m_edges[34];
    m_edges[13]->vertex = m_vertices[3]; m_edges[13]->opposite = m_edges[4];
    m_edges[14]->vertex = m_vertices[4]; m_edges[14]->opposite = m_edges[17];

    m_edges[15]->vertex = m_vertices[7]; m_edges[15]->opposite = m_edges[28];
    m_edges[16]->vertex = m_vertices[4]; m_edges[16]->opposite = m_edges[7];
    m_edges[17]->vertex = m_vertices[3]; m_edges[17]->opposite = m_edges[14];

    // Right
    m_edges[18]->vertex = m_vertices[5]; m_edges[18]->opposite = m_edges[31];
    m_edges[19]->vertex = m_vertices[6]; m_edges[19]->opposite = m_edges[10];
    m_edges[20]->vertex = m_vertices[1]; m_edges[20]->opposite = m_edges[23];

    m_edges[21]->vertex = m_vertices[2]; m_edges[21]->opposite = m_edges[25];
    m_edges[22]->vertex = m_vertices[1]; m_edges[22]->opposite = m_edges[1];
    m_edges[23]->vertex = m_vertices[6]; m_edges[23]->opposite = m_edges[20];

    // Up
    m_edges[24]->vertex = m_vertices[2]; m_edges[24]->opposite = m_edges[3];
    m_edges[25]->vertex = m_vertices[6]; m_edges[25]->opposite = m_edges[21];
    m_edges[26]->vertex = m_vertices[3]; m_edges[26]->opposite = m_edges[29];

    m_edges[27]->vertex = m_vertices[7]; m_edges[27]->opposite = m_edges[9];
    m_edges[28]->vertex = m_vertices[3]; m_edges[28]->opposite = m_edges[15];
    m_edges[29]->vertex = m_vertices[6]; m_edges[29]->opposite = m_edges[26];

    // Down
    m_edges[30]->vertex = m_vertices[5]; m_edges[30]->opposite = m_edges[6];
    m_edges[31]->vertex = m_vertices[1]; m_edges[31]->opposite = m_edges[18];
    m_edges[32]->vertex = m_vertices[4]; m_edges[32]->opposite = m_edges[35];

    m_edges[33]->vertex = m_vertices[0]; m_edges[33]->opposite = m_edges[0];
    m_edges[34]->vertex = m_vertices[4]; m_edges[34]->opposite = m_edges[12];
    m_edges[35]->vertex = m_vertices[1]; m_edges[35]->opposite = m_edges[32];
}

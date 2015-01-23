/*
 * Model.cpp
 * @author : GAUTHIER Silvère
 *
 * Definition file of Model.h.
 *
 */

#include "model/Model.h"
#include "func/functions.h"

Model::Model(){
    m_name = "";
    m_data = vector<Node>();
}

Model::Model(string name){
    m_name = name;
    m_data = vector<Node>();
}

Model::~Model(){
    // TODO
}

string Model::getName() const { return m_name; }
ModelType Model::getType() const { return m_type; }
unsigned int Model::getSize() const { return m_data.size(); }
Node* Model::getNode(unsigned int index) { return &m_data[index]; }

void Model::setName(string name) { m_name = name; }

void Model::makeCube(float width, float height, float depth, unsigned int resolution){

    m_type = CUBE;
    m_data.clear();

    Node tmpNode;

    // Left and Right sides
    for(float x = -width/2 ; x <= width/2 ; x += width) {

        tmpNode.position[0] = x;

        for(float y = -height/2 ; y <= height/2 ; y += height/resolution) {

            tmpNode.position[1] = y;

            for(float z = -depth/2 ; z <= depth/2 ; z += depth/resolution) {

                tmpNode.position[2] = z;

                m_data.push_back(tmpNode);
            }
        }
    }

    // Up and Down sides
    for(float x = -width/2 ; x <= width/2 ; x += width/resolution) {

        tmpNode.position[0] = x;

        for(float y = -height/2 ; y <= height/2 ; y += height) {

            tmpNode.position[1] = y;

            for(float z = -depth/2 ; z <= depth/2 ; z += depth/resolution) {

                tmpNode.position[2] = z;

                m_data.push_back(tmpNode);
            }
        }
    }

    // Front and Back sides
    for(float x = -width/2 ; x <= width/2 ; x += width/resolution) {

        tmpNode.position[0] = x;

        for(float y = -height/2 ; y <= height/2 ; y += height/resolution) {

            tmpNode.position[1] = y;

            for(float z = -depth/2 ; z <= depth/2 ; z += depth) {

                tmpNode.position[2] = z;

                m_data.push_back(tmpNode);
            }
        }
    }

    for(unsigned int i = 0 ; i < m_data.size()-1 ; ++i) {
        for(unsigned int j = i+1 ; j < m_data.size() ; ++j) {
            if(i != j && !contains(m_data[i].neighbours, &m_data[j])) {
                if(abs(m_data[i].position[0] - m_data[j].position[0]) == width/resolution
                        || abs(m_data[i].position[1] - m_data[j].position[1]) == height/resolution
                        || abs(m_data[i].position[2] - m_data[j].position[2]) == depth/resolution) {
                    m_data[i].neighbours.push_back(&m_data[j]);
                    m_data[j].neighbours.push_back(&m_data[i]);
                }
            }
        }
    }
}

void Model::makeSphere(float radius, unsigned int resolution){
    // TODO
}

void Model::makeCylinder(float radius1, float radius2, float height, unsigned int resolution){
    // TODO
}

void Model::makeTorus(float radius1, float radius2, unsigned int resolution){
    // TODO
}

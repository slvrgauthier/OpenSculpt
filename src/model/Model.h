/*
 * Model.h
 * @author : GAUTHIER Silvère
 *
 * ModelType enumerate the different possibilities to make a base mesh.
 * Node represent a node of our internal mesh, with 3D position and neighbourhood.
 * Model is a mesh defined by a list of Nodes and let the user create base meshes.
 *
 * Models must be added to a ModelManager to be rendered.
 *
 */

#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <string>

using namespace std;

enum ModelType {
    CUBE,
    SPHERE,
    CYLINDER,
    TORUS
};

typedef struct Node {
    float position[3];
    vector<Node*> neighbours;
} Node;

class Model {
private:
    string m_name;
    ModelType m_type;
    vector<Node> m_data;

public:
    Model();
    Model(string name);
    ~Model();

    string getName() const;
    ModelType getType() const;

    void setName(string name);

    /* The four functions below erase the previous data. */
    void makeCube(float width, float height, float depth, unsigned int resolution);
    void makeSphere(float radius, unsigned int resolution);
    void makeCylinder(float radius1, float radius2, float height, unsigned int resolution);
    void makeTorus(float radius1, float radius2, unsigned int resolution);
};

#endif // MODEL_H

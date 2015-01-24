/*
 * Model.h
 * @author : Team OpenSculpt
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

#include <QVector>
#include <QString>

using namespace std;

enum ModelType {
    CUBE,
    SPHERE,
    CYLINDER,
    TORUS
};

typedef struct Node {
    float position[3];
    QVector<Node*> neighbours;
} Node;

class Model {
private:
    QString m_name;
    ModelType m_type;
    QVector<Node> m_data;

public:
    Model();
    Model(QString name);
    ~Model();

    QString getName() const;
    ModelType getType() const;
    unsigned int getSize() const;
    Node* getNode(unsigned int index);

    void setName(QString name);

    /* The four functions below erase the previous data. */
    void makeCube(float width, float height, float depth, unsigned int resolution);
    void makeSphere(float radius, unsigned int resolution);
    void makeCylinder(float radius1, float radius2, float height, unsigned int resolution);
    void makeTorus(float radius1, float radius2, unsigned int resolution);
};

#endif // MODEL_H

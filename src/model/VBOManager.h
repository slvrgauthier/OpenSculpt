#ifndef VBOMANAGER_H
#define VBOMANAGER_H

#include <GL/glew.h>
#include <string>
#include <vector>

using namespace std;

typedef struct VBO {
    GLuint m_id;
    string m_name;
    unsigned int m_size;
} VBO;

class VBOManager {
private :
    vector<VBO> m_vbos;

private:
    void alloc(GLuint vbo, GLsizei size);
    //void realloc(GLuint vbo, GLsizei size);

public:
    VBOManager();
    ~VBOManager();

    GLuint newVBO();
    GLuint newVBO(string name);
    GLuint newVBO(unsigned int size, GLenum type);
    GLuint newVBO(unsigned int size, GLenum type, string name);

    void deleteVBO(GLuint &vbo);

    GLuint getVBO(string name) const;
    GLuint getVBO(unsigned int index) const;

//public slots:


//signals:

};

#endif // VBOMANAGER_H

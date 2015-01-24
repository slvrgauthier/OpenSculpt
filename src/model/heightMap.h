/*
    Copyright 2010-2011  Guillaume Belz
    This software is free: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.
    This software is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    in <http://www.gnu.org/licenses/>.
*/

#ifndef HEIGHTMAP_H
#define HEIGHTMAP_H

#include <QtCore/QVector>
#include <QtCore/QTimer>
#include <QtCore/QTime>
#include <QtGui/QVector2D>
#include <QtGui/QVector3D>
#include <QtOpenGL/QGLWidget>
#include <QtOpenGL/QGLBuffer>

class HeightmapWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit HeightmapWidget(QWidget *parent = 0);
    ~HeightmapWidget();

    QSize minimumSizeHint() const;
    QSize sizeHint() const;

public:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

private:
    void rotateBy(int x, int y, int z);

private:
    // Heightmap infos
    int vertices_by_x;
    int vertices_by_z;
    int quads_by_x;
    int quads_by_z;

    // FPS
    QTimer timer;
    QTime last_time;
    int frame_count;
    int last_count;

    // 3D / 2D coords
    QVector<QVector3D> m_vertices;
    QVector<QVector3D> m_vertexarray;
    QVector<QVector2D> m_textures;
    QVector<QVector2D> m_texturearray;
    QVector<GLuint>    m_indices;
    GLuint             m_textureid;

    // GPU Buffer
    QGLBuffer m_vertexbuffer;
    QGLBuffer m_indicebuffer;
    QGLBuffer m_texturebuffer;

    // View & rotation settings
    QPoint last_pos;
    float  distance;
    qreal  x_rot;
    qreal  y_rot;
    qreal  z_rot;

    // Modes affichage
    enum MODE_RENDU { MODE_GL_VERTEX,
                      MODE_VERTEXARRAY,
                      MODE_VERTEXARRAY_INDICES,
                      MODE_VERTEBUFFEROBJECT_INDICES };

    MODE_RENDU mode_rendu;
    bool mode_texture;
    bool mode_fill;
    int delay;
};

#endif // HEIGHTMAP_H

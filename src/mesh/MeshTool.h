#ifndef MESHTOOL_H
#define MESHTOOL_H

#include "Mesh.h"
#include "functions.h"
#include <QPoint>

#include <QDebug>

/*
 * Nom de classe outil :
 *  - LTName pour "LocalTool" -> outil pour la sculpture de l'objet
 *  - GTName pour "GlobalTool" -> outil pour action sur l'objet en entier
 *  - WTName pour "WindowTool" -> outil pour le déplacement de la caméra uniquement
 */

enum TOOL
{
    GTMOVE,
    GTROTATE,
    GTSCALE,

    LTADD,
    LTINFLATE,
    LTMOVE,
    LTPINCH,
    LTSMOOTH,

    WTMOVE,
    WTROTATE,
    WTSCALE,

    NOTOOL
};

class MeshTool
{
public:
    void gtmove(Mesh *mesh, QVector3D move);
    void gtrotate(Mesh *mesh, QVector3D move);
    void gtscale(Mesh *mesh, QVector3D move);

    void ltadd(Mesh *mesh, QPoint last_position, float brushSize, float strength, Qt::KeyboardModifiers modifiers);
    void ltinflate(Mesh *mesh, QPoint last_position, float brushSize, float strength, Qt::KeyboardModifiers modifiers);
    void ltmove(Mesh *mesh, QPoint last_position, QVector3D move, float brushSize);
    void ltpinch(Mesh *mesh, QPoint last_position, float brushSize, float strength, Qt::KeyboardModifiers modifiers);
    void ltsmooth(Mesh *mesh, QPoint last_position, float brushSize, float strength, Qt::KeyboardModifiers modifiers);

    void subdivideAuto(Mesh *mesh, QPoint last_position, float brushSize);
};

#endif // MESHTOOL_H

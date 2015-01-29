#ifndef TOOL_H
#define TOOL_H

#include "model/Model.h"
#include <QVector3D>

/*
 * nom de classe outil :
 *  - LTName pour "LocalTool" -> outil pour la sculpture (extrusion, lissage...etc)
 *  - GTName pour "GlobalTool" -> outil pour action sur l'objet en entier (rotation, move...etc)
 *  - WTName pour "WindowTool" -> outil pour le déplacement de la caméra uniquement
 */

class Tool
{
public:
    virtual void action(Model *model, QVector3D position, QVector3D move) = 0;
};

#endif // TOOL_H

#ifndef TOOL_H
#define TOOL_H

#include "model/Model.h"
#include <QVector2D>
#include <QPoint>

/*
 * nom de classe outil :
 *  - LTName pour "LocalTool" -> outil pour la sculpture (extrusion, lissage...etc)
 *  - GTName pour "GlobalTool" -> outil pour action sur l'objet en entier (rotation, move...etc)
 *  - WTName pour "WindowTool" -> outil pour le déplacement de la caméra uniquement
 */

class Tool
{
public:
    virtual void action(Model *model, QPoint last_position, QPoint current_position, float distance, float x_rot, float y_rot, float z_rot) = 0;
};

#endif // TOOL_H

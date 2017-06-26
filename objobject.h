#ifndef OBJOBJECT_H
#define OBJOBJECT_H
#include <QVector>
#include <polygon.h>
#include <QVector3D>

class OBJobject
{
public:
    OBJobject();
    QVector<QVector3D> vertices;
    QVector<Polygon> faces;
    QVector<QVector3D> normalsArray;
};

#endif // OBJOBJECT_H

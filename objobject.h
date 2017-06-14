#ifndef OBJOBJECT_H
#define OBJOBJECT_H
#include <QVector>
#include <polygon.h>

class OBJobject
{
public:
    OBJobject();
    QVector<int> vertices;
    QVector<Polygon> faces;
    QVector<int> normalsArray;
};

#endif // OBJOBJECT_H

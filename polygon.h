#ifndef POLYGON_H
#define POLYGON_H
#include<QTextStream>
#include<QVector>
#include <QVector3D>

class Polygon
{
public:
    Polygon();
    Polygon(const QStringList &objStringList);
    Polygon(const QVector<int> &surfIntVect);
    int vertex(int vertexInd) const;
    QVector<int> vertArr;
    bool operator== (const Polygon &b) const;
    QVector<QVector3D> normalMap;
};

#endif // POLYGON_H

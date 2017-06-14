#ifndef POLYGON_H
#define POLYGON_H
#include<QTextStream>
#include<QVector>

class Polygon
{
public:
    Polygon();
    Polygon(const QStringList &objStringList);
    Polygon(const QVector<int> &surfIntVect);
    int vertex(int vertexInd) const;
    QVector<int> vertArr;

    bool operator== (const Polygon &b) const;
};

#endif // POLYGON_H

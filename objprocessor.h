#ifndef OBJREADER_H
#define OBJREADER_H
#include <QString>
#include <objobject.h>
#include <QFile>

class OBJprocessor
{
private:
    static OBJobject parse(QFile &file2parse);
public:
    OBJprocessor();
    static bool read(const QString &objfilename, OBJobject &obj2return);
    static QVector<Polygon> triangulate(const QVector<Polygon> &inpPolygonArr);
    static QVector<QVector3D> computeNormals(const QVector<Polygon> &inputPolygonArr, const QVector<int> &inputVertArr);
};

#endif // OBJREADER_H

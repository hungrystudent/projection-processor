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
    static QVector<QVector3D> computeNormals(const QVector<Polygon> &inputPolygonArr, const QVector<QVector3D> &inputVertArr);
    static QVector<float> getGradientForOnePoint(const QVector3D &pointOne, const QVector3D &pointTwo,const float rotation, const float shiftX, const float shiftY, const float shitfZ);
    static QVector<float> getGrad(const QVector<QVector3D> &meshOne, const QVector<QVector3D> &meshTwo, const float rotation, const float shiftX, const float shiftY, const float shitfZ);
    static float errFuncForOneResidual(const QVector3D &pointOne, const QVector3D &pointTwo, const float rotation, const float shiftX, const float shiftY);
};

#endif // OBJREADER_H

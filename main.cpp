#include <QCoreApplication>
#include <objobject.h>
#include <objprocessor.h>
#include <stdio.h>
#include <iostream>
#include <QDebug>
#include <QVector>
#include <QVector3D>

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    OBJobject handHighPoly;
    OBJobject handLowPoly;

    if(!OBJprocessor::read(QString(DATA_ROOT) + "Neutral.obj",handHighPoly)){
        cout << "No such file or directory \n";
        qDebug() << QString(DATA_ROOT) + "Neutral.obj";
        return 0;
    }
    if(!OBJprocessor::read(QString(DATA_ROOT) + "WrapHand.obj",handLowPoly)){
        cout << "No such file or directory \n";
        qDebug() << QString(DATA_ROOT) + "WrapHand.obj" + "\n";
        return 0;
    }

    handHighPoly.faces = OBJprocessor::triangulate(handHighPoly.faces);
    QVector<QVector3D> normals = OBJprocessor.computeNormals(handHighPoly.faces,handHighPoly.vertices);
    return a.exec();
}

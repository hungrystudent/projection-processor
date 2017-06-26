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

//    if(!OBJprocessor::read(QString(DATA_ROOT) + "Neutral.obj",handHighPoly)){
//        cout << "No such file or directory \n";
//        qDebug() << QString(DATA_ROOT) + "Neutral.obj";
//        return 0;
//    }
    if(!OBJprocessor::read(QString(DATA_ROOT) + "cube.obj",handLowPoly)){
        cout << "No such file or directory \n";
        qDebug() << QString(DATA_ROOT) + "cube.obj" + "\n";
        return 0;
    }

    //handLowPoly.faces = OBJprocessor::triangulate(handLowPoly.faces);
    QVector<QVector3D> normals = OBJprocessor::computeNormals(handLowPoly.faces,handLowPoly.vertices);
    return a.exec();
}

#include <QCoreApplication>
#include <objobject.h>
#include <objprocessor.h>
#include <stdio.h>
#include <iostream>
#include <QDebug>
#include <QVector>
#include <QVector3D>
#include <kdtreenode.h>
#include <kdtree.h>

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    OBJobject handHighPoly;
    OBJobject testCube;

//    if(!OBJprocessor::read(QString(DATA_ROOT) + "Neutral.obj",handHighPoly)){
//        cout << "No such file or directory \n";
//        qDebug() << QString(DATA_ROOT) + "Neutral.obj";
//        return 0;
//    }
    if(!OBJprocessor::read(QString(DATA_ROOT) + "cube.obj",testCube)){
        cout << "No such file or directory \n";
        qDebug() << QString(DATA_ROOT) + "cube.obj" + "\n";
        return 0;
    }

    //handLowPoly.faces = OBJprocessor::triangulate(handLowPoly.faces);
    QVector<QVector3D> normals = OBJprocessor::computeNormals(testCube.faces,testCube.vertices);
    testCube.normalsArray = normals;
    int vertCount = testCube.vertices.count();
    QVector<int> indexArray(vertCount);
    for (int vIndex=0; vIndex < vertCount; vIndex++){
        indexArray[vIndex]=vIndex;
    }
    KDTreeNode *cubeTree;
    cubeTree = KDTree::createTree(testCube.vertices,indexArray,0);
    QVector3D testDot(1.001,-0.001,1.001);
    KDTreeNode *closest = KDTree::findClosest(cubeTree,cubeTree,testDot,0);
    return a.exec();
}

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
#include <QTime>
#include "mainwindow.h"
#include <QApplication>
#include <QTest>
#include "kdtreetests.h"
#include <objprocessor.h>

using namespace std;

void runTests()
{
    KDtreeTests tests;
    QTest::qExec(&tests);
}

int main(int argc, char *argv[])
{
    runTests();
    QApplication a(argc, argv);
    int STEP = 10000;
    float STEP_LENGTH = 0.001;
    qDebug() << "HEY HEY HEY" ;
//    QVector<QVector3D> mesh1={QVector3D(-3,-3,0),QVector3D(-1,-2,0)};
//    QVector<QVector3D> mesh2 = {QVector3D(1,2,0),QVector3D(4,3,0)};

    QVector<QVector3D> mesh1 = {QVector3D(0,0,0),QVector3D(1,0,0)};
    QVector<QVector3D> mesh2 = {QVector3D(0,0,0),QVector3D(0,1,0)};


    QVector<float> phaseVec;
    float sumErr = 0;
    float shiftX=0,shiftY=0,rotation=0;
    for(int i=0;i<STEP;i++){
        sumErr = 0;
        for(int j=0;j<mesh1.count();j++){
            sumErr+= OBJprocessor::errFuncForOneResidual(mesh1[j],mesh2[j],rotation,shiftX,shiftY);
        }
        qDebug() << sumErr;
        phaseVec = OBJprocessor::getGrad(mesh1,mesh2,rotation,shiftX,shiftY,0);
        rotation -= STEP_LENGTH * phaseVec[0];
        shiftX -= STEP_LENGTH *phaseVec[1];
        shiftY -= STEP_LENGTH *phaseVec[2];
    }

    MainWindow w;
    w.show();

    //    QTime myTimer;
    //    OBJobject handHighPoly;
    //    OBJobject testCube;

    //    //    if(!OBJprocessor::read(QString(DATA_ROOT) + "Neutral.obj",handHighPoly)){
    //    //        cout << "No such file or directory \n";
    //    //        qDebug() << QString(DATA_ROOT) + "Neutral.obj";
    //    //        return 0;
    //    //    }
    //    if(!OBJprocessor::read(QString(DATA_ROOT) + "cube.obj",testCube)){
    //        cout << "No such file or directory \n";
    //        qDebug() << QString(DATA_ROOT) + "cube.obj" + "\n";
    //        return 0;
    //    }

    //    //handLowPoly.faces = OBJprocessor::triangulate(handLowPoly.faces);
    //    QVector<QVector3D> normals = OBJprocessor::computeNormals(testCube.faces,testCube.vertices);
    //    testCube.normalsArray = normals;
    //    int vertCount = testCube.vertices.count();
    //    QVector<int> indexArray(vertCount);
    //    for (int vIndex=0; vIndex < vertCount; vIndex++){
    //        indexArray[vIndex]=vIndex;
    //    }

    //    KDTreeNode *cubeTree;

    //    cubeTree = KDTree::createTree(testCube.vertices,indexArray,0);
    //    qDebug() << "Tree created \n";

    //        myTimer.start();
    //    QVector3D testDot(2.00,2.00,2.00);
    //    KDTreeNode *closest = KDTree::findClosest(cubeTree,testDot,0);
    //    int nMilliseconds = myTimer.elapsed();

    //    qDebug() << "closest found \n";
    //    qDebug() << "x coord: " << closest->coordinates.x();
    //    qDebug() << "y coord: " << closest->coordinates.y();
    //    qDebug() << "z coord: " << closest->coordinates.z();
    //    qDebug() << "elapsed time: " << nMilliseconds;
    return a.exec();
}

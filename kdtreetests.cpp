#include "kdtreetests.h"
#include <QTest>
#include <cmath>
#include <kdtree.h>
#include <kdtreenode.h>
#include <objobject.h>
#include <objprocessor.h>


KDtreeTests::KDtreeTests()
{

}

void KDtreeTests::cubeSearch()
{
    OBJobject testCube;
    if(!OBJprocessor::read(QString(DATA_ROOT) + "cube.obj",testCube)){
        //qDebug() << "No such file or directory \n"; << QString(DATA_ROOT) + "cube.obj" + "\n";
    }
    int vertCount = testCube.vertices.count();
    QVector<int> indexArray(vertCount);
    for (int vIndex=0; vIndex < vertCount; vIndex++){
        indexArray[vIndex]=vIndex;
    }
    KDTreeNode *cubeTree;
    cubeTree = KDTree::createTree(testCube.vertices,indexArray,0);
    QVector3D testDot(2.00,0.30,0.00);
    QVector3D realClosest(1.00,0.00,0.00);
    KDTreeNode *closest = KDTree::findClosest(cubeTree,testDot,0);
    QCOMPARE(closest->coordinates,realClosest);
}

void KDtreeTests::degenerateSearch()
{
    OBJobject testCube;
    if(!OBJprocessor::read(QString(DATA_ROOT) + "degenerate.obj",testCube)){
        //qDebug() << "No such file or directory \n"; << QString(DATA_ROOT) + "degenerate.obj" + "\n";
    }
    int vertCount = testCube.vertices.count();
    QVector<int> indexArray(vertCount);
    for (int vIndex=0; vIndex < vertCount; vIndex++){
        indexArray[vIndex]=vIndex;
    }
    KDTreeNode *cubeTree;
    cubeTree = KDTree::createTree(testCube.vertices,indexArray,0);
    QVector3D testDot(2.00,2.00,2.00);
    QVector3D realClosest(0.00,0.00,0.00);
    KDTreeNode *closest = KDTree::findClosest(cubeTree,testDot,0);
    QCOMPARE(closest->coordinates,realClosest);
}

void KDtreeTests::inlineSearchY()
{
    OBJobject testCube;
    if(!OBJprocessor::read(QString(DATA_ROOT) + "lineY.obj",testCube)){
        //qDebug() << "No such file or directory \n"; << QString(DATA_ROOT) + "lineY.obj" + "\n";
    }
    int vertCount = testCube.vertices.count();
    QVector<int> indexArray(vertCount);
    for (int vIndex=0; vIndex < vertCount; vIndex++){
        indexArray[vIndex]=vIndex;
    }
    KDTreeNode *cubeTree;
    cubeTree = KDTree::createTree(testCube.vertices,indexArray,0);
    QVector3D testDot(1.00,10.00,1.00);
    QVector3D realClosest(0.00,8.00,0.00);
    KDTreeNode *closest = KDTree::findClosest(cubeTree,testDot,0);
    QCOMPARE(closest->coordinates,realClosest);
}

void KDtreeTests::inlineSearchZ()
{
    OBJobject testCube;
    if(!OBJprocessor::read(QString(DATA_ROOT) + "lineZ.obj",testCube)){
        //qDebug() << "No such file or directory \n"; << QString(DATA_ROOT) + "lineZ.obj" + "\n";
    }
    int vertCount = testCube.vertices.count();
    QVector<int> indexArray(vertCount);
    for (int vIndex=0; vIndex < vertCount; vIndex++){
        indexArray[vIndex]=vIndex;
    }
    KDTreeNode *cubeTree;
    cubeTree = KDTree::createTree(testCube.vertices,indexArray,0);
    QVector3D testDot(1.00,1.00,10.00);
    QVector3D realClosest(0.00,0.00,8.00);
    KDTreeNode *closest = KDTree::findClosest(cubeTree,testDot,0);
    QCOMPARE(closest->coordinates,realClosest);
}

void KDtreeTests::inlineSearchX()
{
    OBJobject testCube;
    if(!OBJprocessor::read(QString(DATA_ROOT) + "lineX.obj",testCube)){
        //qDebug() << "No such file or directory \n"; << QString(DATA_ROOT) + "lineX.obj" + "\n";
    }
    int vertCount = testCube.vertices.count();
    QVector<int> indexArray(vertCount);
    for (int vIndex=0; vIndex < vertCount; vIndex++){
        indexArray[vIndex]=vIndex;
    }
    KDTreeNode *cubeTree;
    cubeTree = KDTree::createTree(testCube.vertices,indexArray,0);
    QVector3D testDot(10.00,1.00,1.00);
    QVector3D realClosest(8.00,0.00,0.00);
    KDTreeNode *closest = KDTree::findClosest(cubeTree,testDot,0);
    QCOMPARE(closest->coordinates,realClosest);
}


void KDtreeTests::flat1()
{
    OBJobject testCube;
    if(!OBJprocessor::read(QString(DATA_ROOT) + "flat.obj",testCube)){
        //qDebug() << "No such file or directory \n"; << QString(DATA_ROOT) + "flat.obj" + "\n";
    }
    int vertCount = testCube.vertices.count();
    QVector<int> indexArray(vertCount);
    for (int vIndex=0; vIndex < vertCount; vIndex++){
        indexArray[vIndex]=vIndex;
    }
    KDTreeNode *cubeTree;
    cubeTree = KDTree::createTree(testCube.vertices,indexArray,0);
    QVector3D testDot(-0.10,2.10,0.00);
    QVector3D realClosest(1.00,2.00,0.00);
    KDTreeNode *closest = KDTree::findClosest(cubeTree,testDot,0);
    QCOMPARE(closest->coordinates,realClosest);
}

void KDtreeTests::warpedCube()
{
    OBJobject testCube;
    if(!OBJprocessor::read(QString(DATA_ROOT) + "warpedcube.obj",testCube)){
        //qDebug() << "No such file or directory \n"; << QString(DATA_ROOT) + "flat.obj" + "\n";
    }
    int vertCount = testCube.vertices.count();

   // QVector<QVector3D> vertices = { QVector3D(0.12,0,0),QVector3D(1,0,0),QVector3D(1,1,0),QVector3D(0,1,0),QVector3D(0,0,-1.3) };
    QVector<int> indexArray(vertCount);
    for (int vIndex=0; vIndex < vertCount; vIndex++)
        indexArray[vIndex]=vIndex;

    KDTreeNode *cubeTree;
    cubeTree = KDTree::createTree(testCube.vertices,indexArray,0);
    QVector3D testDot(-20,20,1);
    //QVector3D realClosest(1.041440, 1.021004, 1.021329);
    KDTreeNode *closest = KDTree::findClosest(cubeTree,testDot,0);
    QCOMPARE(closest->verticeGlobalNumber,6);
    //QCOMPARE(closest->coordinates,realClosest);
}

void KDtreeTests::warpedCube2()
{
//    OBJobject testCube;
//    if(!OBJprocessor::read(QString(DATA_ROOT) + "warpcube.obj",testCube)){
//        //qDebug() << "No such file or directory \n"; << QString(DATA_ROOT) + "flat.obj" + "\n";
//    }
//    int vertCount = testCube.vertices.count();
    QVector<QVector3D> vertices = {QVector3D(1,1,-21), QVector3D(0.12,0,0),QVector3D(1,0,0),QVector3D(1,1,0),QVector3D(0,1,0),QVector3D(0,0,-1.3), QVector3D(1,2,-3) };
    QVector<int> indexArray(vertices.count());
    for (int vIndex=0; vIndex < vertices.count(); vIndex++)
        indexArray[vIndex]=vIndex;
    KDTreeNode *cubeTree;
    cubeTree = KDTree::createTree(vertices,indexArray,0);
    QVector3D testDot(1,2,-3.1);
    //QVector3D realClosest(1.041440, 1.021004, 1.021329);
    KDTreeNode *closest = KDTree::findClosest(cubeTree,testDot,0);
    QCOMPARE(closest->verticeGlobalNumber,6);
    //QCOMPARE(closest->coordinates,realClosest);
}


void KDtreeTests::warpedCube3()
{
//    OBJobject testCube;
//    if(!OBJprocessor::read(QString(DATA_ROOT) + "warpcube.obj",testCube)){
//        //qDebug() << "No such file or directory \n"; << QString(DATA_ROOT) + "flat.obj" + "\n";
//    }
//    int vertCount = testCube.vertices.count();
    QVector<QVector3D> vertices = {QVector3D(0,-20,10),QVector3D(-3,-3,-3),QVector3D(10,2,-4), QVector3D(0,-21,11), QVector3D(0.12,0,0),QVector3D(1,0,0),QVector3D(1,1,0),QVector3D(0,1,0),QVector3D(0,0,-1.3), QVector3D(1,2,-3) };
    QVector<int> indexArray(vertices.count());
    for (int vIndex=0; vIndex < vertices.count(); vIndex++)
        indexArray[vIndex]=vIndex;
    KDTreeNode *cubeTree;
    cubeTree = KDTree::createTree(vertices,indexArray,0);
    QVector3D testDot(0,-21,10.2);
    //QVector3D realClosest(1.041440, 1.021004, 1.021329);
    KDTreeNode *closest = KDTree::findClosest(cubeTree,testDot,0);
    QCOMPARE(closest->verticeGlobalNumber,3);
    //QCOMPARE(closest->coordinates,realClosest);
}

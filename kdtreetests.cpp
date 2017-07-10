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
    QVector3D testDot(-0.1,2.1,0);
    QVector3D realClosest(8.00,0.00,0.00);
    KDTreeNode *closest = KDTree::findClosest(cubeTree,testDot,0);
    QCOMPARE(closest->coordinates,realClosest);
}

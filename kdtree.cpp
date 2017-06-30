#include "kdtree.h"
#include <kdtreenode.h>

KDTree::KDTree()
{

}

bool KDTree::xAxisLessThan(const QVector3D &vec1, const QVector3D &vec2)
{
    return vec1.x()<vec2.x();
}

bool KDTree::yAxisLessThan(const QVector3D &vec1, const QVector3D &vec2)
{
    return vec1.y()<vec2.y();
}

bool KDTree::zAxisLessThan(const QVector3D &vec1, const QVector3D &vec2)
{
    return vec1.z()<vec2.z();
}

KDTreeNode *KDTree::createTree(const QVector<QVector3D> &pointList, int depth)
{
    KDTreeNode *emptyNode;
    if((depth > TDEPTH)||(pointList.count() < 1)){
        emptyNode = new KDTreeNode(true);
        return emptyNode;
    }

    QVector<QVector3D> localPointList = pointList;
    int dimCount = 3;
    KDTreeNode *node2return;
    KDTreeNode *leftChild;
    KDTreeNode *rightChild;
    QVector<QVector3D> beforeMedianArr;
    QVector<QVector3D> afterMedianArr;

    int axis = depth % dimCount;
    switch (axis) {
    case 0:
        qSort(localPointList.begin(),localPointList.end(),xAxisLessThan);
        break;
    case 1:
        qSort(localPointList.begin(),localPointList.end(),yAxisLessThan);
        break;
    case 2:
        qSort(localPointList.begin(),localPointList.end(),zAxisLessThan);
        break;
    default:
        break;
    }

    int median = (localPointList.count()-1) / 2;

    for (int i=0; i<(median); i++){
        beforeMedianArr.append(localPointList[i]);
    }
    for (int i=median+1; i<localPointList.count(); i++){
        afterMedianArr.append(localPointList[i]);
    }

    leftChild=KDTree::createTree(beforeMedianArr,++depth);
    rightChild=KDTree::createTree(afterMedianArr,++depth);
    node2return = new KDTreeNode(leftChild,rightChild,median,localPointList[median]);
    return node2return;
}

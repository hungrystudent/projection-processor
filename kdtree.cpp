#include "kdtree.h"
#include <kdtreenode.h>

KDTree::KDTree()
{

}

//bool KDTree::xAxisLessThan(const QVector3D &vec1, const QVector3D &vec2)
//{
//    return vec1.x()<vec2.x();
//}

//bool KDTree::yAxisLessThan(const QVector3D &vec1, const QVector3D &vec2)
//{
//    return vec1.y()<vec2.y();
//}

//bool KDTree::zAxisLessThan(const QVector3D &vec1, const QVector3D &vec2)
//{
//    return vec1.z()<vec2.z();
//}



KDTreeNode *KDTree::createTree(const QVector<QVector3D> &pointList,const QVector<int> &indexArray, int depth)
{
    int dimCount = 3;
    KDTreeNode *node2return;
    KDTreeNode *leftChild;
    KDTreeNode *rightChild;
    QVector<int> beforeMedianIndexes;
    QVector<int> afterMedianIndexes;
    QVector<int> localIndexes = indexArray;
    int medianGlobalIndex;
    if(indexArray.count() == 1){
        leftChild=KDTree::createTree(pointList,beforeMedianIndexes,++depth);
        rightChild=KDTree::createTree(pointList,afterMedianIndexes,++depth);
        medianGlobalIndex = indexArray[0];
        node2return = new KDTreeNode(leftChild,rightChild,medianGlobalIndex,pointList[medianGlobalIndex]);
    }

    KDTreeNode *emptyNode;
    if((depth > TDEPTH)||(indexArray.count() <1)){
        emptyNode = new KDTreeNode(true);
        return emptyNode;
    }

    auto xAxisLessThan = [&](const int ind1, const int ind2){
        return pointList[ind1].x() < pointList[ind2].x();
    };
    auto yAxisLessThan = [&](const int ind1, const int ind2){
        return pointList[ind1].y() < pointList[ind2].y();
    };
    auto zAxisLessThan = [&](const int ind1, const int ind2){
        return pointList[ind1].z() < pointList[ind2].z();
    };




    int median = (localIndexes.count()) / 2;
    int axis = depth % dimCount;
    switch (axis) {
    case 0:
        qSort(localIndexes.begin(),localIndexes.end(),xAxisLessThan);
        break;
    case 1:
        qSort(localIndexes.begin(),localIndexes.end(),yAxisLessThan);
        break;
    case 2:
        qSort(localIndexes.begin(),localIndexes.end(),zAxisLessThan);
        break;
    default:
        break;
    }

    for (int i=0; i<(median); i++){
        beforeMedianIndexes.append(localIndexes[i]);
    }
    for (int i=median+1; i<localIndexes.count(); i++){
        afterMedianIndexes.append(localIndexes[i]);
    }
    medianGlobalIndex = localIndexes[median];
    leftChild=KDTree::createTree(pointList,beforeMedianIndexes,1+depth);
    rightChild=KDTree::createTree(pointList,afterMedianIndexes,1+depth);
    node2return = new KDTreeNode(leftChild,rightChild,medianGlobalIndex,pointList[medianGlobalIndex]);
    return node2return;

//    auto func = [&](const int ind1, const int ind2){
//        return pointList[ind1].x() < pointList[ind2].x();
//    };
//    QVector<int> indices;
//    qSort(indices.begin(),indices.end(),func);

//    KDTreeNode *emptyNode;
//    if((depth > TDEPTH)||(pointList.count() < 1)){
//        emptyNode = new KDTreeNode(true);
//        return emptyNode;
//    }

//    QVector<QVector3D> localPointList = pointList;
//    int dimCount = 3;
//    KDTreeNode *node2return;
//    KDTreeNode *leftChild;
//    KDTreeNode *rightChild;
//    QVector<QVector3D> beforeMedianArr;
//    QVector<QVector3D> afterMedianArr;

//    int axis = depth % dimCount;
//    switch (axis) {
//    case 0:
//        qSort(localPointList.begin(),localPointList.end(),xAxisLessThan);
//        break;
//    case 1:
//        qSort(localPointList.begin(),localPointList.end(),yAxisLessThan);
//        break;
//    case 2:
//        qSort(localPointList.begin(),localPointList.end(),zAxisLessThan);
//        break;
//    default:
//        break;
//    }

//    int median = (localPointList.count()-1) / 2;

//    for (int i=0; i<(median); i++){
//        beforeMedianArr.append(localPointList[i]);
//    }
//    for (int i=median+1; i<localPointList.count(); i++){
//        afterMedianArr.append(localPointList[i]);
//    }

//    leftChild=KDTree::createTree(beforeMedianArr,++depth);
//    rightChild=KDTree::createTree(afterMedianArr,++depth);
//    node2return = new KDTreeNode(leftChild,rightChild,median,localPointList[median]);
//    return node2return;
}

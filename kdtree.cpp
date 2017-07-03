#include "kdtree.h"
#include <kdtreenode.h>
#include <qmath.h>
KDTree::KDTree()
{

}




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
}

KDTreeNode *KDTree::findClosest(KDTreeNode *subTreeForSearch, const QVector3D &inputDot, int depth)
{

    int dimCount = 3;
    int axis = depth % dimCount;
    KDTreeNode *currentBest;
    KDTreeNode *maybeBetter;
    float newBestDistance;
    float probBestDistance;

    if (subTreeForSearch->emptyFlag == true){
        return subTreeForSearch;
    }
    switch (axis) {
    case 0:
        if (inputDot.x() >= subTreeForSearch->coordinates.x()){
            currentBest = KDTree::findClosest(subTreeForSearch->rightNode,inputDot,depth+1);
        }else{
            currentBest = KDTree::findClosest(subTreeForSearch->leftNode,inputDot,depth+1);
        }
        break;
    case 1:
        if (inputDot.y() >= subTreeForSearch->coordinates.y()){
            currentBest = KDTree::findClosest(subTreeForSearch->rightNode,inputDot,depth+1);
        }else{
            currentBest = KDTree::findClosest(subTreeForSearch->leftNode,inputDot,depth+1);
        }
        break;
    case 2:
        if (inputDot.z() >= subTreeForSearch->coordinates.z()){
            currentBest = KDTree::findClosest(subTreeForSearch->rightNode,inputDot,depth+1);
        }else{
            currentBest = KDTree::findClosest(subTreeForSearch->leftNode,inputDot,depth+1);
        }
        break;
    default:
        break;
    }

    float x_cur_difference = subTreeForSearch->coordinates.x() - inputDot.x();
    float y_cur_difference = subTreeForSearch->coordinates.y() - inputDot.y();
    float z_cur_difference = subTreeForSearch->coordinates.z() - inputDot.z();
    float cur_distance= qSqrt(x_cur_difference*x_cur_difference+y_cur_difference*y_cur_difference+z_cur_difference*z_cur_difference);

    float x_best_difference = currentBest->coordinates.x() - inputDot.x();
    float y_best_difference = currentBest->coordinates.y() - inputDot.y();
    float z_best_difference = currentBest->coordinates.z() - inputDot.z();
    float best_distance= qSqrt(x_best_difference*x_best_difference+y_best_difference*y_best_difference+z_best_difference*z_best_difference);

    if ((cur_distance < best_distance)){
        currentBest=subTreeForSearch;
        newBestDistance = cur_distance;
    }

    if (subTreeForSearch->leftNode->emptyFlag != true){
        switch (axis) {
        case 0:
            if ((newBestDistance > qFabs(currentBest->coordinates.x() - inputDot.x())) ){
                maybeBetter = KDTree::findClosest(subTreeForSearch->leftNode,inputDot,depth+1);
            }else{
                maybeBetter = subTreeForSearch;
            }
            break;
        case 1:
            if ((newBestDistance > qFabs(currentBest->coordinates.y() - inputDot.y()))){
                maybeBetter = KDTree::findClosest(subTreeForSearch->leftNode,inputDot,depth+1);
            }else{
                maybeBetter = subTreeForSearch;
            }
            break;
        case 2:
            if ((newBestDistance > qFabs(currentBest->coordinates.z() - inputDot.z()))){
                maybeBetter = KDTree::findClosest(subTreeForSearch->leftNode,inputDot,depth+1);
            }else{
                maybeBetter = subTreeForSearch;
            }
            break;
        default:
            break;
        }

        if(maybeBetter != subTreeForSearch){
            float probx_cur_difference = subTreeForSearch->coordinates.x() - inputDot.x();
            float proby_cur_difference = subTreeForSearch->coordinates.y() - inputDot.y();
            float probz_cur_difference = subTreeForSearch->coordinates.z() - inputDot.z();
            float probcur_distance= qSqrt(probx_cur_difference*probx_cur_difference+proby_cur_difference*proby_cur_difference+probz_cur_difference*probz_cur_difference);

            float probx_best_difference = maybeBetter->coordinates.x() - inputDot.x();
            float proby_best_difference = maybeBetter->coordinates.y() - inputDot.y();
            float probz_best_difference = maybeBetter->coordinates.z() - inputDot.z();
            float probbest_distance= qSqrt(probx_best_difference*probx_best_difference+proby_best_difference*proby_best_difference+probz_best_difference*probz_best_difference);

            if ((probcur_distance < probbest_distance)){
                currentBest=subTreeForSearch;
            }
        }
    }

    return currentBest;
}

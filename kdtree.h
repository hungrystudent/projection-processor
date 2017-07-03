#ifndef KDTREE_H
#define KDTREE_H
#include <kdtreenode.h>
#include <QVector3D>

class KDTree
{
private:
    static const int TDEPTH = 10;
public:
    KDTree();
    static KDTreeNode *createTree(const QVector<QVector3D> &pointList,const QVector<int> &indexArray, int depth);
    static KDTreeNode *findClosest(KDTreeNode *treeForSearch,KDTreeNode *inpCurrentBest, const QVector3D &inputDot,int depth);
};

#endif // KDTREE_H

#ifndef KDTREENODE_H
#define KDTREENODE_H
#include <QVector>

class KDTreeNode
{
public:
    KDTreeNode();
    const int TDEPTH = 10;
    QVector<int> trace;
    int vertexNumber;
    KDTreeNode *leftNode;
    KDTreeNode *rightNode;
    KDTreeNode createTree(const QVector<int> &pointList, const int depth);
};

#endif // KDTREENODE_H

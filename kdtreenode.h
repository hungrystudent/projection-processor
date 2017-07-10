#ifndef KDTREENODE_H
#define KDTREENODE_H
#include <QVector>
#include <QVector3D>

class KDTreeNode
{
public:
    KDTreeNode();
    ~KDTreeNode();
    KDTreeNode(bool flag);
    KDTreeNode(KDTreeNode *inpLeftNode,KDTreeNode *inpRightNode,int inpPointNum, const QVector3D &inpCoords);
    bool emptyFlag;
    int verticeGlobalNumber;
    QVector3D coordinates;
    KDTreeNode *leftNode;
    KDTreeNode *rightNode;
};

#endif // KDTREENODE_H

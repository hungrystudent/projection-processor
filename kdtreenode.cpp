#include "kdtreenode.h"

KDTreeNode::KDTreeNode()
{

}

KDTreeNode::KDTreeNode(bool flag)
{
    emptyFlag = flag;
}

KDTreeNode::KDTreeNode(KDTreeNode *inpLeftNode, KDTreeNode *inpRightNode, int inpPointNum, const QVector3D &inpCoords)
{
    emptyFlag = false;
    leftNode = inpLeftNode;
    rightNode = inpRightNode;
    verticeGlobalNumber = inpPointNum;
    coordinates = inpCoords;
}


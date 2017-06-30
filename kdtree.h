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
    static KDTreeNode *createTree(const QVector<QVector3D> &pointList, int depth);
    static bool xAxisLessThan(const QVector3D &vec1, const QVector3D &vec2);
    static bool yAxisLessThan(const QVector3D &vec1, const QVector3D &vec2);
    static bool zAxisLessThan(const QVector3D &vec1, const QVector3D &vec2);
};

#endif // KDTREE_H

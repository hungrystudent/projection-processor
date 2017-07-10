#ifndef KDTREETESTS_H
#define KDTREETESTS_H

#include <QObject>

class KDtreeTests: public QObject
{
    Q_OBJECT
public:
    KDtreeTests();
private slots:
    void cubeSearch();
    void degenerateSearch();
    void inlineSearchX();
    void inlineSearchY();
    void inlineSearchZ();
    void flat1();
};

#endif // KDTREETESTS_H

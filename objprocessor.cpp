#include "objprocessor.h"
#include <QFile>
#include <QTextStream>
#include <QFile>
#include <polygon.h>

OBJprocessor::OBJprocessor()
{

}

OBJobject OBJprocessor::parse(QFile &file2parse)
{

    OBJobject obj2return = OBJobject();

    float xcor,ycor,zcor;
    xcor=0;
    ycor=0;
    zcor=0;

    QString vertMark = QString("v");
    QString txCoorMark = QString("vt");
    QString normalsMark = QString("vn");
    QString vParamMark = QString("vp");
    QString surfaceMark = QString("f");
    QString groupMark = QString("g");

    QTextStream in(&file2parse);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList splitedStr = line.split( " ",  QString::SkipEmptyParts);

        if (splitedStr.value(0) == vertMark){
            xcor = splitedStr.value(1).toFloat();
            ycor = splitedStr.value(2).toFloat();
            zcor = splitedStr.value(3).toFloat();
            obj2return.vertices.append(xcor);
            obj2return.vertices.append(ycor);
            obj2return.vertices.append(zcor);
        }
        if (splitedStr.value(0) == surfaceMark){
            obj2return.faces.append(Polygon(splitedStr));
        }
    }
    return obj2return;
}

bool OBJprocessor::read(const QString &objfilename, OBJobject &obj2return)
{

    QFile objFile(objfilename);
    if (!objFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    obj2return = parse(objFile);

    return true;
}

QVector<Polygon> OBJprocessor::triangulate(const QVector<Polygon> &inpPolygonArr)
{
    OBJobject obj2return = OBJobject();

    Q_ASSERT(!inpPolygonArr.isEmpty());
    QVector<Polygon> returnArray;
    for(int polygonIndex=0; polygonIndex<inpPolygonArr.length(); polygonIndex++){
        const int nVertices = inpPolygonArr[polygonIndex].vertArr.length()-1;
        for (int polygVrtIndex = 1; polygVrtIndex < nVertices; polygVrtIndex++){
            Polygon polygon = inpPolygonArr[polygonIndex];
            QVector<int> locVVector;
            locVVector << polygon.vertex(0);
            locVVector << polygon.vertex(polygVrtIndex);
            locVVector << polygon.vertex(polygVrtIndex+1);
            Polygon polygForAdd;
            polygForAdd = Polygon(locVVector);
            returnArray.append(polygForAdd);
        }
    }
    return returnArray;
}

QVector<int> OBJprocessor::computeNormals(const OBJobject &obj2compute)
{
    QVector<int> normals2return;
    int facesCount = obj2compute.faces.count();
    for(int i=0; i<facesCount;i++){

    }
}



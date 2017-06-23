#include "objprocessor.h"
#include <QFile>
#include <QTextStream>
#include <QFile>
#include <polygon.h>
#include <QVector>
#include <QVector3D>

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

QVector<QVector3D> OBJprocessor::computeNormals(const QVector<Polygon> &inputPolygonArr, const QVector<int> &inputVertArr)
{
    int amountOfVerts = inputVertArr.count();
    int amountOfPolygons = inputPolygonArr.count();

    QVector<QVector3D> arr2return(amountOfVerts);
    QVector<QVector3D> emptyArr;
    QVector<int> timesVertAppear(amountOfVerts);

    for(int polygIndex=0; polygIndex<amountOfPolygons;polygIndex++){
        for(int vertIndex=0; vertIndex<inputPolygonArr[polygIndex].vertArr.count(); vertIndex++){

        }
    }

    int polygonCount = inputPolygonArr.count();
    for(int polygonIndex=0; polygonIndex<polygonCount;polygonIndex++){
        int numOfPolygonVerts = inputPolygonArr[polygonIndex].vertArr.count();
        if (numOfPolygonVerts > 3){
            return emptyArr;
        }
        float xOne, yOne, zOne = 0;
        float xTwo, yTwo, zTwo = 0;
        for (int polygVertIndex = 0; polygVertIndex < numOfPolygonVerts; polygVertIndex++){
            int vNum1 = inputPolygonArr[polygonIndex].vertArr[0];
            int vNum2 = inputPolygonArr[polygonIndex].vertArr[1];
            int vNum3 = inputPolygonArr[polygonIndex].vertArr[2];

            float xvNum1 = inputVertArr[(int)(vNum1*3-3)];
            float yvNum1 = inputVertArr[(int)(vNum1*3-2)];
            float zvNum1 = inputVertArr[(int)(vNum1*3-1)];

            float xvNum2 = inputVertArr[(int)(vNum2*3-3)];
            float yvNum2 = inputVertArr[(int)(vNum2*3-2)];
            float zvNum2 = inputVertArr[(int)(vNum2*3-1)];

            float xvNum3 = inputVertArr[(int)(vNum3*3-3)];
            float yvNum3 = inputVertArr[(int)(vNum3*3-2)];
            float zvNum3 = inputVertArr[(int)(vNum3*3-1)];

            xOne = xvNum1 - xvNum2;
            yOne = yvNum1 - yvNum2;
            zOne = zvNum1 - zvNum2;

            xTwo = xvNum1 - xvNum3;
            yTwo = yvNum1 - yvNum3;
            zTwo = zvNum1 - zvNum3;

            QVector3D productOfVectors;
            QVector3D leftVector(xOne, yOne, zOne);
            QVector3D rightVector(xTwo, yTwo, zTwo);

            productOfVectors = QVector3D::crossProduct(leftVector,rightVector);
            arr2return.append(productOfVectors);

        }
    }

    return arr2return;
}




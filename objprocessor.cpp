#include "objprocessor.h"
#include <QFile>
#include <QTextStream>
#include <QFile>
#include <polygon.h>
#include <QVector>
#include <QVector3D>
#include <qmath.h>
#include <QDebug>

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
            obj2return.vertices.append(QVector3D(xcor,ycor,zcor));
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

///Computes mean normals to every vertice, arranging it in the same order as a vertice array.
QVector<QVector3D> OBJprocessor::computeNormals(const QVector<Polygon> &inputPolygonArr, const QVector<QVector3D> &inputVertArr)
{
    int amountOfVerts = inputVertArr.count();
    int amountOfPolygons = inputPolygonArr.count();

    QVector<QVector3D> arr2return(amountOfVerts);
    QVector<QVector3D> emptyArr;

    int polygonCount = inputPolygonArr.count();
    for(int polygonIndex=0; polygonIndex<polygonCount;polygonIndex++){
        int numOfPolygonVerts = inputPolygonArr[polygonIndex].vertArr.count();
        for (int polygVertIndex = 0; polygVertIndex < numOfPolygonVerts; polygVertIndex++){
            int vertNumCurrent;
            int vertNumNext;
            int vertNumPrev;

            vertNumCurrent = inputPolygonArr[polygonIndex].vertArr[polygVertIndex];
            int cyclePrev;
            int cycleNext;
            cycleNext = (polygVertIndex+numOfPolygonVerts+2) % (numOfPolygonVerts);
            cyclePrev = (polygVertIndex+numOfPolygonVerts-1) % (numOfPolygonVerts);
            vertNumNext = inputPolygonArr[polygonIndex].vertArr[cycleNext];
            vertNumPrev = inputPolygonArr[polygonIndex].vertArr[cyclePrev];

            float xvNum1 = inputVertArr[vertNumCurrent-1].x();
            float yvNum1 = inputVertArr[vertNumCurrent-1].y();
            float zvNum1 = inputVertArr[vertNumCurrent-1].z();

            float xvNum2 = inputVertArr[vertNumNext-1].x();
            float yvNum2 = inputVertArr[vertNumNext-1].y();
            float zvNum2 = inputVertArr[vertNumNext-1].z();


            float xvNum3 = inputVertArr[vertNumPrev-1].x();
            float yvNum3 = inputVertArr[vertNumPrev-1].y();
            float zvNum3 = inputVertArr[vertNumPrev-1].z();

            float xOne, yOne, zOne = 0;
            float xTwo, yTwo, zTwo = 0;

            xOne = xvNum2 - xvNum1;
            yOne = yvNum2 - yvNum1;
            zOne = zvNum2 - zvNum1;

            xTwo = xvNum3 - xvNum1;
            yTwo = yvNum3 - yvNum1;
            zTwo = zvNum3 - zvNum1;

            QVector3D productOfVectors;
            QVector3D leftVector(xOne, yOne, zOne);
            QVector3D rightVector(xTwo, yTwo, zTwo);

            productOfVectors = QVector3D::crossProduct(leftVector,rightVector);
            arr2return[vertNumCurrent-1] += productOfVectors;
        }
    }

    for(int indexOfNormals=0; indexOfNormals < arr2return.count(); indexOfNormals++){
        arr2return[indexOfNormals].normalize();
    }
    return arr2return;
}

float OBJprocessor::errFuncForOneResidual(const QVector3D &pointOne, const QVector3D &pointTwo, const float rotation, const float shiftX, const float shiftY){
    float value2return;
    float rotX = pointOne.x()*cos(rotation) - pointOne.y()*sin(rotation);
    float rotY = pointOne.x()*sin(rotation) + pointOne.y()*cos(rotation);
    float transX = rotX + shiftX;
    float transY = rotY + shiftY;
    float residualX = transX - pointTwo.x();
    float residualY = transY - pointTwo.y();
    value2return = (residualX)*(residualX) + (residualY)*(residualY);
    return value2return;
}

QVector<float> OBJprocessor::getGrad(const QVector<QVector3D> &meshOne, const QVector<QVector3D> &meshTwo, const float rotation, const float shiftX, const float shiftY, const float shitfZ){
    QVector<float> prevPhaseVec;
    QVector<float> phaseVec;
    phaseVec.append(0);
    phaseVec.append(0);
    phaseVec.append(0);
    for(int j=0;j<meshOne.count();j++){
        prevPhaseVec = OBJprocessor::getGradientForOnePoint(meshOne[j],meshTwo[j],rotation,shiftX,shiftY,0);
        for(int i=0; i<phaseVec.count(); i++){
            phaseVec[i]+=prevPhaseVec[i];
        }
    }
    return phaseVec;
}

QVector<float> OBJprocessor::getGradientForOnePoint(const QVector3D &pointOne, const QVector3D &pointTwo, const float rotation, const float shiftX, const float shiftY, const float shitfZ)
{
    QVector<float> vector2return;
        float derivAlpha= 2*(pointOne.x()*cos(rotation)-pointOne.y()*sin(rotation)+shiftX-pointTwo.x())*(-pointOne.x()*sin(rotation)-pointOne.y()*cos(rotation)) +
                2*(pointOne.x()*sin(rotation)+pointOne.y()*cos(rotation)+shiftY-pointTwo.y())*(pointOne.x()*cos(rotation)-pointOne.y()*sin(rotation));
        float derivShiftX = 2*(pointOne.x()*cos(rotation)-pointOne.y()*sin(rotation)+shiftX-pointTwo.x());
        float derivShiftY = 2*(pointOne.x()*sin(rotation)+pointOne.y()*cos(rotation)+shiftY-pointTwo.y());

        vector2return.append(derivAlpha);
        vector2return.append(derivShiftX);
        vector2return.append(derivShiftY);

    float dFdA = (errFuncForOneResidual(pointOne,pointTwo,rotation+0.01,shiftX,shiftY) - errFuncForOneResidual(pointOne,pointTwo,rotation,shiftX,shiftY))/0.01;
    float dFdX = (errFuncForOneResidual(pointOne,pointTwo,rotation,shiftX+0.01,shiftY) - errFuncForOneResidual(pointOne,pointTwo,rotation,shiftX,shiftY))/0.01;
    float dFdY = (errFuncForOneResidual(pointOne,pointTwo,rotation,shiftX,shiftY+0.01) - errFuncForOneResidual(pointOne,pointTwo,rotation,shiftX,shiftY))/0.01;;

//    qDebug() << (derivAlpha - dFdA);
//    qDebug() << (derivShiftX - dFdX);
//    qDebug() << (derivShiftY - dFdY);
//    vector2return.append(dFdA);
//    vector2return.append(dFdX);
//    vector2return.append(dFdY);
    return vector2return;
}





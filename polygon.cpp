#include "polygon.h"

Polygon::Polygon()
{
}

Polygon::Polygon(const QStringList &objStringList)
{
    for(int i=0; i<objStringList.length();i++){
        if (objStringList.value(i) == "f")
            continue;
        else{
            int numVert = objStringList.value(i).split("/").value(0).toInt();
           vertArr.append(numVert);
        }
    }
    int a=0;
}

Polygon::Polygon(const QVector<int> &surfIntVect)
{
    for(int k=0; k<surfIntVect.length(); k++){
        vertArr.append(surfIntVect.value(k));
    }
}

int Polygon::vertex(int vertexInd) const
{
    return vertArr[vertexInd];
}

bool Polygon::operator== (const Polygon &b) const{
   for(int i=0;i<this->vertArr.length();i++){
        if(this->vertArr[i] != b.vertArr[i])
            return false;
        return true;
   }
}

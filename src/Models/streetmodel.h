#ifndef STREETMODEL_H
#define STREETMODEL_H
#include "src/tinyxml/tinystr.h"
#include "src/tinyxml/tinyxml.h"
#include "pointmodel.h"
#include <iostream>
#include <vector>
#include "basemodel.h"
using namespace std;
class StreetModel : public BaseModel
{
public:
    // name of the street
    string Name;
    // point, where street starts
    PointModel* StartPosition;
    // point, where street ends
    PointModel* EndPosition;
    // basic constructor
    StreetModel(unsigned int id = 0, string Name = "", PointModel* start = nullptr, PointModel* end = nullptr);
    // constructor for creating object from xml
    StreetModel(TiXmlElement* xml, vector<PointModel*> points);
    // debug function for printing models content on stdout
    virtual void Print(int indent) override;
    // if street is connected by StartPosition or EndPosition with STREET
    // returns pointer to one of this points, nullptr otherwise
    PointModel* IsConnectedBy(StreetModel* street);
    // returns lenght of the street
    double GetLength();
    // if POINT is StartPoint, returns EndPoint and conversely, nullptr otherwise
    PointModel* GetOppositePoint(PointModel* point);


};

#endif // STREETMODEL_H

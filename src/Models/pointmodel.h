#ifndef POINTMODEL_H
#define POINTMODEL_H

#include "src/tinyxml/tinystr.h"
#include "src/tinyxml/tinyxml.h"
#include "src/Models/basemodel.h"
// class representing 2d point
class PointModel : public BaseModel
{
public:
    // x coordinate
    int X;
    // y coordinate
    int Y;
    // basic constructor
    PointModel(unsigned int id = 0, int X = 0, int Y = 0);
    // constructor for creating object from xml
    PointModel(TiXmlElement* xml);
    // returns distance between obejct and POINT
    double GetDistanceFrom(PointModel* point);
    // debug function for printing models content on stdout
    virtual void Print(int indent) override;

};

#endif // POINTMODEL_H

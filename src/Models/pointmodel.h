#ifndef POINTMODEL_H
#define POINTMODEL_H

#include "src/tinyxml/tinystr.h"
#include "src/tinyxml/tinyxml.h"
#include "src/Models/basemodel.h"
#include <iostream>
#include <math.h>



// class representing 2d point
class PointModel : public BaseModel
{
public:
    // basic constructor
    PointModel(unsigned int id = 0, double X = 0, double Y = 0);
    // constructor for creating object from xml
    PointModel(TiXmlElement* xml);
    // vrátí souřadnici x
    double getX();
    // vrátí souřadnici y
    double getY();
    // returns distance between obejct and POINT
    double GetDistanceFrom(PointModel* point);
    // debug function for printing models content on stdout
    virtual void Print(int indent) override;

private:
    // x coordinate
    double X;
    // y coordinate
    double Y;


};

#endif // POINTMODEL_H

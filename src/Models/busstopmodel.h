#ifndef BUSSTOPMODEL_H
#define BUSSTOPMODEL_H
#include "src/Models/streetmodel.h"
#include "src/Models/basemodel.h"
#include "src/tinyxml/tinystr.h"
#include "src/tinyxml/tinyxml.h"
// class representing bus stop
class BusStopModel : public BaseModel
{
public:
    // pointer to street where bus stop is
    StreetModel* Street;
    // exact position
    PointModel* Position;
    // basic constructor
    BusStopModel(unsigned int id = 0, double Position = 0, StreetModel* Street = nullptr);
    // constructor for creating object from xml
    BusStopModel(TiXmlElement* xml, vector<StreetModel*> streets);
    // destructor
    ~BusStopModel();
    // debug function for printing models content on stdout
    virtual void Print(int indent) override;
    // returns lenght between bus stop and street's start point
    double DistanceFromStart();
    // returns lenght between bus stop and street's end point
    double DistanceFromEnd();
private:
    // calculates the Position property,
    // POSITION is number in range from 0 to 1 marking how far from start point bus stop id
    void CalculatePosition(double position);

};

#endif // BUSSTOPMODEL_H

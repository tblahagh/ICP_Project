#ifndef BUSSTOPMODEL_H
#define BUSSTOPMODEL_H
#include "src/Models/streetmodel.h"
#include "src/Models/basemodel.h"
#include "src/tinyxml/tinystr.h"
#include "src/tinyxml/tinyxml.h"
// class representing bus stop
using namespace std;

class BusStopModel : public BaseModel
{
public:

    // basic constructor
    BusStopModel(unsigned int id = 0, QString name = "", double Position = 0, StreetModel* Street = nullptr);
    // constructor for creating object from xml
    BusStopModel(TiXmlElement* xml, vector<StreetModel*> streets);
    // destructor
    ~BusStopModel();

    StreetModel* getStreet();
    PointModel* getPosition();
    double getPositionOnStreet();
    QString getName();

    void isCorrect();
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

    // pointer to street where bus stop is
    StreetModel* street;
    // exact position
    PointModel* position;

    double positionOnStreet = 0;
    // name
    QString name;

};

#endif // BUSSTOPMODEL_H

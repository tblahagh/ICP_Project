#ifndef BUSLINE_H
#define BUSLINE_H

#include "basemodel.h"
#include "busstopmodel.h"
#include <vector>
using namespace std;
class BusLineModel : public BaseModel
{
public:
    // name of the bus line
    string Name;
    // array of bus stops representing bus line
    vector<BusStopModel*> BusStops;
    // array of streets representing path of buses of the bus line
    vector<StreetModel*> Path;
    // basic constructor
    BusLineModel(unsigned int id = 0, string name = "", vector<BusStopModel*> busStops = {});
    // constructor for creating object from xml
    BusLineModel(TiXmlElement* xml, vector<BusStopModel*> busStops, vector<StreetModel*> streets);
    // debug function for printing models content on stdout
    virtual void Print(int indent) override;
    // returns pointer to bus stop with identifier ID
    BusStopModel* GetBusStopById(const unsigned int id);
    // returns index of BUSSTOP in BusStops
    unsigned int GetIndexByBusStop(const BusStopModel* busStop);
    // returns vector of points between LEFTBUSSTOP and RIGHTBUSSTOP
    vector<PointModel*> GetPointsBetweenBusStops(BusStopModel* leftBusStop, BusStopModel* rightBusStop);
    // returns vector of streets between LEFTBUSSTOP and RIGHTBUSSTOP
    // if SKIP == true, function does not returns streets, where given bus stops are
    vector<StreetModel*> GetStreetsBetweenBusStops(BusStopModel* leftBusStop , BusStopModel* rightBusStop, bool skip = false);
    // returns index of STREET in Path
    unsigned int GetIndexOfStreet(StreetModel* street);
    // returns index of street in Path, where is BUSSTOP
    unsigned int GetStreetIndexByBusStop(BusStopModel* busStop);
    // returns distance between bus stops by their indexes
    double GetDistanceOfBusStops(unsigned int leftIndex, unsigned int rightIndex);
    // returns distance between LEFTBUSSTOP and RIGHTBUSSTOP
    double GetDistanceOfBusStops(BusStopModel* leftBusStop, BusStopModel* rightBusStop);

};

#endif // BUSLINE_H

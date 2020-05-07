#ifndef BUSLINE_H
#define BUSLINE_H

#include "basemodel.h"
#include "busstopmodel.h"
#include <vector>
using namespace std;
class BusLineModel : public BaseModel
{
public:
    // basic constructor
    BusLineModel(unsigned int id = 0, QString name = "", vector<BusStopModel*> busStops = {}, vector<int> times = {}, PathModel* path = NULL);
    // constructor for creating object from xml
    BusLineModel(TiXmlElement* xml, vector<BusStopModel*> busStops, vector<StreetModel*> streets);
    ~BusLineModel();
    // debug function for printing models content on stdout
    virtual void Print(int indent) override;
    // returns pointer to bus stop with identifier ID
    BusStopModel* GetBusStopById(int id);
    // returns index of BUSSTOP in BusStops
    unsigned int GetIndexByBusStop(BusStopModel* busStop);
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
    int getDurationInMinutes();

    QString getName();
    vector<BusStopModel*> getBusStops();
    vector<int> getTimes();
    PathModel* getPath();
    void isCorrect();

private:
    // name of the bus line
    QString Name = "";
    // array of bus stops representing bus line
    vector<BusStopModel*> BusStops;
    // array of streets representing path of buses of the bus line
    PathModel* Path = NULL;
    // times to next stop
    vector<int> Times;

};

#endif // BUSLINE_H

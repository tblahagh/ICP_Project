#ifndef BUSMODEL_H
#define BUSMODEL_H

#include "basemodel.h"
#include "buslinemodel.h"
#include "busstopmodel.h"
#include "pointmodel.h"
#include "clockmodel.h"
// class representing bus

using namespace std;

class ClockModel;

class BusModel : public BaseModel
{
public:
    // basic constructor
    BusModel(unsigned int id = 0, tm _startTime = {}, BusLineModel* _busLine = nullptr, ClockModel* _clockModel = nullptr);
    // return last bus stop, which bus visited on its way
    BusStopModel* LastVisitedBusStop();
    // return next bus stop, which bus has to visit or nullptr if bus ended its ride
    BusStopModel* NextBusStop();
    // return current position of bus
    PointModel CurrentPosition();
    // debug function for printing object content to stdout
    void Print(int indent) override;

    bool actualizePosition(); // if false - destruct
    bool goToNextStreet();
    void goToNextStop();

    BusLineModel* getBusLine();
    bool getOpenedDetail();
    void setOpenedDetail(bool op);
    tm getStartTime();
    int getNextStopIndex();

private:
    // pointer to bus line, which is related to this bus
    BusLineModel* busLine = NULL;

    ClockModel* clockModel = NULL;
    int delay;
    tm startTime;

    tm lastActualizeTime;
    double actualSpeed = 0; // in points / seconds

    unsigned int indexOfNextStop = 0;
    double positionOnActualStreet = 0;
    bool directionStartToEnd = true; // direction on actual street


    vector<double> usualSpeedOnPath = {};
    vector<unsigned int> indexOfActualStreetOnPath = {};
    vector<PathModel*> actualPaths = {};
    vector<bool> actualDirectionOnPath = {};


    bool openedDetail = false;
    bool qdebug = false;
};

#endif // BUSMODEL_H

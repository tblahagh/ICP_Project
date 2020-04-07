#ifndef BUSMODEL_H
#define BUSMODEL_H

#include "basemodel.h"
#include "buslinemodel.h"
#include "timesetmodel.h"
#include "busstopmodel.h"
#include "pointmodel.h"
// class representing bus
class BusModel : public BaseModel
{
public:
    // pointer to bus line, which is related to this bus
    BusLineModel* BusLine;
    // pointer to time set, which is related to this bus
    TimeSetModel* TimeSet;
    // basic constructor
    BusModel(unsigned int id = 0, BusLineModel* busLine = nullptr, TimeSetModel* timeSet = nullptr);
    // return last bus stop, which bus visited on its way
    BusStopModel* LastVisitedBusStop();
    // return next bus stop, which bus has to visit or nullptr if bus ended its ride
    BusStopModel* NextBusStop();
    // return current position of bus
    PointModel CurrentPosition();
    // debug function for printing object content to stdout
    void Print(int indent) override;

};

#endif // BUSMODEL_H

#ifndef TIMETABLEMODEL_H
#define TIMETABLEMODEL_H

#include "basemodel.h"
#include "buslinemodel.h"
#include "busmodel.h"
#include <vector>

using namespace std;
class TimeTableModel : public BaseModel
{
public:

    // basic contructor
    TimeTableModel(unsigned int id = 0, BusLineModel* busLine = nullptr, vector<tm> startTimes = {});
    // constructor for creating object from xml
    TimeTableModel(TiXmlElement* xml, vector<BusLineModel*> busLines);
    // destructor
    ~TimeTableModel();

    vector<tm> getStartTimes();
    BusLineModel* getBusLine();

    void isCorrect();
/*
    // returns all active buses of this time table
    vector<BusModel> GetActiveBuses();
    // returns bus stop from BusLine with indexed by INDEX
    BusStopModel* GetBusStopByIndex(const unsigned int index);
    // returns bus stop from BusLine with identifier ID
    BusStopModel * GetBusStopById(const unsigned int id);
    // returns all todays time sets
    vector<TimeSetModel*> GetTodayTimeSets();
    // returns all todays active time sets
    vector<TimeSetModel*> GetTodayActualTimeSets();*/
    // debug function for printing models content on stdout
    virtual void Print(int indent) override;

private:
    // vector of time sets of this time table
    vector<tm> StartTimes;
    // pointer to bus line, which is related to time table
    BusLineModel* BusLine;
};

#endif // TIMETABLEMODEL_H

#ifndef TIMESET_H
#define TIMESET_H
#include <ctime>
#include <vector>
using namespace std;

#include "src/Models/basemodel.h"
// class representing set of times for each bus stop in specific bus line
class TimeSetModel : public BaseModel
{
public:
    // vector of times
    vector<tm> Times;
    // basic constructor
    TimeSetModel(unsigned int id = 0, vector<tm> times = {});
    // constructor for creating object from xml
    TimeSetModel(TiXmlElement* xml);
    // returns first time in vector
    tm GetFirstTime();
    // returns last time in vector
    tm GetLastTime();
    // if IsActual == true, returns time, that is closest to present time from left
    tm GetActualTime();
    // returns time from Times by INDEX
    tm GetTimeByIndex(const unsigned int index);
    // returns time between times given by their indexes
    tm GetTimeBetween(unsigned int left, unsigned int right);
    // returns index of actual time
    unsigned int GetIndexOfActualTime();
    // returns if present time is between first and last time in Times
    bool IsActual();
    // returns true if time set does not contains any times
    bool IsEmpty();
    // returns true if time set passes midnight
    bool CrossesDay();
    // debug function for printing models content on stdout
    virtual void Print(int indent) override;
private:
    // debug function for printing time to stdout
    void PrintTime(tm time);
};

#endif // TIMESET_H

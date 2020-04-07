#ifndef MAPMODEL_H
#define MAPMODEL_H
#include <vector>
#include "src/Models/streetmodel.h"
#include "src/Models/busstopmodel.h"
#include "src/Models/pointmodel.h"
#include "src/Models/buslinemodel.h"
#include "src/Models/timetablemodel.h"
using namespace std;
// class representing whole map
class MapModel
{
public:
    // width of map
    int width;
    // height of map
    int height;
    // points with which streets are connected
    vector<PointModel*> Points;
    // all streets of the map
    vector<StreetModel*> Streets;
    // all bus stops of the map
    vector<BusStopModel*> BusStops;
    // all bus lines of the map
    vector<BusLineModel*> BusLines;
    // time tables for bus lines
    vector<TimeTableModel*> TimeTables;
    // basic constructor
    MapModel();
    // destructor
    ~MapModel();
    // debug function for printing map content to stdout
    void Print();
};

#endif // MAPMODEL_H

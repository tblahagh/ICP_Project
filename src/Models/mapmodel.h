#ifndef MAPMODEL_H
#define MAPMODEL_H
#include <vector>
#include "src/Models/streetmodel.h"
#include "src/Models/pathmodel.h"
#include "src/Models/busstopmodel.h"
#include "src/Models/pointmodel.h"
#include "src/Models/buslinemodel.h"
#include "src/Models/busmodel.h"
#include "src/Models/clockmodel.h"
#include "src/Models/timetablemodel.h"
#include <iostream>

using namespace std;

class TimeTableModel;
class ClockModel;
class BusModel;
class PathModel;
class BusStopModel;
class PointModel;
class BusLineModel;
class StreetModel;
class MainWindow;

// class representing whole map
class MapModel
{
public:
    // getters
    double getWidth();
    double getHeight();
    vector<PointModel*> getPoints();
    vector<StreetModel*> getStreets();
    vector<BusStopModel*> getBusStops();
    vector<BusLineModel*> getBusLines();
    vector<TimeTableModel*> getTimeTables();
    vector<BusModel*> getBuses();

    // add
    void addPoint(PointModel* point);
    void addStreet(StreetModel* street);
    void addBusStop(BusStopModel* busStop);
    void addBusLine(BusLineModel* busLine);
    void addTimeTable(TimeTableModel* timeTable);
    void deleteBus(vector<BusModel*> *buses, BusModel* bus);

    // load buses
    void loadBuses(ClockModel* clock);
    void actualizeBuses(ClockModel* clock);
    // get street which contains point
    StreetModel* getStreetByPoint(PointModel *point, double zoom);
    BusStopModel* getBusStopByPoint(PointModel *point, double zoom);
    BusModel* getBusByPoint(PointModel *point, double zoom);

    // basic constructor
    MapModel(MainWindow* _mainWindow);
    // destructor
    ~MapModel();
    // debug function for printing map content to stdout
    void Print();

private:
    MainWindow* mainWindow;
    // width of map
    double width;
    // height of map
    double height;
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
    // buses on the map
    vector<BusModel*> Buses;

    tm lastActualizeBuses = {};
};

#endif // MAPMODEL_H

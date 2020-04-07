#include "mapmodel.h"
using namespace std;
#include <iostream>
MapModel::MapModel()
{

}
MapModel::~MapModel()
{

    for (TimeTableModel* timeTable :TimeTables)
        delete timeTable;
    for (BusLineModel* busLine: BusLines)
        delete busLine;
    for (BusStopModel* busStop : BusStops)
        delete busStop;
    for (StreetModel* street : Streets)
        delete street;
    for (PointModel* point : Points)
        delete point;

}
void MapModel::Print()
{
  /*  cout << "Width: " << this->width << endl << "Height: " << this->height << endl;
    cout << "Points:\n";*/

    /*for (PointModel* point : Points)
    {
        point->Print();
    }
    cout << "Streets:\n";

    for (StreetModel* street : Streets)
    {
        street->Print();
    }*/
   /* cout << "Bus Stops:\n";
    for (BusStopModel* busStop : BusStops)
    {
        busStop->Print();
    }*/
    /*cout << "Bus Lines:\n";
    for (BusLineModel* busLine : BusLines)
    {
        busLine->Print(0);
    }*/
    cout << "Time Tables:\n";
    for (TimeTableModel* timeTable : TimeTables)
    {
        timeTable->Print(0);
    }

}

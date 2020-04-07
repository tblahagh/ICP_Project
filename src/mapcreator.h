#ifndef MAPCREATOR_H
#define MAPCREATOR_H
#include <vector>
#include "Models/mapmodel.h"
#include "Models/streetmodel.h"
#include "Models/pointmodel.h"
#include "Models/busstopmodel.h"
#include "Models/buslinemodel.h"
#include "Models/timesetmodel.h"
#include "Models/timetablemodel.h"
#include "tinyxml/tinystr.h"
#include "tinyxml/tinyxml.h"
// class representing creator of the map
class MapCreator
{
public:
    // basic contructor
    MapCreator();
    // function parse XML file with name FILENAME and returns created map
    MapModel CreateMap(string filename);
private:

    // function creates and returns points from XML
    vector<PointModel*> CreatePoints(TiXmlNode *xml);
    // function creates and returns streets from XML
    vector<StreetModel*> CreateStreets(TiXmlNode* xml, const vector<PointModel*> points);
    // function creates and returns bus stops from XML
    vector<BusStopModel*> CreateBusStops(TiXmlNode* xml, const vector<StreetModel*> streets);
    // function creates and returns bus lines from XML
    vector<BusLineModel*> CreateBusLines(TiXmlNode* xml, const vector<BusStopModel*> busStops, const vector<StreetModel*> streets);
    // function creates and returns time tables from XML
    vector<TimeTableModel*> CreateTimeTables(TiXmlNode* xml, const vector<BusLineModel*> busLines);
};
#endif // MAPCREATOR_H

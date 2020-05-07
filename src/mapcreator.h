#ifndef MAPCREATOR_H
#define MAPCREATOR_H
#include <vector>
#include "Models/mapmodel.h"
#include "Models/streetmodel.h"
#include "Models/pointmodel.h"
#include "Models/pathmodel.h"
#include "Models/busstopmodel.h"
#include "Models/buslinemodel.h"
#include "Models/timetablemodel.h"
#include "tinyxml/tinystr.h"
#include "tinyxml/tinyxml.h"
#include <fstream>
#include <iostream>
#include <string>
// class representing creator of the map

using namespace std;

class MapModel;
class StreetModel;
class PointModel;
class BusStopModel;
class BusLineModel;
class TimeSetModel;
class TimeTableModel;
class PathModel;

class MapCreator
{
public:
    // basic contructor
    MapCreator();
    // function parse XML file with name FILENAME and returns created map
    MapModel *CreateMap(string filename, MainWindow* _mainWindow);
private:

    // function creates and returns points from XML
    void CreatePoints(TiXmlNode *xml, MapModel* map);
    // function creates and returns streets from XML
    void CreateStreets(TiXmlNode* xml, MapModel* map);
    // function creates and returns bus stops from XML
    void CreateBusStops(TiXmlNode* xml, MapModel* map);
    // function creates and returns bus lines from XML
    void CreateBusLines(TiXmlNode* xml, MapModel* map);
    // function creates and returns time tables from XML
    void CreateTimeTables(TiXmlNode* xml, MapModel* map);


};
#endif // MAPCREATOR_H

#include "mapcreator.h"


#include <fstream>
#include <iostream>
#include <string>
using namespace std;
// class representing creator of the map
MapCreator::MapCreator()
{

}


vector<PointModel*> MapCreator::CreatePoints(TiXmlNode *xml)
{
    vector<PointModel*> points;
    TiXmlNode* xmlPoint = nullptr;
    while ((xmlPoint = xml->IterateChildren(xmlPoint)) != nullptr)
    {
        points.push_back(new PointModel(xmlPoint->ToElement()));
    }
    return points;
}
vector<StreetModel*> MapCreator::CreateStreets(TiXmlNode* xml, const vector<PointModel*> points)
{
    vector<StreetModel*> streets;
    TiXmlNode *xmlStreet = nullptr;
    while ((xmlStreet = xml->IterateChildren(xmlStreet)) != nullptr)
    {
       StreetModel* street = new StreetModel(xmlStreet->ToElement(), points);
       streets.push_back(street);
    }
    return streets;
}


vector<BusStopModel*> MapCreator::CreateBusStops(TiXmlNode* xml, const vector<StreetModel*> streets)
{
    vector<BusStopModel*> busStops;
    TiXmlNode* xmlBusStop = nullptr;
    while ((xmlBusStop = xml->IterateChildren(xmlBusStop)) != nullptr)
    {
        TiXmlElement* xmlBusStopElement = xmlBusStop->ToElement();
        BusStopModel* busStop = new BusStopModel(xmlBusStopElement, streets);
        busStops.push_back(busStop);
    }
    return busStops;
}
vector<BusLineModel*> MapCreator::CreateBusLines(TiXmlNode* xml, const vector<BusStopModel*> busStops, const vector<StreetModel*> streets)
{
    vector<BusLineModel*> busLines;
    TiXmlNode *xmlBusLine = nullptr;
    while ((xmlBusLine = xml->IterateChildren(xmlBusLine)) != nullptr)
    {  
        BusLineModel* busLine = new BusLineModel(xmlBusLine->ToElement(), busStops, streets);
        busLines.push_back(busLine);
    }
    return busLines;
}

vector<TimeTableModel*> MapCreator::CreateTimeTables(TiXmlNode* xml, const vector<BusLineModel*> busLines)
{
    vector<TimeTableModel*> timeTables ={};
    TiXmlNode* xmlTimeTable = nullptr;
    while ((xmlTimeTable = xml->IterateChildren(xmlTimeTable)) != nullptr)
    {
        TimeTableModel* timeTable = new TimeTableModel(xmlTimeTable->ToElement(), busLines);
        timeTables.push_back(timeTable);
    }
    return timeTables;
}
MapModel MapCreator::CreateMap(string filename)
{
    TiXmlDocument document(filename.c_str());
    MapModel map = MapModel();
    bool load = document.LoadFile();
 //   TiXmlNode * child = nullptr;
    if (load == true)
    {
        TiXmlElement* xmlMap = document.RootElement();
        if (xmlMap->QueryIntAttribute("width", &map.width) != TIXML_SUCCESS)
            cerr << "Could not resolve width" << endl;
        if (xmlMap->QueryIntAttribute("height", &map.height) != TIXML_SUCCESS)
            cerr << "Could not resolve height" << endl;
        map.Points = CreatePoints(xmlMap->FirstChild("points"));
        map.Streets = CreateStreets(xmlMap->FirstChild("streets"), map.Points);
        map.BusStops = CreateBusStops(xmlMap->FirstChild("busstops"), map.Streets);
        map.BusLines = CreateBusLines(xmlMap->FirstChild("buslines"), map.BusStops, map.Streets);
        map.TimeTables = CreateTimeTables(xmlMap->FirstChild("timetables"), map.BusLines);
    }
    return map;

}



#include "mapcreator.h"

//********************************************************************************
// konstruktory, destruktory
//--------------------------------------------------------------------------------

//-------------------------------------------------------------
// Základní konstruktor
MapCreator::MapCreator()
{

}

//********************************************************************************
// výpočetní metody
//--------------------------------------------------------------------------------

//-----------------------------------------------------------------
// Metoda vytvoří modely bodů z XML uzlu a vloží je do mapy
void MapCreator::CreatePoints(TiXmlNode *xml, MapModel* map)
{
    TiXmlNode* xmlPoint = nullptr;
    while ((xmlPoint = xml->IterateChildren(xmlPoint)) != nullptr)
    {
        map->addPoint(new PointModel(xmlPoint->ToElement()));
    }
}

//-----------------------------------------------------------------
// Metoda vytvoří modely ulic z XML uzlu a vloží je do mapy
void MapCreator::CreateStreets(TiXmlNode* xml, MapModel* map)
{
    TiXmlNode *xmlStreet = nullptr;
    while ((xmlStreet = xml->IterateChildren(xmlStreet)) != nullptr)
    {
       StreetModel* street = new StreetModel(xmlStreet->ToElement(), map->getPoints());
       map->addStreet(street);
    }
}

//---------------------------------------------------------------
// Metoda vytvoří modely zastávek z XML uzlu a vloží je do mapy
void MapCreator::CreateBusStops(TiXmlNode* xml, MapModel* map)
{
    TiXmlNode* xmlBusStop = nullptr;
    while ((xmlBusStop = xml->IterateChildren(xmlBusStop)) != nullptr)
    {
        TiXmlElement* xmlBusStopElement = xmlBusStop->ToElement();
        BusStopModel* busStop = new BusStopModel(xmlBusStopElement, map->getStreets());
        map->addBusStop(busStop);
    }
}

//--------------------------------------------------------------
// Metoda vytvoří modely autobusových linek z XML uzlu a vloží je do mapy
void MapCreator::CreateBusLines(TiXmlNode* xml, MapModel* map)
{
    TiXmlNode *xmlBusLine = nullptr;
    while ((xmlBusLine = xml->IterateChildren(xmlBusLine)) != nullptr)
    {  
        BusLineModel* busLine = new BusLineModel(xmlBusLine->ToElement(), map->getBusStops(), map->getStreets());
        map->addBusLine(busLine);
    }

}


//----------------------------------------------------------------
// Metoda vytvoří modely jízdních řádů z XML uzlu a vloží je do mapy
void MapCreator::CreateTimeTables(TiXmlNode* xml, MapModel* map)
{
    TiXmlNode* xmlTimeTable = nullptr;
    while ((xmlTimeTable = xml->IterateChildren(xmlTimeTable)) != nullptr)
    {
        TimeTableModel* timeTable = new TimeTableModel(xmlTimeTable->ToElement(), map->getBusLines());
        map->addTimeTable(timeTable);
    }

}

//-------------------------------------------------------------------
// vytvoří mapu
MapModel *MapCreator::CreateMap(string filename, MainWindow* _mainWindow)
{
    if(_mainWindow == NULL) throw new QString("Nepodařilo se vytvořit mapu");
    TiXmlDocument document(filename.c_str());
    MapModel *map = new MapModel(_mainWindow);
    bool load = document.LoadFile();
    if (load == true)
    {
        TiXmlElement* xmlMap = document.RootElement();
        int width = 0, height = 0;
        const char* title = xmlMap->Attribute("title");
        if (title == nullptr)
            throw new QString("Chybí vlastnost title");
        if ((xmlMap->QueryIntAttribute("width", &width)) != TIXML_SUCCESS)
            throw new QString("Chybí vlastnost width");
        if ((xmlMap->QueryIntAttribute("height", &height)) != TIXML_SUCCESS)
            throw new QString("Chybí vlastnost height");
        map->setTitle(title);
        map->setWidth(width);
        map->setHeight(height);
        CreatePoints(xmlMap->FirstChild("points"), map);
        CreateStreets(xmlMap->FirstChild("streets"), map);
        CreateBusStops(xmlMap->FirstChild("busstops"), map);
        CreateBusLines(xmlMap->FirstChild("buslines"), map);
        CreateTimeTables(xmlMap->FirstChild("timetables"), map);

    }
    else throw new QString("Nepodařilo se načíst soubor.");
    return map;

}



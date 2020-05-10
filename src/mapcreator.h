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
/**
 * Třída vytvářející model mapy z XML souboru
 */
class MapCreator
{
public:
    /**
     * Základní konstruktor
     */
    MapCreator();

    /**
     * Funkce vytvoří model mapy z XML, vyhodí výjimku pokud nastane chyba při čtení souboru
     * @param filename Jméno souboru s XML
     * @param _mainWindow Okno aplikace
     * @return Ukazatel na vytvořenou mapu
     */
    MapModel *CreateMap(string filename, MainWindow* _mainWindow);
private:

    /**
     * Metoda vytvoří modely bodů z XML uzlu a vloží je do mapy
     * @param xml XML uzel, ze kterého se body vytvářejí
     * @param map Mapa do které se body přidají
     */
    void CreatePoints(TiXmlNode *xml, MapModel* map);
    /**
     * Metoda vytvoří modely ulic z XML uzlu a vloží je do mapy
     * @param xml XML uzel, ze kterého se ulice vytvářejí
     * @param map Mapa do které se ulice přidají
     */
    void CreateStreets(TiXmlNode* xml, MapModel* map);
    /**
     * Metoda vytvoří modely zastávek z XML uzlu a vloží je do mapy
     * @param xml XML uzel, ze kterého se zastávky vytvářejí
     * @param map Mapa do které se zastávky přidají
     */
    void CreateBusStops(TiXmlNode* xml, MapModel* map);
    /**
     * Metoda vytvoří modely autobusových linek z XML uzlu a vloží je do mapy
     * @param xml XML uzel, ze kterého se linky vytvářejí
     * @param map Mapa do které se linky přidají
     */
    void CreateBusLines(TiXmlNode* xml, MapModel* map);
    /**
     * Metoda vytvoří modely jízdních řádů z XML uzlu a vloží je do mapy
     * @param xml XML uzel, ze kterého se řády vytvářejí
     * @param map Mapa do které se řády přidají
     */
    void CreateTimeTables(TiXmlNode* xml, MapModel* map);


};
#endif // MAPCREATOR_H

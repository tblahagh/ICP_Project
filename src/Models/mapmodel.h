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

/**
 * Třída reprezentující celou mapu
 */
class MapModel
{
public:

    /**
     * Základní kostruktor
     * @param _mainWindow Okno aplikace
     */
    MapModel(MainWindow* _mainWindow);

    /**
     * Destruktor
     */
    ~MapModel();

    /**
     * Ladící metoda pro výpis obsahu modelu na standartní výstup
     * @param Počet tabulátorů před výpisem
     */
    void Print();

    /**
     * Funkce vrací šířku mapy
     * @return Šířka mapy
     */
    double getWidth();

    /**
     * Funkce vrací výšky mapy
     * @return Výška mapy
     */
    double getHeight();

    /**
     * Funkce vrací název mapy
     * @return Název mapy
     */
    QString getTitle();

    /**
     * Funkce vrací body, kterými jsou na mapě ulice propojeny
     * @return Pole ukazatelů na body
     */
    vector<PointModel*> getPoints();

    /**
     * Funkce vrací ulice, ze kterých se mapa skládá
     * @return Pole ukazatelů na ulice, ze kterých se mapa skládá
     */
    vector<StreetModel*> getStreets();

    /**
     * Funkce vrací autobusové zastávky na mapě
     * @return Pole ukazatelů na zastávky na mapě
     */
    vector<BusStopModel*> getBusStops();

    /**
     * Funkce vrací autobusové linky, které jsou vytvořeny ze zastávek
     * @return Pole ukazatelů na autobusové linky mapy
     */
    vector<BusLineModel*> getBusLines();

    /**
     * Funkce vrací jízdní řády, kterými se řídí autobusové linky
     * @return Pole ukazatelů na jízdní řády
     */
    vector<TimeTableModel*> getTimeTables();

    /**
     * Funkce vrací autobusy, které jsou současně na trase
     * @return Pole ukazatelů na autobusy
     */
    vector<BusModel*> getBuses();

    /**
     * Metoda nastaví šířku mapy
     * @param width Nová šířka mapy
     */
    void setWidth(double width);

    /**
     * Metoda nastaví výšku mapy
     * @param height Nová výška mapy
     */
    void setHeight(double height);

    /**
     * Metoda nastaví název mapy
     * @param title Nový název mapy
     */
    void setTitle(QString title);

    /**
     * Metoda přidá bod do mapy
     * @param point Nový bod
     */
    void addPoint(PointModel* point);

    /**
     * Metoda přidá ulici do mapy
     * @param street Nová ulice
     */
    void addStreet(StreetModel* street);

    /**
     * Metoda přidá autobusovou zastávku do mapy
     * @param busStop Nová zastávka
     */
    void addBusStop(BusStopModel* busStop);

    /**
     * Metoda přidá autobusovou linku do mapy
     * @param busLine Nová linka
     */
    void addBusLine(BusLineModel* busLine);

    /**
     * Metoda přidá nový jízdní řád do mapy
     * @param timeTable Nový jízdní řád
     */
    void addTimeTable(TimeTableModel* timeTable);



    /**
     * Metoda vytvoří autobusy podle času hodin
     * @param clock Hodiny podle kterých se autobusy vytvařejí
     */
    void loadBuses(ClockModel* clock);

    /**
     * Metoda aktualizuje autobusy podle času hodin
     * @param clock Hodiny podle kterých se autobusy aktualizují
     */
    void actualizeBuses(ClockModel* clock);

    /**
     * Funkce vrací ulici podle bodu
     * @param point Bod, podle kterého se ulice hledá
     * @param zoom Zvětšení mapy, které je třeba zohlednit
     * @return Ukazatel na ulici, na které se bod nachází
     */
    StreetModel* getStreetByPoint(PointModel *point, double zoom);

    /**
     * Funkce vrací autobusovou zastávku podle bodu
     * @param point Bod, podle kterého se zastávka hledá
     * @param zoom Zvětšení mapy, které je třeba zohlednit
     * @return Ukazatel na zastávku
     */
    BusStopModel* getBusStopByPoint(PointModel *point, double zoom);

    /**
     * Funkce vrací autobus podle bodu
     * @param point Bod, podle kterého se autobus hledá
     * @param zoom Zvětšení mapy, které je třeba zohlednit
     * @return Ukazatel na autobus
     */
    BusModel* getBusByPoint(PointModel *point, double zoom);





private:

    /**
     * Okno aplikace
     */
    MainWindow* mainWindow;

    /**
     * Název mapy
     */
    QString title;

    /**
     * Šířka mapy
     */
    double width;
    /**
     * Výška mapy
     */
    double height;
    /**
     * Body, kterými jsou ulice mapy propojeny
     */
    vector<PointModel*> Points;
    /**
     * Ulice, ze který se mapa skládá
     */
    vector<StreetModel*> Streets;
    /**
     * Autobusové zastávky na mapě
     */
    vector<BusStopModel*> BusStops;
    /**
     * Autobusové linky na mapě
     */
    vector<BusLineModel*> BusLines;
    /**
     * Jízdní řády autobusových linek
     */
    vector<TimeTableModel*> TimeTables;
    /**
     * Autobusy na cestě
     */
    vector<BusModel*> Buses;

    tm lastActualizeBuses = {};

    void deleteBus(vector<BusModel*> *buses, BusModel* bus);
};

#endif // MAPMODEL_H

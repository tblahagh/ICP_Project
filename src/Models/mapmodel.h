/*
 * Autoři: Tomáš Blaha, Vojtěch Wawreczka
 * Datum: 9.5.2020
 *
 * Třída reprezentující celou mapu
 * */
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
 * @brief Třída reprezentující celou mapu
 */
class MapModel
{
public:

    /**
     * @brief Základní kostruktor
     * @param _mainWindow Okno aplikace
     */
    MapModel(MainWindow* _mainWindow);

    /**
     * @brief Destruktor
     */
    ~MapModel();

    /**
     * @brief Ladící metoda pro výpis obsahu modelu na standartní výstup
     */
    void Print();

    /**
     * @brief Funkce vrací šířku mapy
     * @return Šířka mapy
     */
    double getWidth();

    /**
     * @brief Funkce vrací výšky mapy
     * @return Výška mapy
     */
    double getHeight();

    /**
     * @brief Funkce vrací název mapy
     * @return Název mapy
     */
    QString getTitle();

    /**
     * @brief Funkce vrací body, kterými jsou na mapě ulice propojeny
     * @return Pole ukazatelů na body
     */
    vector<PointModel*> getPoints();

    /**
     * @brief Funkce vrací ulice, ze kterých se mapa skládá
     * @return Pole ukazatelů na ulice, ze kterých se mapa skládá
     */
    vector<StreetModel*> getStreets();

    /**
     * @brief Funkce vrací autobusové zastávky na mapě
     * @return Pole ukazatelů na zastávky na mapě
     */
    vector<BusStopModel*> getBusStops();

    /**
     * @brief Funkce vrací autobusové linky, které jsou vytvořeny ze zastávek
     * @return Pole ukazatelů na autobusové linky mapy
     */
    vector<BusLineModel*> getBusLines();

    /**
     * @brief Funkce vrací jízdní řády, kterými se řídí autobusové linky
     * @return Pole ukazatelů na jízdní řády
     */
    vector<TimeTableModel*> getTimeTables();

    /**
     * @brief Funkce vrací autobusy, které jsou současně na trase
     * @return Pole ukazatelů na autobusy
     */
    vector<BusModel*> getBuses();

    /**
     * @brief Metoda nastaví šířku mapy
     * @param width Nová šířka mapy
     */
    void setWidth(double width);

    /**
     * @brief Metoda nastaví výšku mapy
     * @param height Nová výška mapy
     */
    void setHeight(double height);

    /**
     * @brief Metoda nastaví název mapy
     * @param title Nový název mapy
     */
    void setTitle(QString title);

    /**
     * @brief Metoda přidá bod do mapy
     * @param point Nový bod
     */
    void addPoint(PointModel* point);

    /**
     * @brief Metoda přidá ulici do mapy
     * @param street Nová ulice
     */
    void addStreet(StreetModel* street);

    /**
     * @brief Metoda přidá autobusovou zastávku do mapy
     * @param busStop Nová zastávka
     */
    void addBusStop(BusStopModel* busStop);

    /**
     * @brief Metoda přidá autobusovou linku do mapy
     * @param busLine Nová linka
     */
    void addBusLine(BusLineModel* busLine);

    /**
     * @brief Metoda přidá nový jízdní řád do mapy
     * @param timeTable Nový jízdní řád
     */
    void addTimeTable(TimeTableModel* timeTable);



    /**
     * @brief Metoda vytvoří autobusy podle času hodin
     * @param clock Hodiny podle kterých se autobusy vytvařejí
     */
    void loadBuses(ClockModel* clock);

    /**
     * @brief Metoda aktualizuje autobusy podle času hodin
     * @param clock Hodiny podle kterých se autobusy aktualizují
     */
    void actualizeBuses(ClockModel* clock);


    /**
     * @brief Funkce odstraní autobus, který ukončil trasu
     * @param buses Seznam modelů, odkud je potřeba autobus odstranit
     * @param bus Model autobusu, který je potřeba odstanit
     */
    void deleteBus(vector<BusModel*> *buses, BusModel* bus);

    /**
     * @brief Funkce vrací ulici podle bodu
     * @param point Bod, podle kterého se ulice hledá
     * @param zoom Zvětšení mapy, které je třeba zohlednit
     * @return Ukazatel na ulici, na které se bod nachází
     */
    StreetModel* getStreetByPoint(PointModel *point, double zoom);

    /**
     * @brief Funkce vrací autobusovou zastávku podle bodu
     * @param point Bod, podle kterého se zastávka hledá
     * @param zoom Zvětšení mapy, které je třeba zohlednit
     * @return Ukazatel na zastávku
     */
    BusStopModel* getBusStopByPoint(PointModel *point, double zoom);

    /**
     * @brief Funkce vrací autobus podle bodu
     * @param point Bod, podle kterého se autobus hledá
     * @param zoom Zvětšení mapy, které je třeba zohlednit
     * @return Ukazatel na autobus
     */
    BusModel* getBusByPoint(PointModel *point, double zoom);





private:

    /**
     * @brief Okno aplikace
     */
    MainWindow* mainWindow;

    /**
     * @brief Název mapy
     */
    QString title;

    /**
     * @brief Šířka mapy
     */
    double width;
    /**
     * @brief Výška mapy
     */
    double height;
    /**
     * @brief Body, kterými jsou ulice mapy propojeny
     */
    vector<PointModel*> Points;
    /**
     * @brief Ulice, ze který se mapa skládá
     */
    vector<StreetModel*> Streets;
    /**
     * @brief Autobusové zastávky na mapě
     */
    vector<BusStopModel*> BusStops;
    /**
     * @brief Autobusové linky na mapě
     */
    vector<BusLineModel*> BusLines;
    /**
     * @brief Jízdní řády autobusových linek
     */
    vector<TimeTableModel*> TimeTables;
    /**
     * @brief Autobusy na cestě
     */
    vector<BusModel*> Buses;

    /**
     * @brief Čas poslední aktualizace
     */
    tm lastActualizeBuses = {};

};

#endif // MAPMODEL_H

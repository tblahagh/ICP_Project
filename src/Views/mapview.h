/*
 * Autoři: Tomáš Blaha, Vojtěch Wawreczka
 * Datum: 9.5.2020
 * */
#ifndef MAPVIEW_H
#define MAPVIEW_H
#include <QWidget>
#include <QHBoxLayout>
#include <QPainter>
#include <QtWidgets>
#include <iostream>
#include <vector>
#include "src/Models/mapmodel.h"
#include "src/mainwindow.h"
#include "streetview.h"
#include "busstopview.h"
#include "busview.h"

using namespace std;

class MainWindow;
class MapModel;
class BusView;
/**
 * Pohled celé mapy
 */
class MapView : public QWidget
{
    Q_OBJECT

public:
    /**
     * Základní kontruktor
     * @param _mainWindow Okno aplikace
     * @param parent Rodič pohledu
     */
    MapView(MainWindow* _mainWindow, QWidget *parent = nullptr);
    /**
     * Destruktor
     */
    ~MapView();
    /**
     * Metoda vykreslí mapu
     * @param event
     */
    void paintEvent(QPaintEvent *event);
    /**
     * Funkce vrací model mapy
     * @return Ukazatel na model mapy
     */
    MapModel* getMapModel();
    /**
     * Funkce vrací zoom mapy
     * @return Hodnota zoomu mapy
     */
    double getZoom();
    /**
     * Funkce vrací offset mapy
     * @return Hodnota offsetu mapy
     */
    double getOffset();
    /**
     * Funkce vrací mód mapy
     * @return Hodnota módu mapy
     */
    int getMode();
    /**
     * Metoda nastaví mód mapy
     * @param _mode Nový mód
     */
    void setMode(int _mode);
    /**
     * Funkce vrací pohled ulice
     * @param model Model ulice, jehož pohled chceme
     * @return Ukazatel na pohled ulice
     */
    StreetView* getStreetByModel(StreetModel* model);
    /**
     * Metoda vybere všechny ulice z trasy
     * @param path trasa, jejíž ulice se mají vybrat
     */
    void selectPath(PathModel* path);
    /**
     * Metoda vytvoří autobusy
     */
    void loadBuses();
    /**
     * Metoda zavře všechny otevřené detaily ulic
     */
    void closeStreets();
    /**
     * Metoda inicializuje pohled na novou mapu
     * @param map Nová mapa
     */
    void selectMap(MapModel* map);

public slots:
    /**
     * Metodá zvýší zoom
     */
    void increaseZoom();
    /**
     * Metoda sníží zoom
     */
    void decreaseZoom();


protected:
    /**
     * Metoda, která se provede při kliknutí na mapu
     * @param event
     */
    void mousePressEvent(QMouseEvent *event);

private:
    /**
     * Okno aplikace
     */
    MainWindow *mainWindow;
    /**
     * Model mapy
     */
    MapModel* mapModel;
    /**
     * Pohledy ulic
     */
    vector<StreetView*> streets;
    /**
     * Pohledy zastávek
     */
    vector<BusStopView*> busStops;
    /**
     * Pohledy autobusů
     */
    vector<BusView*> buses;
    /**
     * Zoom
     */
    double zoom = 1;
    /**
     * Offset
     */
    double offset = 10;
    /**
     * Mód
     */
    int mode = 0;
};

#endif // MAPVIEW_H

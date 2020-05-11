/*
 * Autoři: Tomáš Blaha, Vojtěch Wawreczka
 * Datum: 9.5.2020
 *
 * Pohled celé mapy
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
 * @brief Pohled celé mapy
 */
class MapView : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Základní kontruktor
     * @param _mainWindow Okno aplikace
     * @param parent Rodič pohledu
     */
    MapView(MainWindow* _mainWindow, QWidget *parent = nullptr);
    /**
     * @brief Destruktor
     */
    ~MapView();
    /**
     * @brief Metoda vykreslí mapu
     * @param event
     */
    void paintEvent(QPaintEvent *event);
    /**
     * @brief Funkce vrací model mapy
     * @return Ukazatel na model mapy
     */
    MapModel* getMapModel();
    /**
     * @brief Funkce vrací zoom mapy
     * @return Hodnota zoomu mapy
     */
    double getZoom();
    /**
     * @brief Funkce vrací offset mapy
     * @return Hodnota offsetu mapy
     */
    double getOffset();
    /**
     * @brief Funkce vrací mód mapy
     * @return Hodnota módu mapy
     */
    int getMode();
    /**
     * @brief Metoda nastaví mód mapy
     * @param _mode Nový mód
     */
    void setMode(int _mode);
    /**
     * @brief Funkce vrací pohled ulice
     * @param model Model ulice, jehož pohled chceme
     * @return Ukazatel na pohled ulice
     */
    StreetView* getStreetByModel(StreetModel* model);
    /**
     * @brief Metoda vybere všechny ulice z trasy
     * @param path trasa, jejíž ulice se mají vybrat
     */
    void selectPath(PathModel* path);
    /**
     * @brief Metoda vytvoří autobusy
     */
    void loadBuses();
    /**
     * @brief Metoda zavře všechny otevřené detaily ulic
     */
    void closeStreets();
    /**
     * @brief Metoda inicializuje pohled na novou mapu
     * @param map Nová mapa
     */
    void selectMap(MapModel* map);

public slots:
    /**
     * @brief Metodá zvýší zoom
     */
    void increaseZoom();
    /**
     * @brief Metoda sníží zoom
     */
    void decreaseZoom();


protected:
    /**
     * @brief Metoda, která se provede při kliknutí na mapu
     * @param event
     */
    void mousePressEvent(QMouseEvent *event);

private:
    /**
     * @brief Okno aplikace
     */
    MainWindow *mainWindow;
    /**
     * @brief Model mapy
     */
    MapModel* mapModel;
    /**
     * @brief Pohledy ulic
     */
    vector<StreetView*> streets;
    /**
     * @brief Pohledy zastávek
     */
    vector<BusStopView*> busStops;
    /**
     * @brief Pohledy autobusů
     */
    vector<BusView*> buses;
    /**
     * @brief Zoom
     */
    double zoom = 1;
    /**
     * @brief Offset
     */
    double offset = 10;
    /**
     * @brief Mód
     */
    int mode = 0;
};

#endif // MAPVIEW_H

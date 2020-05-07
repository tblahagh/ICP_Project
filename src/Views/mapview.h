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

class MapView : public QWidget
{
    Q_OBJECT

public:
    // konstruktor
    MapView(MapModel *_mapModel, MainWindow* _mainWindow, QWidget *parent = nullptr);
    // destruktor
    ~MapView();
    // vykreslení mapy
    void paintEvent(QPaintEvent *event);
    // vrátí model mapy
    MapModel* getMapModel();
    // vrátí zoom
    double getZoom();
    // vrátí offset
    double getOffset();
    // vrátí mod
    int getMode();
    // nastavení modu
    void setMode(int _mode);
    // vrati pohled ulice podle modelu
    StreetView* getStreetByModel(StreetModel* model);
    void selectPath(PathModel* path);
    void loadBuses();
    void closeStreets();


public slots:
    // zvýšit zoom
    void increaseZoom();
    // snížit zoom
    void decreaseZoom();


protected:
    // kliknutí na mapu
    void mousePressEvent(QMouseEvent *event);

private:
    // hlavni okno
    MainWindow *mainWindow;
    // model mapy
    MapModel* mapModel;
    // pohledy ulic
    vector<StreetView*> streets;
    // pohledy zastavek
    vector<BusStopView*> busStops;
    // pohledy autobusu
    vector<BusView*> buses;
    // zoom
    double zoom = 1;
    //offset
    double offset = 10;
    // mod zobrazeni - 0-default, 1-path
    int mode = 0;
};

#endif // MAPVIEW_H

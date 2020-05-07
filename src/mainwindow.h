#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QHBoxLayout>
#include <QWidget>
#include <QSizePolicy>
#include <windows.h>

#include "src/Views/mapview.h"
#include "src/Views/clockview.h"
#include "src/Views/clockdetailview.h"
#include "src/Views/streetdetailview.h"
#include "src/Views/detourdetailview.h"
#include "src/Views/busstopdetailview.h"
#include "src/Views/busdetailview.h"
#include "src/Models/pathmodel.h"
#include "src/Models/basemodel.h"
#include "src/mapcreator.h"


#include <QPainter>

class ClockView;
class ClockDetailView;
class StreetDetailView;
class DetourDetailView;
class BusStopDetailView;
class BusDetailView;
class ClockModel;
class MapView;
class MapCreator;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void clockTicked();
    void closeDetail();
    void updateDetail();
    void clearWidget();
    void openStreetDetail(StreetView *view);
    void openDetourDetail(StreetView *view);
    void openBusStopDetail(BusStopView *view);
    void openBusDetail(BusView *view);
    void mapUpdate();
    void selectStreetOnDetour(StreetView *view);
    void deselectStreetsOnDetour();
    void closeBusDetail(BusModel* bus);
    void showException(const QString *text);
    void clockInitialized();

public slots:
    void increaseMapZoom();
    void decreaseMapZoom();
    void openClockDetail();

private:
    // centrální umístění
    QWidget * central = NULL;
    // základní hbox
    QHBoxLayout *layout;
    // vbox pro detaily a nastavení
    QVBoxLayout *vbox;
    // widget pro nastaveni
    QWidget *widget;
    // widget - velikost pro scroll area
    QWidget *scrollWidget;
    // scroll area pro mapu
    QScrollArea *scroll;

    // objekt pro vytvoření mapy
    MapCreator *creator = NULL;
    // model mapy
    MapModel *mapModel = NULL;
    // pohled pro mapu
    MapView *mapView;

    // model pro hodiny
    ClockModel *clockModel = NULL;
    // pohled pro hodiny
    ClockView *clockView;
    // tlačítko pro úpravu hodin
    QPushButton *btnClockEdit;
    // zobrazeni hodin
    QLabel *labelClock;

    // tlačítka pro zoom +, -
    QPushButton *btnZoomPlus;
    QPushButton *btnZoomMinus;

    // label pro hlaseni exception
    QLabel *exceptionLabel = NULL;

    // detail hodin
    ClockDetailView *clockDetailView = NULL;
    // detail ulice
    StreetDetailView *streetDetailView = NULL;
    // detail objížďky
    DetourDetailView *detourDetailView = NULL;
    // detail zastávky
    BusStopDetailView *busStopDetailView = NULL;
    // detail autobusu
    BusDetailView *busDetailView = NULL;

};
#endif // MAINWINDOW_H

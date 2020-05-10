/*
 * Autoři: Tomáš Blaha, Vojtěch Wawreczka
 * Datum: 9.5.2020
 * */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QHBoxLayout>
#include <QWidget>
#include <QSizePolicy>


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
/**
 * Hlavní okno aplikace
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    /**
     * Konstruktor, provede inicializaci všech komponent okna
     * @param parent Rodič okna
     */
    MainWindow(QWidget *parent = 0);

    /**
     * Destruktor
     */
    ~MainWindow();
    /**
     * Metoda zobrazí nový čas na hodinách po tiknutí
     */
    void clockTicked();
    /**
     * Metoda zavře všechny detaily
     */
    void closeDetail();
    /**
     * Metoda aktualizuje všechny detaily
     */
    void updateDetail();
    /**
     * Metoda vyčistí plochu detailu
     */
    void clearWidget();
    /**
     * Metoda otevře detail ulice
     * @param view Pohled ulice která se má zobrazit
     */
    void openStreetDetail(StreetView *view);
    /**
     * Metoda otevře detail objížďky
     * @param view Pohled ulice, které se objížďka týká
     */
    void openDetourDetail(StreetView *view);
    /**
     * Metoda otevře detail autobusové zastávky
     * @param view Pohled autobusové zastávky, která se má zobrazit
     */
    void openBusStopDetail(BusStopView *view);
    /**
     * Metoda otevře detail autobusu
     * @param view Pohled autobusu, který se má zobrazit
     */
    void openBusDetail(BusView *view);
    /**
     * Metoda aktualizuje pohled mapy
     */
    void mapUpdate();
    /**
     * Metoda vloží ulici do vytvářené objíždky
     * @param view Pohled ulice, která má být přidána
     */
    void selectStreetOnDetour(StreetView *view);
    /**
     * Metoda odstraní ulici z vytvářené objíždky
     * @param view Pohled ulice, která má být odstraněna
     */
    void deselectStreetsOnDetour();
    /**
     * Metoda zavře detail autobusu
     * @param view Autobus, jehož model má být zavřen
     */
    void closeBusDetail(BusModel* bus);
    /**
     * Metoda zobrazí výjimku
     * @param text Text výjimky
     */
    void showException(const QString *text);
    /**
     * Metoda provede akce po inicializaci hodin
     */
    void clockInitialized();

public slots:
    /**
     * Metoda zvýší zoom mapy
     */
    void increaseMapZoom();
    /**
     * Metoda sníží zoom mapy
     */
    void decreaseMapZoom();
    /**
     * Metoda otevře detail hodin
     */
    void openClockDetail();
    /**
     * Metoda otevře průzkumník souborů pro výběr mapy
     */
    void openFileDialog();
private:


    /**
     * Centrální umístění
     */
    QWidget * central = NULL;
    /**
     * Základní hbox
     */
    QHBoxLayout *layout;
    /**
     * Vbox pro detaily a nastavení
     */
    QVBoxLayout *vbox;

    /**
     * Widget pro nastaveni
     */
    QWidget *widget;
    //
    /**
     * Widget - velikost pro scroll area
     */
    QWidget *scrollWidget;
    //
    /**
     * Scroll area pro mapu
     */
    QScrollArea *scroll;

    //
    /**
     * Objekt pro vytvoření mapy
     */
    MapCreator *creator = NULL;
    //
    /**
     * Model mapy
     */
    MapModel *mapModel = NULL;
    //
    /**
     * Pohled pro mapu
     */
    MapView *mapView;
    /**
     * Popisek s názvem mapy
     */
    QLabel *labelMapFile;
    /**
     * Tlačítko pro otevření průzkumníku souborů pro výběr mapy
     */
    QPushButton* btnMapFileSelect;
    /**
     * Model hodin
     */
    ClockModel *clockModel = NULL;

    /**
     * Pohled hodin
     */
    ClockView *clockView;
    /**
     * Tlačítko pro úpravu hodin
     */
    QPushButton *btnClockEdit;

    /**
     * Zobrazení hodin
     */
    QLabel *labelClock;

    /**
     * Zoom popisek
     */
    QLabel *labelZoom;

    /**
     * Tlačítka pro zoom
     */
    QPushButton *btnZoomPlus;
    QPushButton *btnZoomMinus;

    /**
     * Popisek pro hlášení chyb
     */
    QLabel *exceptionLabel = NULL;

    /**
     * Detail hodin
     */
    ClockDetailView *clockDetailView = NULL;
    /**
     * Detail ulice
     */
    StreetDetailView *streetDetailView = NULL;
    /**
     * Detail objížďky
     */
    DetourDetailView *detourDetailView = NULL;
    /**
     * Detail zastávky
     */
    BusStopDetailView *busStopDetailView = NULL;
    /**
     * Detail autobusu
     */
    BusDetailView *busDetailView = NULL;
    /**
     * Indikátor jestli je otevřena mapa
     */
    bool mapSelected;
};
#endif // MAINWINDOW_H

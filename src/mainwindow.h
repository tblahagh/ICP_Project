/*
 * Autoři: Tomáš Blaha, Vojtěch Wawreczka
 * Datum: 9.5.2020
 *
 * Hlavní okno aplikace
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
 * @brief Hlavní okno aplikace
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    /**
     * @brief Konstruktor, provede inicializaci všech komponent okna
     * @param parent Rodič okna
     */
    MainWindow(QWidget *parent = 0);

    /**
     * @brief Destruktor
     */
    ~MainWindow();
    /**
     * @brief Metoda zobrazí nový čas na hodinách po tiknutí
     */
    void clockTicked();
    /**
     * @brief Metoda zavře všechny detaily
     */
    void closeDetail();
    /**
     * @brief Metoda aktualizuje všechny detaily
     */
    void updateDetail();
    /**
     * @brief Metoda vyčistí plochu detailu
     */
    void clearWidget();
    /**
     * @brief Metoda otevře detail ulice
     * @param view Pohled ulice která se má zobrazit
     */
    void openStreetDetail(StreetView *view);
    /**
     * @brief Metoda otevře detail objížďky
     * @param view Pohled ulice, které se objížďka týká
     */
    void openDetourDetail(StreetView *view);
    /**
     * @brief Metoda otevře detail autobusové zastávky
     * @param view Pohled autobusové zastávky, která se má zobrazit
     */
    void openBusStopDetail(BusStopView *view);
    /**
     * @brief Metoda otevře detail autobusu
     * @param view Pohled autobusu, který se má zobrazit
     */
    void openBusDetail(BusView *view);
    /**
     * @brief Metoda aktualizuje pohled mapy
     */
    void mapUpdate();
    /**
     * @brief Metoda vloží ulici do vytvářené objíždky
     * @param view Pohled ulice, která má být přidána
     */
    void selectStreetOnDetour(StreetView *view);
    /**
     * @brief Metoda odstraní ulici z vytvářené objíždky
     */
    void deselectStreetsOnDetour();
    /**
     * @brief Metoda zavře detail autobusu
     * @param bus Autobus, jehož model má být zavřen
     */
    void closeBusDetail(BusModel* bus);
    /**
     * @brief Metoda zobrazí výjimku
     * @param text Text výjimky
     */
    void showException(const QString *text);
    /**
     * @brief Metoda provede akce po inicializaci hodin
     */
    void clockInitialized();

public slots:
    /**
     * @brief Metoda zvýší zoom mapy
     */
    void increaseMapZoom();
    /**
     * @brief Metoda sníží zoom mapy
     */
    void decreaseMapZoom();
    /**
     * @brief Metoda otevře detail hodin
     */
    void openClockDetail();
    /**
     * @brief Metoda otevře průzkumník souborů pro výběr mapy
     */
    void openFileDialog();
private:


    /**
     * @brief Centrální umístění
     */
    QWidget * central = NULL;
    /**
     * @brief Základní hbox
     */
    QHBoxLayout *layout;
    /**
     * @brief Vbox pro detaily a nastavení
     */
    QVBoxLayout *vbox;

    /**
     * @brief Widget pro nastaveni
     */
    QWidget *widget;

    /**
     * @brief Widget - velikost pro scroll area
     */
    QWidget *scrollWidget;

    /**
     * @brief Scroll area pro mapu
     */
    QScrollArea *scroll;

    /**
     * @brief Objekt pro vytvoření mapy
     */
    MapCreator *creator = NULL;

    /**
     * @brief Model mapy
     */
    MapModel *mapModel = NULL;

    /**
     * @brief Pohled pro mapu
     */
    MapView *mapView;
    /**
     * @brief Popisek s názvem mapy
     */
    QLabel *labelMapFile;
    /**
     * @brief Tlačítko pro otevření průzkumníku souborů pro výběr mapy
     */
    QPushButton* btnMapFileSelect;
    /**
     * @brief Model hodin
     */
    ClockModel *clockModel = NULL;

    /**
     * @brief Pohled hodin
     */
    ClockView *clockView;
    /**
     * @brief Tlačítko pro úpravu hodin
     */
    QPushButton *btnClockEdit;

    /**
     * @brief Zobrazení hodin
     */
    QLabel *labelClock;

    /**
     * @brief Zoom popisek
     */
    QLabel *labelZoom;

    /**
     * @brief Tlačítka pro zoom
     */
    QPushButton *btnZoomPlus;
    QPushButton *btnZoomMinus;

    /**
     * @brief Popisek pro hlášení chyb
     */
    QLabel *exceptionLabel = NULL;

    /**
     * @brief Detail hodin
     */
    ClockDetailView *clockDetailView = NULL;
    /**
     * @brief Detail ulice
     */
    StreetDetailView *streetDetailView = NULL;
    /**
     * @brief Detail objížďky
     */
    DetourDetailView *detourDetailView = NULL;
    /**
     * @brief Detail zastávky
     */
    BusStopDetailView *busStopDetailView = NULL;
    /**
     * @brief Detail autobusu
     */
    BusDetailView *busDetailView = NULL;
    /**
     * @brief Indikátor jestli je otevřena mapa
     */
    bool mapSelected;
};
#endif // MAINWINDOW_H

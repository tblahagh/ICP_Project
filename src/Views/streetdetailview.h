/*
 * Autoři: Tomáš Blaha, Vojtěch Wawreczka
 * Datum: 9.5.2020
 * */
#ifndef STREETDETAILVIEW_H
#define STREETDETAILVIEW_H
#include <QWidget>
#include <QMainWindow>
#include "src/mainwindow.h"
#include "streetview.h"

#include <QPushButton>
#include <QHBoxLayout>
#include <QSizePolicy>

using namespace std;

class MainWindow;
/**
 * Pohled detailu ulice
 */
class StreetDetailView : public QWidget
{
    Q_OBJECT

public:
    /**
     * Základní konstruktor
     * @param _streetView Ulice, které se detail týká
     * @param _mainWindow Okno aplikace
     * @param parent Rodič pohledu
     */
    StreetDetailView(StreetView* _streetView, MainWindow* _mainWindow, QWidget *parent = 0);
    /**
     * Destruktor
     */
    ~StreetDetailView();
    /**
     * Metoda vykreslí objížďku na widget
     * @param widget Widget na který se má objížďka vykreslit
     */
    void paint(QWidget *widget);

public slots:
    /**
     * Metoda volaná při stisku tlačítka uloží stav ulice
     */
    void btnSaveClicked();
    /**
     * Metoda volaná při stisku tlačítka zavře detail ulice
     */
    void btnCloseClicked();
    /**
     * Metoda volaná při stisku tlačítka otevře detail objížďky ulice
     */
    void btnDetourDetailClicked();

private:
    /**
     * Okno aplikace
     */
    MainWindow *mainWindow;
    /**
     * Model ulice
     */
    StreetView *streetView;

    /**
     * Layout
     */
    QGridLayout *layout = NULL;

    /**
     * Přepínače
     */
    QRadioButton *btnGreen;
    QRadioButton *btnOrange;
    QRadioButton *btnRed;
    QRadioButton *btnBlack;
    QButtonGroup *fieldTraffic;

    /**
     * Tlačítka
     */
    QPushButton *btnSave;
    QPushButton *btnClose;
    QPushButton *btnDetourDetail;

};

#endif // STREETDETAILVIEW_H


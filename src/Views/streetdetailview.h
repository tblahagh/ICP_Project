/*
 * Autoři: Tomáš Blaha, Vojtěch Wawreczka
 * Datum: 9.5.2020
 *
 * Pohled detailu ulice
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
 * @brief Pohled detailu ulice
 */
class StreetDetailView : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Základní konstruktor
     * @param _streetView Ulice, které se detail týká
     * @param _mainWindow Okno aplikace
     * @param parent Rodič pohledu
     */
    StreetDetailView(StreetView* _streetView, MainWindow* _mainWindow, QWidget *parent = 0);
    /**
     * @brief Destruktor
     */
    ~StreetDetailView();
    /**
     * @brief Metoda vykreslí objížďku na widget
     * @param widget Widget na který se má objížďka vykreslit
     */
    void paint(QWidget *widget);

public slots:
    /**
     * @brief Metoda volaná při stisku tlačítka uloží stav ulice
     */
    void btnSaveClicked();
    /**
     * @brief Metoda volaná při stisku tlačítka zavře detail ulice
     */
    void btnCloseClicked();
    /**
     * @brief Metoda volaná při stisku tlačítka otevře detail objížďky ulice
     */
    void btnDetourDetailClicked();

private:
    /**
     * @brief Okno aplikace
     */
    MainWindow *mainWindow;
    /**
     * @brief Model ulice
     */
    StreetView *streetView;

    /**
     * @brief Layout
     */
    QGridLayout *layout = NULL;

    /**
     * @brief Přepínače
     */
    QRadioButton *btnGreen;
    QRadioButton *btnOrange;
    QRadioButton *btnRed;
    QRadioButton *btnBlack;
    QButtonGroup *fieldTraffic;

    /**
     * @brief Tlačítka
     */
    QPushButton *btnSave;
    QPushButton *btnClose;
    QPushButton *btnDetourDetail;

};

#endif // STREETDETAILVIEW_H


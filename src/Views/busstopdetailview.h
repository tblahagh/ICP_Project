/*
 * Autoři: Tomáš Blaha, Vojtěch Wawreczka
 * Datum: 9.5.2020
 *
 * Pohled detailu autobusové zastávky
 * */
#ifndef BUSSTOPDETAILVIEW_H
#define BUSSTOPDETAILVIEW_H
#include <QWidget>
#include <QMainWindow>
#include "src/mainwindow.h"
#include "busstopview.h"

#include <QPushButton>
#include <QHBoxLayout>
#include <QSizePolicy>

using namespace std;

class MainWindow;
/**
 * @brief Pohled detailu autobusové zastávky
 */
class BusStopDetailView : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Základní konstruktor
     * @param _busStopView Pohled zastávky jejíž se detail týká
     * @param _mainWindow Okno aplikace
     * @param parent Rodič pohledu
     */
    BusStopDetailView(BusStopView* _busStopView, MainWindow* _mainWindow, QWidget *parent = 0);
    /**
     * @brief Destruktor
     */
    ~BusStopDetailView();
    /**
     * @brief Metoda vykreslí detail do widgetu
     * @param widget Widget, do kterého se má detail vykreslit
     */
    void paint(QWidget *widget);

public slots:
    /**
     * @brief Metoda zavření detailu
     */
    void btnCloseClicked();


private:
    /**
     * @brief Okno aplikace
     */
    MainWindow *mainWindow;

    /**
     * @brief Pohled zastávky
     */
    BusStopView *busStopView;

    /**
     * @brief Layout
     */
    QGridLayout *layout = NULL;

    /**
     * @brief Tlačítko pro zavření detailu
     */
    QPushButton *btnClose;

};

#endif // BUSSTOPDETAILVIEW_H

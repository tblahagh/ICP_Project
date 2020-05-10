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
 * Pohled detailu autobusové zastávky
 */
class BusStopDetailView : public QWidget
{
    Q_OBJECT

public:
    /**
     * Základní konstruktor
     * @param _busStopView Pohled zastávky jejíž se detail týká
     * @param _mainWindow Okno aplikace
     * @param parent Rodič pohledu
     */
    BusStopDetailView(BusStopView* _busStopView, MainWindow* _mainWindow, QWidget *parent = 0);
    /**
     * Destruktor
     */
    ~BusStopDetailView();
    /**
     * Metoda vykreslí detail do widgetu
     * @param widget Widget, do kterého se má detail vykreslit
     */
    void paint(QWidget *widget);

public slots:
    /**
     * Metoda zavření detailu
     */
    void btnCloseClicked();


private:
    /**
     * Okno aplikace
     */
    MainWindow *mainWindow;

    /**
     * Pohled zastávky
     */
    BusStopView *busStopView;

    /**
     * Layout
     */
    QGridLayout *layout = NULL;

    /**
     * Tlačítko pro zavření detailu
     */
    QPushButton *btnClose;

};

#endif // BUSSTOPDETAILVIEW_H

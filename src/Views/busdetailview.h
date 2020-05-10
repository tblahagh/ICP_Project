#ifndef BUSDETAILVIEW_H
#define BUSDETAILVIEW_H
#include <QWidget>
#include <QMainWindow>
#include "src/mainwindow.h"
#include "busview.h"

#include <QPushButton>
#include <QHBoxLayout>
#include <QSizePolicy>

using namespace std;

class MainWindow;
/**
 * Pohled detailu autobusu
 */
class BusDetailView : public QWidget
{
    Q_OBJECT

public:
    /**
     * Základní konstruktor
     * @param _busView Pohled autobusu jehož se detail týká
     * @param _mainWindow Okno aplikace
     * @param parent Rodič pohledu
     */
    BusDetailView(BusView* _busView, MainWindow* _mainWindow, QWidget *parent = 0);
    /**
     * Destruktor
     */
    ~BusDetailView();
    /**
     * Metoda vykreslí detail do widgetu
     * @param widget Widget, do kterého se má detail vykreslit
     */
    void paint(QWidget *widget);
    /**
     * Funkce vrací pohled autobusu, jehož se detail týká
     * @return Ukazatel na pohled autobusu
     */
    BusView* getBusView();

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
     * Pohled autobusu
     */
    BusView *busView;

    /**
     * Layout
     */
    QGridLayout *layout = NULL;
    /**
     * Tlačítko pro zavření detailu
     */
    QPushButton *btnClose;

};

#endif // BUSDETAILVIEW_H

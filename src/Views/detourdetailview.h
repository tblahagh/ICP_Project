#ifndef DETOURDETAILVIEW_H
#define DETOURDETAILVIEW_H
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
 * Pohled reprezentující objíďku na mapě
 */
class DetourDetailView : public QWidget
{
    Q_OBJECT

public:
    /**
     * Základní konstruktor
     * @param _streetView Ulice, které se objížďka týká
     * @param _mainWindow Okno aplikace
     * @param parent Rodič pohledu
     */
    DetourDetailView(StreetView* _streetView, MainWindow* _mainWindow, QWidget *parent = 0);

    /**
     * Destruktor
     */
    ~DetourDetailView();
    /**
     * Metoda vykreslí objížďku na widget
     * @param widget Widget na který se má objížďka vykreslit
     */
    void paint(QWidget *widget);
    /**
     * Metoda přidá ulici do objížďky
     * @param street Ulice, která se má přidat
     */
    void addStreet(StreetModel *street);
    /**
     * Metoda smaže všechny ulice z objížďky
     */
    void clearStreets();

public slots:
    /**
     * Metoda volaná při stisku tlačítka uloží stav objížďky
     */
    void btnSaveClicked();
    /**
     * Metoda volaná při stisku tlačítka smaže stav objížďky
     */
    void btnClearClicked();
    /**
     * Metoda volaná při stisku tlačítka zavře detail objížďky
     */
    void btnCloseClicked();

private:

    /**
     * Okno aplikace
     */
    MainWindow *mainWindow;
    /**
     * Model ulice, které se objížďka týká
     */
    StreetView *streetView;
    /**
     * Layout
     */
    QGridLayout *layout = NULL;
    /**
     * Textová pole
     */
    QLineEdit *fieldDelay;
    /**
     * Popisky
     */
    QLabel *labelPathInfo;
    /**
     * Tlačítka
     */
    QPushButton *btnSave;
    QPushButton *btnClear;
    QPushButton *btnClose;

    /**
     * Zadaná cesta objížďky
     */
    PathModel* path = NULL;

};

#endif // DETOURDETAILVIEW_H

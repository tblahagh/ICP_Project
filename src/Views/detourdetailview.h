/*
 * Autoři: Tomáš Blaha, Vojtěch Wawreczka
 * Datum: 9.5.2020
 *
 * Pohled reprezentující objíďku na mapě
 * */
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
 * @brief Pohled reprezentující objíďku na mapě
 */
class DetourDetailView : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Základní konstruktor
     * @param _streetView Ulice, které se objížďka týká
     * @param _mainWindow Okno aplikace
     * @param parent Rodič pohledu
     */
    DetourDetailView(StreetView* _streetView, MainWindow* _mainWindow, QWidget *parent = 0);

    /**
     * @brief Destruktor
     */
    ~DetourDetailView();
    /**
     * @brief Metoda vykreslí objížďku na widget
     * @param widget Widget na který se má objížďka vykreslit
     */
    void paint(QWidget *widget);
    /**
     * @brief Metoda přidá ulici do objížďky
     * @param street Ulice, která se má přidat
     */
    void addStreet(StreetModel *street);
    /**
     * @brief Metoda smaže všechny ulice z objížďky
     */
    void clearStreets();

public slots:
    /**
     * @brief Metoda volaná při stisku tlačítka uloží stav objížďky
     */
    void btnSaveClicked();
    /**
     * @brief Metoda volaná při stisku tlačítka smaže stav objížďky
     */
    void btnClearClicked();
    /**
     * @brief Metoda volaná při stisku tlačítka zavře detail objížďky
     */
    void btnCloseClicked();

private:

    /**
     * @brief Okno aplikace
     */
    MainWindow *mainWindow;
    /**
     * @brief Model ulice, které se objížďka týká
     */
    StreetView *streetView;
    /**
     * @brief Layout
     */
    QGridLayout *layout = NULL;
    /**
     * @brief Textová pole
     */
    QLineEdit *fieldDelay;
    /**
     * @brief Popisky
     */
    QLabel *labelPathInfo;
    /**
     * @brief Tlačítka
     */
    QPushButton *btnSave;
    QPushButton *btnClear;
    QPushButton *btnClose;

    /**
     * @brief Zadaná cesta objížďky
     */
    PathModel* path = NULL;

};

#endif // DETOURDETAILVIEW_H

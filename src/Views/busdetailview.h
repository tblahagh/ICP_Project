/*
 * Autoři: Tomáš Blaha, Vojtěch Wawreczka
 * Datum: 9.5.2020
 *
 * Pohled detailu autobusu
 * */
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
 * @brief Pohled detailu autobusu
 */
class BusDetailView : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Základní konstruktor
     * @param _busView Pohled autobusu jehož se detail týká
     * @param _mainWindow Okno aplikace
     * @param parent Rodič pohledu
     */
    BusDetailView(BusView* _busView, MainWindow* _mainWindow, QWidget *parent = 0);
    /**
     * @brief Destruktor
     */
    ~BusDetailView();
    /**
     * @brief Metoda vykreslí detail do widgetu
     * @param widget Widget, do kterého se má detail vykreslit
     */
    void paint(QWidget *widget);
    /**
     * @brief Funkce vrací pohled autobusu, jehož se detail týká
     * @return Ukazatel na pohled autobusu
     */
    BusView* getBusView();

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
     * @brief Pohled autobusu
     */
    BusView *busView;

    /**
     * @brief Layout
     */
    QGridLayout *layout = NULL;
    /**
     * @brief Tlačítko pro zavření detailu
     */
    QPushButton *btnClose;

};

#endif // BUSDETAILVIEW_H

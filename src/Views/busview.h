#ifndef BUSVIEW_H
#define BUSVIEW_H
#include <QWidget>
#include <QPainter>
#include <QtWidgets>
#include <iostream>
#include <vector>
#include "src/Models/busmodel.h"

using namespace std;

class BusModel;
/**
 * Pohled autobusu vykreslující se do mapy
 */
class BusView : public QWidget
{
public:
    /**
     * Základní konstruktor
     * @param _busModel Autobus, které se pohled týká
     * @param parent Rodič pohledu
     */
    BusView(BusModel* _busModel, QWidget *parent = nullptr);
    /**
     * Metoda vykreslí autobus
     * @param painter Plátno pro vykreslování
     * @param zoom Zvětšení mapy, které je třeba zohlednit
     * @param offset Offset od hrany mapy
     */
    void paint(QPainter *painter, double zoom, double offset);
    /**
     * Funkce vrací model autobusu, které se pohled týká
     * @return Ukazatel na model autobusu
     */
    BusModel* getBusModel();

    /**
     * Metoda nastaví autobus jako otevřený
     */
    void open();
    /**
     * Metoda nastaví autobus jako uzavřený
     */
    void close();

private:
    /**
     * Model autobusu
     */
    BusModel* busModel;
};


#endif // BUSVIEW_H

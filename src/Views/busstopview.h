/*
 * Autoři: Tomáš Blaha, Vojtěch Wawreczka
 * Datum: 9.5.2020
 * */
#ifndef BUSSTOPVIEW_H
#define BUSSTOPVIEW_H
#include <QWidget>
#include <QPainter>
#include <QtWidgets>
#include <iostream>
#include <vector>
#include "src/Models/busstopmodel.h"

using namespace std;
/**
 * Pohled který vykreslí zastávku na mapu
 */
class BusStopView : public QWidget
{
public:
    /**
     * Základní konstruktor
     * @param _busStopModel Zastávka, které se pohled týká
     * @param parent Rodič pohledu
     */
    BusStopView(BusStopModel* _busStopModel, QWidget *parent = nullptr);
    /**
     * Metoda vykreslí zastávku
     * @param painter Plátno pro vykreslování
     * @param zoom Zvětšení mapy, které je třeba zohlednit
     * @param offset Offset od hrany mapy
     */
    void paint(QPainter *painter, double zoom, double offset);
    /**
     * Funkce vrací model zastávky, které se pohled týká
     * @return Ukazatel na model zastávky
     */
    BusStopModel* getBusStopModel();

    /**
     * Metoda nastaví zastávku jako otevřenou
     */
    void open();
    /**
     * Metoda nastaví zastávku jako uzavřenou
     */
    void close();

private:
    /**
     * Model zastávky
     */
    BusStopModel* busStopModel;
    /**
     * Indikátor jestli je otevřený detail zastávky
     */
    bool opened = false;
};

#endif // BUSSTOPVIEW_H

/*
 * Autoři: Tomáš Blaha, Vojtěch Wawreczka
 * Datum: 9.5.2020
 *
 * Pohled který vykreslí zastávku na mapu
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
 * @brief Pohled který vykreslí zastávku na mapu
 */
class BusStopView : public QWidget
{
public:
    /**
     * @brief Základní konstruktor
     * @param _busStopModel Zastávka, které se pohled týká
     * @param parent Rodič pohledu
     */
    BusStopView(BusStopModel* _busStopModel, QWidget *parent = nullptr);
    /**
     * @brief Metoda vykreslí zastávku
     * @param painter Plátno pro vykreslování
     * @param zoom Zvětšení mapy, které je třeba zohlednit
     * @param offset Offset od hrany mapy
     */
    void paint(QPainter *painter, double zoom, double offset);
    /**
     * @brief Funkce vrací model zastávky, které se pohled týká
     * @return Ukazatel na model zastávky
     */
    BusStopModel* getBusStopModel();

    /**
     * @brief Metoda nastaví zastávku jako otevřenou
     */
    void open();
    /**
     * @brief Metoda nastaví zastávku jako uzavřenou
     */
    void close();

private:
    /**
     * @brief Model zastávky
     */
    BusStopModel* busStopModel;
    /**
     * @brief Indikátor jestli je otevřený detail zastávky
     */
    bool opened = false;
};

#endif // BUSSTOPVIEW_H

/*
 * Autoři: Tomáš Blaha, Vojtěch Wawreczka
 * Datum: 9.5.2020
 * */
#ifndef STREETVIEW_H
#define STREETVIEW_H
#include <QWidget>
#include <QPainter>
#include <QtWidgets>
#include <iostream>
#include <vector>
#include "src/Models/streetmodel.h"

using namespace std;
/**
 * Pohled ulice vykreslující se do mapy
 */
class StreetView : public QWidget
{
public:
    /**
     * Základní konstruktor
     * @param _busModel ulice, které se pohled týká
     * @param parent Rodič pohledu
     */
    StreetView(StreetModel* _streetModel, QWidget *parent = nullptr);
    /**
     * Metoda vykreslí ulici
     * @param painter Plátno pro vykreslování
     * @param zoom Zvětšení mapy, které je třeba zohlednit
     * @param offset Offset od hrany mapy
     */
    void paint(QPainter *painter, double zoom, double offset, int mode);
    /**
     * Funkce vrací model ulice, které se pohled týká
     * @return Ukazatel na model ulice
     */
    StreetModel* getStreetModel();

    /**
     * Metoda nastaví ulici jako otevřenou
     */
    void open();
    /**
     * Metoda nastaví ulici jako uzavřenou
     */
    void close();
    /**
     * Metoda nastaví ulici jako vybranou
     */
    void select();
    /**
     * Metoda nastaví ulici jako nevybranou
     */
    void deselect();

private:
    /**
     * Model ulice
     */
    StreetModel* streetModel;
    /**
     * Indikátor jestli je otevřený detail ulice
     */
    boolean opened = false;
    /**
     * Indikátor jestli je ulice vybraná
     */
    boolean selected = false;
};

#endif // STREETVIEW_H

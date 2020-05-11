/*
 * Autoři: Tomáš Blaha, Vojtěch Wawreczka
 * Datum: 9.5.2020
 *
 * Pohled ulice vykreslující se do mapy
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
 * @brief Pohled ulice vykreslující se do mapy
 */
class StreetView : public QWidget
{
public:
    /**
     * @brief Základní konstruktor
     * @param _streetModel ulice, které se pohled týká
     * @param parent Rodič pohledu
     */
    StreetView(StreetModel* _streetModel, QWidget *parent = nullptr);
    /**
     * @brief Metoda vykreslí ulici
     * @param painter Plátno pro vykreslování
     * @param zoom Zvětšení mapy, které je třeba zohlednit
     * @param offset Offset od hrany mapy
     */
    void paint(QPainter *painter, double zoom, double offset, int mode);
    /**
     * @brief Funkce vrací model ulice, které se pohled týká
     * @return Ukazatel na model ulice
     */
    StreetModel* getStreetModel();

    /**
     * @brief Metoda nastaví ulici jako otevřenou
     */
    void open();
    /**
     * @brief Metoda nastaví ulici jako uzavřenou
     */
    void close();
    /**
     * @brief Metoda nastaví ulici jako vybranou
     */
    void select();
    /**
     * @brief Metoda nastaví ulici jako nevybranou
     */
    void deselect();

private:
    /**
     * @brief Model ulice
     */
    StreetModel* streetModel;
    /**
     * @brief Indikátor jestli je otevřený detail ulice
     */
    bool opened = false;
    /**
     * @brief Indikátor jestli je ulice vybraná
     */
    bool selected = false;
};

#endif // STREETVIEW_H

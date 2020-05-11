/*
 * Autoři: Tomáš Blaha, Vojtěch Wawreczka
 * Datum: 9.5.2020
 *
 * Pohled autobusu vykreslující se do mapy
 * */
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
 * @brief Pohled autobusu vykreslující se do mapy
 */
class BusView : public QWidget
{
public:
    /**
     * @brief Základní konstruktor
     * @param _busModel Autobus, které se pohled týká
     * @param parent Rodič pohledu
     */
    BusView(BusModel* _busModel, QWidget *parent = nullptr);
    /**
     * @brief Metoda vykreslí autobus
     * @param painter Plátno pro vykreslování
     * @param zoom Zvětšení mapy, které je třeba zohlednit
     * @param offset Offset od hrany mapy
     */
    void paint(QPainter *painter, double zoom, double offset);
    /**
     * @brief Funkce vrací model autobusu, které se pohled týká
     * @return Ukazatel na model autobusu
     */
    BusModel* getBusModel();

    /**
     * @brief Metoda nastaví autobus jako otevřený
     */
    void open();
    /**
     * @brief Metoda nastaví autobus jako uzavřený
     */
    void close();

private:
    /**
     * @brief Model autobusu
     */
    BusModel* busModel;
};


#endif // BUSVIEW_H

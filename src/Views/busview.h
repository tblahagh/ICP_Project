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

class BusView : public QWidget
{
public:
    // konstruktor
    BusView(BusModel* _busModel, QWidget *parent = nullptr);
    // vykreslení autobusu
    void paint(QPainter *painter, double zoom, double offset);
    // vrátí model autobusu
    BusModel* getBusModel();

    // vykreslí autobus s otevřeným detailem
    void open();
    // vykreslí autobus se zavřeným detailem
    void close();

private:
    // model autobusu
    BusModel* busModel;
};


#endif // BUSVIEW_H

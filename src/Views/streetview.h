#ifndef STREETVIEW_H
#define STREETVIEW_H
#include <QWidget>
#include <QPainter>
#include <QtWidgets>
#include <iostream>
#include <vector>
#include "src/Models/streetmodel.h"

using namespace std;

class StreetView : public QWidget
{
public:
    // konstruktor
    StreetView(StreetModel* _streetModel, QWidget *parent = nullptr);
    // vykreslení ulice
    void paint(QPainter *painter, double zoom, double offset, int mode);
    // vrátí model ulice
    StreetModel* getStreetModel();

    // vykreslí ulici s otevřeným detailem
    void open();
    // vykreslí ulici se zavřeným detailem
    void close();
    // vykresli vybranou ulici
    void select();
    // vykresli nevybranou ulici
    void deselect();

private:
    // model ulice
    StreetModel* streetModel;
    // otevřený detail ulice
    boolean opened = false;
    // vybrana ulice
    boolean selected = false;
};

#endif // STREETVIEW_H

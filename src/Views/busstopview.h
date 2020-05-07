#ifndef BUSSTOPVIEW_H
#define BUSSTOPVIEW_H
#include <QWidget>
#include <QPainter>
#include <QtWidgets>
#include <iostream>
#include <vector>
#include "src/Models/busstopmodel.h"

using namespace std;

class BusStopView : public QWidget
{
public:
    // konstruktor
    BusStopView(BusStopModel* _busStopModel, QWidget *parent = nullptr);
    // vykreslení zastávky
    void paint(QPainter *painter, double zoom, double offset);
    // vrátí model zastávky
    BusStopModel* getBusStopModel();

    // vykreslí zastávku s otevřeným detailem
    void open();
    // vykreslí zastávku se zavřeným detailem
    void close();

private:
    // model zastávky
    BusStopModel* busStopModel;
    // otevřený detail zastávky
    boolean opened = false;
};

#endif // BUSSTOPVIEW_H

#include "busstopview.h"

//****************************************************************************************
// konstruktory, destruktory, tisk
//--------------------------------------------------------------------------------------

//-----------------------------------------------------------------
// konstruktor
BusStopView::BusStopView(BusStopModel* _busStopModel, QWidget *parent) : QWidget(parent){

    if(_busStopModel == NULL) throw new QString("Nepodařilo se vytvořit BusStopView.");

    this->busStopModel = _busStopModel;

}

//*****************************************************************************************
// metody get, set, add
//-----------------------------------------------------------------------------------------

//----------------------------------------------------------------------
// vrací model zastávky
BusStopModel* BusStopView::getBusStopModel(){
    return this->busStopModel;
}

//-----------------------------------------------------------------------
// nastaví zastávku jako otevřenou
void BusStopView::open(){
    opened = true;
}

//--------------------------------------------------------------------------
// nastaví zastávku jako zavřenou
void BusStopView::close(){
    opened = false;
}

//***************************************************************************************
// metody pro vykreslení
//--------------------------------------------------------------------------------------

//---------------------------------------------------------------
// vykreslí ulici
void BusStopView::paint(QPainter *painter, double zoom, double offset){

    if(painter == NULL) throw new QString("Nepodařilo se vytvořit BusStopView.");

    painter->save();

    // vypln
    if(busStopModel->getStreet()->GetTraffic() == 0)
        painter->setBrush(QBrush(QColor("#000000"), Qt::SolidPattern));
    else
        painter->setBrush(QBrush(QColor("#00d1b8"), Qt::SolidPattern));

    //obrys
    QPen pen;
    pen.setWidth(1);
    pen.setColor(QString("grey"));
    if(opened){
        pen.setWidth(2);
        pen.setColor(QString("black"));
    }
    painter->setPen(pen);

    painter->drawRect(busStopModel->getPosition()->getX()*zoom+offset-5, busStopModel->getPosition()->getY()*zoom+offset-5, 10, 10);

    painter->restore();

}

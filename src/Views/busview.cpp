#include "busview.h"

//**************************************************************************************
// konstruktory, destruktory
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------
// konstruktor
BusView::BusView(BusModel* _busModel, QWidget *parent) : QWidget(parent){

    if(_busModel == NULL) throw new QString("Nepodařilo se vytvořit BusView.");

    this->busModel = _busModel;

}

//**************************************************************************************
// metody get, set, add
//---------------------------------------------------------------------------------------

//-------------------------------------------------------------
// vrací model ulice
BusModel* BusView::getBusModel(){
    return this->busModel;
}

//------------------------------------------------------------
// vykreslí ulici jako otevřenou
void BusView::open(){
    busModel->setOpenedDetail(true);
}

//--------------------------------------------------------------
// vykreslí ulici jako zavřenou
void BusView::close(){
    busModel->setOpenedDetail(false);
}


//**************************************************************************************
// metody pro vykreslení
//---------------------------------------------------------------------------------------

//----------------------------------------------------------------
// vykreslí ulici
void BusView::paint(QPainter *painter, double zoom, double offset){

    if(painter == NULL) throw new QString("Nepodařilo se vytvořit BusView.");

    painter->save();

    // vypln
    painter->setBrush(QBrush(QColor("#ff3030"), Qt::SolidPattern));

    //obrys
    QPen pen;
    pen.setWidth(1);
    pen.setColor(QString("grey"));
    if(busModel->getOpenedDetail()){
        pen.setWidth(2);
        pen.setColor(QString("black"));
    }
    painter->setPen(pen);

    painter->drawEllipse(busModel->CurrentPosition().getX()*zoom+offset-7.5, busModel->CurrentPosition().getY()*zoom+offset-7.5, 15, 15);

    painter->restore();

}

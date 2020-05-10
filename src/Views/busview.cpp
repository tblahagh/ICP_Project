#include "busview.h"

//**************************************************************************************
// konstruktory, destruktory
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------
// Základní konstruktor
BusView::BusView(BusModel* _busModel, QWidget *parent) : QWidget(parent){

    if(_busModel == NULL) throw new QString("Nepodařilo se vytvořit BusView.");

    this->busModel = _busModel;

}

//**************************************************************************************
// metody get, set, add
//---------------------------------------------------------------------------------------

//-------------------------------------------------------------
// Funkce vrací model autobusu, které se pohled týká
BusModel* BusView::getBusModel(){
    return this->busModel;
}

//------------------------------------------------------------
// Metoda nastaví autobus jako otevřený
void BusView::open(){
    busModel->setOpenedDetail(true);
}

//--------------------------------------------------------------
// Metoda nastaví autobus jako uzavřený
void BusView::close(){
    busModel->setOpenedDetail(false);
}


//**************************************************************************************
// metody pro vykreslení
//---------------------------------------------------------------------------------------

//----------------------------------------------------------------
// Metoda vykreslí autobus
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

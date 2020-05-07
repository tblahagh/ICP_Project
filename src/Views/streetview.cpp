#include "streetview.h"

//*************************************************************************************
// konstruktory, destruktory, tisk
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------
// konstruktor
StreetView::StreetView(StreetModel* _streetModel, QWidget *parent) : QWidget(parent){

    if(_streetModel == NULL) throw new QString("Nepodařilo se vytvořit StreetView.");

    this->streetModel = _streetModel;

}

//**********************************************************************************
// metody get, set, add
//----------------------------------------------------------------------------------

//---------------------------------------------------------------
// vrací model ulice
StreetModel* StreetView::getStreetModel(){
    return this->streetModel;
}

//--------------------------------------------------------------
// nastaví ulici jako otevřenou
void StreetView::open(){
    opened = true;
}

//------------------------------------------------------------
// nastaví ulici jako zavřenou
void StreetView::close(){
    opened = false;
}

//--------------------------------------------------------------
// nastaví ulici jako vybranou
void StreetView::select(){
    selected = true;
}

//------------------------------------------------------------
// nastaví ulici jako nevybranou
void StreetView::deselect(){
    selected = false;
}

//************************************************************************************
// metody pro vykreslení
//---------------------------------------------------------------------------------

//---------------------------------------------------------------------
// vykreslí ulici
void StreetView::paint(QPainter *painter, double zoom, double offset, int mode){

    if(painter == NULL) throw new QString("Nepodařilo se vytvořit StreetView.");

    painter->save();

    int weight = 2;
    if(opened) weight = 5;

    QPen pen = QPen(Qt::black, weight);

    if(mode == 0){
        switch(streetModel->GetTraffic()){
           case 0:
               pen.setColor(QString("black"));
           break;
           case 1:
               pen.setColor(QString("red"));
           break;
           case 2:
               pen.setColor(QString("orange"));
           break;
           case 3:
               pen.setColor(QString("green"));
           break;
           default:
           break;
        }
    }
    else if(mode == 1){
        if(streetModel->GetTraffic() == 0) pen.setColor(QString("black"));
        else if(selected == true) pen.setColor(QString("blue"));
        else pen.setColor(QString("grey"));
    }

    painter->setPen(pen);

    painter->drawLine(this->streetModel->getStartPosition()->getX()*zoom+offset, this->streetModel->getStartPosition()->getY()*zoom+offset, this->streetModel->getEndPosition()->getX()*zoom+offset, this->streetModel->getEndPosition()->getY()*zoom+offset);

    painter->restore();

}

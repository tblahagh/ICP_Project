#include "mapview.h"

//********************************************************************************
// konstruktory, destruktory, tisk
//---------------------------------------------------------------------------------

//-------------------------------------------------------------------
// Základní kontruktor
MapView::MapView(MainWindow* _mainWindow, QWidget *parent) : QWidget(parent) {

    if( _mainWindow == NULL) throw new QString("Nepodařilo se načíst mapu");

    this->mainWindow = _mainWindow;




}

//---------------------------------------------------------------------
// Destruktor
MapView::~MapView(){


    for(StreetView *view : streets){
        delete view;
    }

    for(BusStopView *view : busStops){
        delete view;
    }

    for(BusView *view : buses){
        delete view;
    }

}


//****************************************************************************************
// metody get, set, add
//-------------------------------------------------------------------------------------

//---------------------------------------------------------------------
// Funkce vrací model mapy
MapModel* MapView::getMapModel(){
    return this->mapModel;
}

//----------------------------------------------------------------------
// Funkce vrací zoom mapy
double MapView::getZoom(){
    return this->zoom;
}

//------------------------------------------------------------------------
// Funkce vrací offset mapy
double MapView::getOffset(){
    return this->offset;
}

//---------------------------------------------------------------------
// Funkce vrací mód mapy
int MapView::getMode(){
    return this->mode;
}

//---------------------------------------------------------------------
// Metodá zvýší zoom
void MapView::increaseZoom(){
    if(zoom == 20) return;

    if(zoom >= 1) zoom++;
    else zoom += 0.1;
}

//--------------------------------------------------------------------
// Metoda sníží zoom
void MapView::decreaseZoom(){
    if(zoom == 0.1) return;

    if(zoom <= 1) zoom -= 0.1;
    else zoom--;
}

//--------------------------------------------------------------------
// Metoda nastaví mód mapy
void MapView::setMode(int _mode){
    if(_mode < 0 || _mode > 1) throw new QString("Nepovolena hodnota modu mapy");

    if(mode == 1 && _mode != 1){
        for(StreetView *street : streets){
            street->deselect();
        }
    }

    this->mode = _mode;
}

//---------------------------------------------------------------------
// Metoda vytvoří autobusy
void MapView::loadBuses(){
    buses.clear();
    for(BusModel *model : mapModel->getBuses()){
        BusView *view = new BusView(model);
        buses.push_back(view);
    }

}

//****************************************************************************************
// metody pro vykreslení
//-------------------------------------------------------------------------------------

//------------------------------------------------------------------
// Metoda vykreslí mapu
void MapView::paintEvent(QPaintEvent*){

    if (mapModel != nullptr)
    {

        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        try {
            for(StreetView *view : streets){
                view->paint(&painter, this->zoom, this->offset, this->mode);
            }

            if(mode == 0){

                for(BusStopView *view : busStops){
                    view->paint(&painter, this->zoom, this->offset);
                }

                for(BusView *view : buses){
                    view->paint(&painter, this->zoom, this->offset);
                }

            }
        }
        catch(const QString *exc){ mainWindow->showException(exc); }
    }
}


//******************************************************************************
// metody pro interakce s uživatelem
//------------------------------------------------------------------------------

//--------------------------------------------------------------
// Metoda, která se provede při kliknutí na mapu
void MapView::mousePressEvent(QMouseEvent *event){

    double x = (event->x()-offset)/zoom;
    double y = (event->y()-offset)/zoom;

    try{
        if(mode == 0){
            BusModel* bus = mapModel->getBusByPoint(new PointModel(0, x, y), zoom);

            if(bus != nullptr){
                for(BusView *view : buses){
                    if(view->getBusModel() == bus){
                        mainWindow->openBusDetail(view);
                        return;
                    }
                }
            }

            // zastavka
            BusStopModel* busStop = mapModel->getBusStopByPoint(new PointModel(0, x, y), zoom);

            if(busStop != nullptr){
                for(BusStopView *view : busStops){
                    if(view->getBusStopModel() == busStop){
                        mainWindow->openBusStopDetail(view);
                        return;
                    }
                }
            }

            // todo press bus / bus stop
        }

        StreetModel* street = mapModel->getStreetByPoint(new PointModel(0, x, y), zoom);

        if(street != nullptr){
            for(StreetView *view : streets){
                if(view->getStreetModel() == street){

                    if(mode == 0) mainWindow->openStreetDetail(view);
                    else if(mode == 1){
                        if(view->getStreetModel()->GetTraffic() == 0) return;
                        mainWindow->selectStreetOnDetour(view);
                    }
                    return;
                }
            }
        }
    }
    catch(const QString *exc){ mainWindow->showException(exc); }

}

//*************************************************************************************
// výpočetní metody
//-------------------------------------------------------------------------------------

//----------------------------------------------------------------------
// Funkce vrací pohled ulice
StreetView* MapView::getStreetByModel(StreetModel* model){

    if(model == NULL) throw new QString("Nebyl vybrán žádný model ulice");

    for(StreetView* street: streets){
        if(street->getStreetModel() == model) return street;
    }

    return nullptr;

}

//------------------------------------------------------------------------
// Metoda vybere všechny ulice z trasy
void MapView::selectPath(PathModel* path){

    for(StreetModel* model: path->getStreets()){
        getStreetByModel(model)->select();
    }

}

//-----------------------------------------------------------------------
// Metoda zavře všechny otevřené detaily ulic
void MapView::closeStreets(){
    for(StreetView *street: streets){
        street->close();
    }
}
//-----------------------------------------------------------------------
// Metoda inicializuje pohled na novou mapu
void MapView::selectMap(MapModel *map) {
    if (map == nullptr)
        throw new QString("Nepodařilo se načíst mapu");
    this->mapModel = map;
    for(StreetModel *model : mapModel->getStreets()){
        StreetView *view = new StreetView(model);
        streets.push_back(view);
    }

    for(BusStopModel *model : mapModel->getBusStops()){
        BusStopView *view = new BusStopView(model);
        busStops.push_back(view);
    }
}

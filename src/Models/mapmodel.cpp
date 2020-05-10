#include "mapmodel.h"
#include "src/TimeLib.h"

//***************************************************************************************
// konstruktory, destruktory a tisk
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
// Základní kostruktor
MapModel::MapModel(MainWindow* _mainWindow){

    if(_mainWindow == NULL) throw new QString("Nepodařilo se vytvořit mapu");
    Buses = vector<BusModel*>();
    this->mainWindow = _mainWindow;
}

//---------------------------------------------------------------------------------------
// Destruktor
MapModel::~MapModel()
{
    for (BusModel* bus : Buses)
        delete bus;
    for (TimeTableModel* timeTable :TimeTables)
        delete timeTable;
    for (BusLineModel* busLine: BusLines)
        delete busLine;
    for (BusStopModel* busStop : BusStops)
        delete busStop;
    for (StreetModel* street : Streets)
        delete street;
    for (PointModel* point : Points)
        delete point;
}

//--------------------------------------------------------------------------------------
// Ladící metoda pro výpis obsahu modelu na standartní výstup
void MapModel::Print()
{
    cout << "Width: " << this->width << endl << "Height: " << this->height << endl;
    cout << "Points:\n";

    for (PointModel* point : Points)
    {
        point->Print(0);
    }
    cout << "Streets:\n";

    for (StreetModel* street : Streets)
    {
        street->Print(0);
    }
    cout << "Bus Stops:\n";
    for (BusStopModel* busStop : BusStops)
    {
        busStop->Print(0);
    }
    cout << "Bus Lines:\n";
    for (BusLineModel* busLine : BusLines)
    {
        busLine->Print(0);
    }
    cout << "Time Tables:\n";
    for (TimeTableModel* timeTable : TimeTables)
    {
        timeTable->Print(0);
    }
    cout << "Buses:\n";
    for (BusModel* bus : Buses)
    {
        bus->Print(0);
    }

}

//******************************************************************************
// metody set, get, add
//------------------------------------------------------------------------------
// Metoda nastaví šířku mapy
void MapModel::setWidth(double width){
    this->width = width;
}
//------------------------------------------------------------------------------
// Metoda nastaví výšku mapy
void MapModel::setHeight(double height){
    this->height = height;
}
//------------------------------------------------------------------------------
// Metoda nastaví název mapy
void MapModel::setTitle(QString title){
    this->title = title;
}
//------------------------------------------------------------------------------
// Funkce vrací název mapy
QString MapModel::getTitle() {
    return this->title;
}
//----------------------------------------------------------------------
// Funkce vrací šířku mapy
double MapModel::getWidth(){
    return this->width;
}

//----------------------------------------------------------------------
// Funkce vrací výšky mapy
double MapModel::getHeight(){
    return this->height;
}

//-----------------------------------------------------------------------
// Funkce vrací body, kterými jsou na mapě ulice propojeny
vector<PointModel*> MapModel::getPoints(){
    return this->Points;
}

//-----------------------------------------------------------------------
// Funkce vrací ulice, ze kterých se mapa skládá
vector<StreetModel*> MapModel::getStreets(){
    return this->Streets;
}

//-----------------------------------------------------------------------
// Funkce vrací autobusové zastávky na mapě
vector<BusStopModel*> MapModel::getBusStops(){
    return this->BusStops;
}

//-----------------------------------------------------------------------
// Funkce vrací autobusové linky, které jsou vytvořeny ze zastávek
vector<BusLineModel*> MapModel::getBusLines(){
    return this->BusLines;
}

//-----------------------------------------------------------------------
// Funkce vrací jízdní řády, kterými se řídí autobusové linky
vector<TimeTableModel*> MapModel::getTimeTables(){
    return this->TimeTables;
}

//-----------------------------------------------------------------------
// Funkce vrací autobusy, které jsou současně na trase
vector<BusModel*> MapModel::getBuses(){
    return this->Buses;
}

//-----------------------------------------------------------------------
// Metoda přidá bod do mapy
void MapModel::addPoint(PointModel* point){

    if(point == NULL) throw new QString("Nebyl vybrán žádný bod.");
    if(std::count(this->Points.begin(), this->Points.end(), point))
        throw new QString("Tento bod je již v seznamu");

    this->Points.push_back(point);

    if(point->getX() > this->width) this->width = point->getX();
    if(point->getY() > this->height) this->height = point->getY();
}

//-----------------------------------------------------------------------
// Metoda přidá ulici do mapy
void MapModel::addStreet(StreetModel* street){

    if(street == NULL) throw new QString("Nebyla vybrána žádná ulice.");
    if(std::count(this->Streets.begin(), this->Streets.end(), street))
        throw new QString("Tato ulice je již v seznamu");

    this->Streets.push_back(street);
}

//-----------------------------------------------------------------------
// Metoda přidá autobusovou zastávku do mapy
void MapModel::addBusStop(BusStopModel *busStop){

    if(busStop == NULL) throw new QString("Nebyla vybrána žádná zastávka.");
    if(std::count(this->BusStops.begin(), this->BusStops.end(), busStop))
        throw new QString("Tato zastávka je již v seznamu");

    this->BusStops.push_back(busStop);
}

//-----------------------------------------------------------------------
// Metoda přidá autobusovou linku do mapy
void MapModel::addBusLine(BusLineModel *busLine){

    if(busLine == NULL) throw new QString("Nebyla vybrána žádná linka.");
    if(std::count(this->BusLines.begin(), this->BusLines.end(), busLine))
        throw new QString("Tato zastávka je již v seznamu");

    this->BusLines.push_back(busLine);
}

//-----------------------------------------------------------------------
// Metoda přidá nový jízdní řád do mapy
void MapModel::addTimeTable(TimeTableModel *timeTable){

    if(timeTable == NULL) throw new QString("Nebyl vybrán žádný jízdní řád.");
    if(std::count(this->TimeTables.begin(), this->TimeTables.end(), timeTable))
        throw new QString("Tento jízdní řád je již v seznamu");

    this->TimeTables.push_back(timeTable);
}

//******************************************************************************************
// výpočetní metody
//-------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------
// Funkce vrací ulici podle bodu
StreetModel* MapModel::getStreetByPoint(PointModel *point, double zoom){

    if(point == NULL) throw new QString("Nebyl vybrán žádný bod");

    double tolerance = 10/zoom;

    for(StreetModel* model: Streets){
        if(model->ContainsPoint(point, tolerance)) return model;

    }

    return nullptr;
}

//-------------------------------------------------------------------------
// Funkce vrací autobusovou zastávku podle bodu
BusStopModel* MapModel::getBusStopByPoint(PointModel *point, double zoom){

    double tolerance = 5/zoom;

    if(point == NULL) throw new QString("Nebyl vybrán žádný bod");

    for(BusStopModel* model: BusStops){
        if(model->getPosition()->getX() >= point->getX()-tolerance && model->getPosition()->getX() <= point->getX()+tolerance
                && model->getPosition()->getY() >= point->getY()-tolerance && model->getPosition()->getY() <= point->getY()+tolerance)
            return model;
    }

    return nullptr;
}

//-------------------------------------------------------------------------
// Funkce vrací autobus podle bodu
BusModel* MapModel::getBusByPoint(PointModel *point, double zoom){

    double tolerance = 5/zoom;

    if(point == NULL) throw new QString("Nebyl vybrán žádný bod");

    for(BusModel* model: Buses){
        if(model->CurrentPosition().GetDistanceFrom(point) <= tolerance)
            return model;
    }

    return nullptr;
}

//--------------------------------------------------------------------------
//Metoda vytvoří autobusy podle času hodin
void MapModel::loadBuses(ClockModel* clock){

    for(BusModel* bus: Buses) delete bus;
    Buses.clear();

    tm now = clock->getTime();
    for(TimeTableModel* table: TimeTables){

        tm firstToShow = SecondsToTime(TimeToSeconds(now) - table->getBusLine()->getDurationInMinutes()*60);
        if(TimeToSeconds(firstToShow) < 0) firstToShow = SecondsToTime(TimeToSeconds(firstToShow) + 24*60*60);

        for(tm start : table->getStartTimes()){
            if(IsTimeBetween(firstToShow, now, start)){
                try{
                    BusModel* bus = new BusModel(0, start, table->getBusLine(), clock);
                    Buses.push_back(bus);
                }
                catch(const QString *exc){ mainWindow->showException(exc); }
            }
        }
    }

    lastActualizeBuses = now;


}

//--------------------------------------------------------------------------
// Metoda aktualizuje autobusy podle času hodin
void MapModel::actualizeBuses(ClockModel* clock){

    for(BusModel* bus : Buses){
        if(!bus->actualizePosition()) deleteBus(&Buses, bus);
    }

    tm now = clock->getTime();

    for(TimeTableModel* table: TimeTables){
        for(tm start : table->getStartTimes()){
            if(IsTimeBetween(lastActualizeBuses, now, start)){
                try{
                    BusModel* bus = new BusModel(0, start, table->getBusLine(), clock);
                    Buses.push_back(bus);
                }
                catch(const QString *exc){ mainWindow->showException(exc); }
            }
        }
    }
    lastActualizeBuses = now;
}

//------------------------------------------------------------------------------
// Metoda vymaže autobus z pole
void MapModel::deleteBus(vector<BusModel*> *buses, BusModel *bus){
    if(bus == NULL) throw new QString("Nebyl vybrán žádný autobus");

    BusModel* pop = buses->at(buses->size()-1);
    buses->pop_back();

    if(pop != bus && !buses->empty()) deleteBus(buses, bus);
    else if(pop == bus){
        mainWindow->closeBusDetail(bus);
        delete pop;
        return;
    }
    buses->push_back(pop);

}


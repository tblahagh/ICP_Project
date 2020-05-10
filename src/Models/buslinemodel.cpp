#include "buslinemodel.h"

//**************************************************************************************
// konstruktory, destruktory, tisk
//---------------------------------------------------------------------------------------

//------------------------------------------------------------------
// Základní konstruktor
BusLineModel::BusLineModel(unsigned int id, QString name, vector<BusStopModel*> busStops, vector<int> times, PathModel* path) : BaseModel(id)
{
    this->path = path;
    this->times = times;
    this->busStops = busStops;
    this->name = name;

    isCorrect();
}

//----------------------------------------------------------------
// Konstruktor pro vytvoření modelu z XML uzlu
BusLineModel::BusLineModel(TiXmlElement* xml, vector<BusStopModel*> busStops, vector<StreetModel*> streets) : BaseModel(xml)
{
    this->name = xml->Attribute("name");
    TiXmlNode* xmlBusStops = xml->FirstChild("busstops");
    TiXmlNode* xmlPath = xml->FirstChild("path");
    if (xmlBusStops == nullptr || xmlPath == nullptr)
        throw QString("Nepodařilo se načíst autobusovou linku.");
    busStops = GetByXml(xmlBusStops, busStops, "busstopid");

    times = GetIntByXml(xmlBusStops, "time");

    path = new PathModel();
    vector<StreetModel*> pathVector = GetByXml(xmlPath, streets, "streetid");
    for(StreetModel* street : pathVector) path->addStreet(street);

    isCorrect();

}

//---------------------------------------------------------------
// Destruktor
BusLineModel::~BusLineModel(){
    if(path != NULL) delete path;
}

//--------------------------------------------------------------
// Ladící metoda pro výpis obsahu modelu na standartní výstup
void BusLineModel::Print(int indent)
{
    PrintIndent(indent);
    cout << "Bus Line " << id << "\n";
    PrintIndent(indent);
    cout << "Path:\n";
    path->Print(indent + 1);
    PrintIndent(indent);
    cout << "BusStops:\n";
    for (BusStopModel * busStop : busStops)
    {
        busStop->Print(indent + 1);
    }
}


//************************************************************************************
// metody get, set, add
//------------------------------------------------------------------------------------

//-------------------------------------------------------------
// Funkce vrací název linky
QString BusLineModel::getName(){
    return this->name;
}

//--------------------------------------------------------------
// Funkce vrací zastávky linky
vector<BusStopModel*> BusLineModel::getBusStops(){
    return this->busStops;
}

//---------------------------------------------------------------
// Funkce vrací minuty mezi zastávkami
vector<int> BusLineModel::getTimes(){
    return this->times;
}

//----------------------------------------------------------------
// Funkce vrací trasu linky
PathModel* BusLineModel::getPath(){
    return this->path;
}

//************************************************************************************
// výpočetní metody
//----------------------------------------------------------------------------------



//------------------------------------------------------------------
// Funkce vrací index zastávky v autobusové lince
unsigned int BusLineModel::GetIndexByBusStop(BusStopModel* busStop)
{
    if(busStop == NULL) throw new QString("Nebyla vybrána žádná zastávky (buslinemodel, line: " + QString::number(id) + ")");

    unsigned int index = 0;
    for (BusStopModel* _busStop : busStops)
    {
        if (_busStop->getId() == busStop->getId())
            return index;
        index++;
    }
    return index;
}

//-------------------------------------------------------------------
// Funkce vrací jak dlouho trvá jízda linky v minutách
int BusLineModel::getDurationInMinutes(){
    int i = 0;
    for(int time : times){
        i += time;
    }
    return i;
}


//-----------------------------------------------------------------------
// Funkce vrací index ulice v cestě podle zastávky
unsigned int BusLineModel::GetStreetIndexByBusStop(BusStopModel *busStop)
{
    unsigned int index = 0;
    for (index = 0; index < path->getStreets().size(); index++)
    {
        if (path->getStreets()[index]->getId() == busStop->getStreet()->getId())
            return index;
    }
    return index;
}

//-------------------------------------------------------------------------
// Funkce vrací ulice mezi zastávkami
vector<StreetModel*> BusLineModel::GetStreetsBetweenBusStops( BusStopModel *leftBusStop, BusStopModel *rightBusStop, bool skip)
{
    vector<StreetModel*> streets = {};
    unsigned int leftStreetIndex = GetStreetIndexByBusStop(leftBusStop);
    unsigned int rightStreetIndex = GetStreetIndexByBusStop(rightBusStop);
    if (skip == false)
        streets.push_back(leftBusStop->getStreet());
    for (leftStreetIndex += 1; leftStreetIndex < rightStreetIndex; leftStreetIndex++)
    {
        streets.push_back(path->getStreets()[leftStreetIndex]);
    }
    if (skip == false)
        streets.push_back(rightBusStop->getStreet());
    return streets;
}

//-------------------------------------------------------------------------
// Funkce vrací pole bodů, které jsou mezi zastávkami
vector<PointModel*> BusLineModel::GetPointsBetweenBusStops(BusStopModel *leftBusStop, BusStopModel *rightBusStop)
{
    vector<PointModel*> points = {};
    unsigned int leftBusStopIndex = GetIndexByBusStop(leftBusStop);
    unsigned int rightBusStopIndex = GetIndexByBusStop(rightBusStop);
    StreetModel* leftStreet = leftBusStop->getStreet();
    points.push_back(busStops[leftBusStopIndex]->getPosition());
    for (; leftBusStopIndex < rightBusStopIndex; leftBusStopIndex++)
    {
        for (StreetModel* street : GetStreetsBetweenBusStops(busStops[leftBusStopIndex], busStops[leftBusStopIndex + 1], true))
        {
            PointModel* point = leftStreet->IsConnectedBy(street);
            if (point == nullptr)
                throw exception();
            points.push_back(point);
            leftStreet = street;
        }
        points.push_back(leftStreet->IsConnectedBy(busStops[leftBusStopIndex+1]->getStreet()));
        points.push_back(busStops[leftBusStopIndex+1]->getPosition());
        leftStreet = busStops[leftBusStopIndex + 1]->getStreet();
    }

    return points;
}

//---------------------------------------------------------------------------
// Funkce vrací vzdálenost na cestě mezi zastávkami
double BusLineModel::GetDistanceOfBusStops(unsigned int leftIndex, unsigned int rightIndex)
{

    if (leftIndex < busStops.size() && rightIndex < busStops.size() && leftIndex <= rightIndex)
    {
        return GetDistanceOfBusStops(busStops[leftIndex], busStops[rightIndex]);
    }
    return 0;

}

//--------------------------------------------------------------------------
// Funkce vrací vzdálenost na cestě mezi zastávkami
double BusLineModel::GetDistanceOfBusStops(BusStopModel *leftBusStop, BusStopModel *rightBusStop)
{
    double distance = 0;
    vector<PointModel*> points = GetPointsBetweenBusStops(leftBusStop, rightBusStop);
    for (unsigned int i = 0; i < points.size() - 1; i++)
    {
        distance += points[i]->GetDistanceFrom(points[i+1]);
    }
    return distance;
}



//****************************************************************************************
// kontrolní metody
//--------------------------------------------------------------------------------------

//----------------------------------------------------------------------
// Funkce vyhodí výjimku, pokud je linka špatně inicializována
void BusLineModel::isCorrect(){

    if(this->name == NULL) name = "";

    if(busStops.size() != times.size()) throw new QString("Každá zastávka musí mít čas dojezdu (buslinemodel, line: " + QString::number(id) + ")");

    int unsigned index = 0;
    for(BusStopModel* busStop: busStops){

        while(index<path->getStreets().size()){
            if(busStop->getStreet() == path->getStreets()[index]) break;
            index++;
        }
        if(index == path->getStreets().size()) throw new QString("Některé zastávky neleží na trase linky. (buslinemodel, line: " + QString::number(id) + ")");
    }


}

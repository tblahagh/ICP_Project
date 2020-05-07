#include "buslinemodel.h"

//**************************************************************************************
// konstruktory, destruktory, tisk
//---------------------------------------------------------------------------------------

//------------------------------------------------------------------
// vytvoří linku z parametrů
BusLineModel::BusLineModel(unsigned int id, QString name, vector<BusStopModel*> busStops, vector<int> times, PathModel* path) : BaseModel(id)
{
    this->Path = path;
    this->Times = times;
    this->BusStops = busStops;
    this->Name = name;

    isCorrect();
}

//----------------------------------------------------------------
// vytvoří linku ze souboru xml
BusLineModel::BusLineModel(TiXmlElement* xml, vector<BusStopModel*> busStops, vector<StreetModel*> streets) : BaseModel(xml)
{
    this->Name = xml->Attribute("name");
    TiXmlNode* xmlBusStops = xml->FirstChild("busstops");
    TiXmlNode* xmlPath = xml->FirstChild("path");
    if (xmlBusStops == nullptr || xmlPath == nullptr)
        throw QString("Nepodařilo se načíst autobusovou linku.");
    BusStops = GetByXml(xmlBusStops, busStops, "busstopid");

    Times = GetIntByXml(xmlBusStops, "time");

    Path = new PathModel();
    vector<StreetModel*> pathVector = GetByXml(xmlPath, streets, "streetid");
    for(StreetModel* street : pathVector) Path->addStreet(street);

    isCorrect();

}

//---------------------------------------------------------------
// destruktor
BusLineModel::~BusLineModel(){
    if(Path != NULL) delete Path;
}

//--------------------------------------------------------------
// tisk
void BusLineModel::Print(int indent)
{
    PrintIndent(indent);
    cout << "Bus Line " << id << "\n";
    PrintIndent(indent);
    cout << "Path:\n";
    Path->Print(indent + 1);
    PrintIndent(indent);
    cout << "BusStops:\n";
    for (BusStopModel * busStop : BusStops)
    {
        busStop->Print(indent + 1);
    }
}


//************************************************************************************
// metody get, set, add
//------------------------------------------------------------------------------------

//-------------------------------------------------------------
// vrátí jméno linky
QString BusLineModel::getName(){
    return this->Name;
}

//--------------------------------------------------------------
// vrátí seznam zastávek
vector<BusStopModel*> BusLineModel::getBusStops(){
    return this->BusStops;
}

//---------------------------------------------------------------
// vrátí seznam časů
vector<int> BusLineModel::getTimes(){
    return this->Times;
}

//----------------------------------------------------------------
// vrátí trasu
PathModel* BusLineModel::getPath(){
    return this->Path;
}

//************************************************************************************
// výpočetní metody
//----------------------------------------------------------------------------------

//--------------------------------------------------------------
// vrátí autobusovou zastávku podle id
BusStopModel* BusLineModel::GetBusStopById(int id)
{
    for (BusStopModel* busStop : BusStops)
    {
        if (busStop->getId() == id)
            return busStop;
    }
    return nullptr;
}

//------------------------------------------------------------------
// vrátí index autobusové zastávky
unsigned int BusLineModel::GetIndexByBusStop(BusStopModel* busStop)
{
    if(busStop == NULL) throw new QString("Nebyla vybrána žádná zastávky (buslinemodel, line: " + QString::number(id) + ")");

    unsigned int index = 0;
    for (BusStopModel* _busStop : BusStops)
    {
        if (_busStop->getId() == busStop->getId())
            return index;
        index++;
    }
    return index;
}

//-------------------------------------------------------------------
// vrátí délku v minutách, jak dlouho trvá trasa
int BusLineModel::getDurationInMinutes(){
    int i = 0;
    for(int time : Times){
        i += time;
    }
    return i;
}


//-----------------------------------------------------------------------
// vrátí index ulice podle zastávky
unsigned int BusLineModel::GetStreetIndexByBusStop(BusStopModel *busStop)
{
    unsigned int index = 0;
    for (index = 0; index < Path->getStreets().size(); index++)
    {
        if (Path->getStreets()[index]->getId() == busStop->getStreet()->getId())
            return index;
    }
    return index;
}

//-------------------------------------------------------------------------
// vrátí seznam ulic mezi zastávkami
vector<StreetModel*> BusLineModel::GetStreetsBetweenBusStops( BusStopModel *leftBusStop, BusStopModel *rightBusStop, bool skip)
{
    vector<StreetModel*> streets = {};
    unsigned int leftStreetIndex = GetStreetIndexByBusStop(leftBusStop);
    unsigned int rightStreetIndex = GetStreetIndexByBusStop(rightBusStop);
    if (skip == false)
        streets.push_back(leftBusStop->getStreet());
    for (leftStreetIndex += 1; leftStreetIndex < rightStreetIndex; leftStreetIndex++)
    {
        streets.push_back(Path->getStreets()[leftStreetIndex]);
    }
    if (skip == false)
        streets.push_back(rightBusStop->getStreet());
    return streets;
}

//-------------------------------------------------------------------------
// vrátí seznam bodů mezi zastávkami
vector<PointModel*> BusLineModel::GetPointsBetweenBusStops(BusStopModel *leftBusStop, BusStopModel *rightBusStop)
{
    vector<PointModel*> points = {};
    unsigned int leftBusStopIndex = GetIndexByBusStop(leftBusStop);
    unsigned int rightBusStopIndex = GetIndexByBusStop(rightBusStop);
    StreetModel* leftStreet = leftBusStop->getStreet();
    points.push_back(BusStops[leftBusStopIndex]->getPosition());
    for (; leftBusStopIndex < rightBusStopIndex; leftBusStopIndex++)
    {
        for (StreetModel* street : GetStreetsBetweenBusStops(BusStops[leftBusStopIndex], BusStops[leftBusStopIndex + 1], true))
        {
            PointModel* point = leftStreet->IsConnectedBy(street);
            if (point == nullptr)
                throw exception();
            points.push_back(point);
            leftStreet = street;
        }
        points.push_back(leftStreet->IsConnectedBy(BusStops[leftBusStopIndex+1]->getStreet()));
        points.push_back(BusStops[leftBusStopIndex+1]->getPosition());
        leftStreet = BusStops[leftBusStopIndex + 1]->getStreet();
    }

    return points;
}

//---------------------------------------------------------------------------
// vrátí vzdálenost mezi zastávkami
double BusLineModel::GetDistanceOfBusStops(unsigned int leftIndex, unsigned int rightIndex)
{

    if (leftIndex < BusStops.size() && rightIndex < BusStops.size() && leftIndex <= rightIndex)
    {
        return GetDistanceOfBusStops(BusStops[leftIndex], BusStops[rightIndex]);
    }
    return 0;

}

//--------------------------------------------------------------------------
// vrátí vzdálenost mezi zastávkami
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
// kontrola, zda je linka korektní
void BusLineModel::isCorrect(){

    if(this->Name == NULL) Name = "";

    if(BusStops.size() != Times.size()) throw new QString("Každá zastávka musí mít čas dojezdu (buslinemodel, line: " + QString::number(id) + ")");

    int unsigned index = 0;
    for(BusStopModel* busStop: BusStops){

        while(index<Path->getStreets().size()){
            if(busStop->getStreet() == Path->getStreets()[index]) break;
            index++;
        }
        if(index == Path->getStreets().size()) throw new QString("Některé zastávky neleží na trase linky. (buslinemodel, line: " + QString::number(id) + ")");
    }


}

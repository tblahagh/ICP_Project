#include "busstopmodel.h"

//********************************************************************************************
// konstruktory, destruktory, tisk
//-------------------------------------------------------------------------------------------

//-----------------------------------------------------------------
// vytvoří zastávku podle parametrů
BusStopModel::BusStopModel(unsigned int id, QString name, double position, StreetModel* street) : BaseModel(id)
{
    this->street = street;
    this->name = name;
    this->positionOnStreet = position;

    isCorrect();
    CalculatePosition(positionOnStreet);
}

//----------------------------------------------------------------
// vytvoří zastávku podle souboru xml
BusStopModel::BusStopModel(TiXmlElement* xml, vector<StreetModel*> streets) : BaseModel(xml)
{
    unsigned int streetId = 0;

    this->name = xml->Attribute("name");
    if (xml->QueryDoubleAttribute("position", &positionOnStreet))
        throw new QString("Nepodařilo se načíst pozici zastávky.");
    if (xml->QueryUnsignedAttribute("street", &streetId) != TIXML_SUCCESS)
        throw new QString("Nepodařilo se načíst ulici.");
    if ((street = GetModelById(streets, streetId)) == nullptr)
        throw new QString("Nepodařilo se najít ulici.");

    isCorrect();
    CalculatePosition(positionOnStreet);
}

//-----------------------------------------------------------------
// destruktor
BusStopModel::~BusStopModel()
{
    delete position;
}

//----------------------------------------------------------------
// tisk
void BusStopModel::Print(int indent)
{
    PrintIndent(indent);
    cout << "Bus Stop " << id << "\n";
    PrintIndent(indent);
    cout << "Position: " << position << endl;
    position->Print(indent + 1);
    PrintIndent(indent);
    cout << "Street:\n";
    street->Print(indent + 1);
}

//********************************************************************************
// metody get, set, add
//-----------------------------------------------------------------------------------

//--------------------------------------------------------------------
// vrátí název zastávky
QString BusStopModel::getName(){
    return this->name;
}

//--------------------------------------------------------------------
// vrátí ulici, na které se zastávka nachází
StreetModel* BusStopModel::getStreet(){
    return this->street;
}

//-------------------------------------------------------------------
// vrátí pozici, na které se zastávka nachází
PointModel* BusStopModel::getPosition(){
    return this->position;
}

//-------------------------------------------------------------------
// vrátí pozici, na které se zastávka nachází
double BusStopModel::getPositionOnStreet(){
    return this->positionOnStreet;
}

//**********************************************************************************
// výpočetní metody
//----------------------------------------------------------------------------------

//-------------------------------------------------------------------
// vypočítá pozici na mapě
void BusStopModel::CalculatePosition(double position){
    if(position < 0 || position > 1) throw new QString("Zastávka musí ležet na ulici");

    double x = street->getStartPosition()->getX() +  ((street->getEndPosition()->getX() - street->getStartPosition()->getX()) * position);
    double y = street->getStartPosition()->getY() + ((street->getEndPosition()->getY() - street->getStartPosition()->getY()) * position);
    this->position = new PointModel(0, x, y);
}

//--------------------------------------------------------------------
// vypočítá vzdálenost od počátku ulice
double BusStopModel::DistanceFromStart(){
    return this->position->GetDistanceFrom(street->getStartPosition());
}

//--------------------------------------------------------------------
// vrátí vzdálenost od konce ulice
double BusStopModel::DistanceFromEnd(){
    return this->position->GetDistanceFrom(street->getEndPosition());
}

//*************************************************************************************
// kontrolní metody
//----------------------------------------------------------------------------------------

//--------------------------------------------------------------------
// zkontroluje, jsou vstupní hodnoty korektní
void BusStopModel::isCorrect(){

    if(this->name == NULL) this->name = "";

    if(this->positionOnStreet < 0 || this->positionOnStreet > 1) throw new QString("Zastávka musí ležet na ulici");

    if(this->street == NULL) throw new QString("Zastávka musí ležet na ulici");

}

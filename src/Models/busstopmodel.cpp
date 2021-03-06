#include "busstopmodel.h"

//********************************************************************************************
// konstruktory, destruktory, tisk
//-------------------------------------------------------------------------------------------

//-----------------------------------------------------------------
// Základní konstruktor
BusStopModel::BusStopModel(unsigned int id, QString name, double position, StreetModel* street) : BaseModel(id)
{
    this->street = street;
    this->name = name;
    this->positionOnStreet = position;

    isCorrect();
    CalculatePosition(positionOnStreet);
}

//----------------------------------------------------------------
// Konstruktor pro vytvoření modelu z XML uzlu
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
// Destruktor
BusStopModel::~BusStopModel()
{
    delete position;
}

//----------------------------------------------------------------
// Ladící metoda pro výpis obsahu modelu na standartní výstup
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
// Funkce vrací název zastávky
QString BusStopModel::getName(){
    return this->name;
}

//--------------------------------------------------------------------
// Funkce vrací ulici kde se zastávka nachází
StreetModel* BusStopModel::getStreet(){
    return this->street;
}

//-------------------------------------------------------------------
// Funkce vrací bod, kde se zastávka nachází
PointModel* BusStopModel::getPosition(){
    return this->position;
}

//-------------------------------------------------------------------
// Funkce vrací hodnotu, jak daleko se zastávka nachází od počátečního bodu
double BusStopModel::getPositionOnStreet(){
    return this->positionOnStreet;
}

//**********************************************************************************
// výpočetní metody
//----------------------------------------------------------------------------------

//-------------------------------------------------------------------
// Funkce vrací hodnotu, jak daleko se zastávka nachází od počátečního bodu
void BusStopModel::CalculatePosition(double position){
    if(position < 0 || position > 1) throw new QString("Zastávka musí ležet na ulici");

    double x = street->getStartPosition()->getX() +  ((street->getEndPosition()->getX() - street->getStartPosition()->getX()) * position);
    double y = street->getStartPosition()->getY() + ((street->getEndPosition()->getY() - street->getStartPosition()->getY()) * position);
    this->position = new PointModel(0, x, y);
}

//--------------------------------------------------------------------
// Funkce vrací vzdálenost mezi zástávkou a počátečním bodem ulice
double BusStopModel::DistanceFromStart(){
    return this->position->GetDistanceFrom(street->getStartPosition());
}

//--------------------------------------------------------------------
// Funkce vrací vzdálenost mezi zástávkou a koncovým bodem ulice
double BusStopModel::DistanceFromEnd(){
    return this->position->GetDistanceFrom(street->getEndPosition());
}

//*************************************************************************************
// kontrolní metody
//----------------------------------------------------------------------------------------

//--------------------------------------------------------------------
// Metoda vyhodí výjimku, pokud je zastávka špatně inicializována
void BusStopModel::isCorrect(){

    if(this->name == NULL) this->name = "";

    if(this->positionOnStreet < 0 || this->positionOnStreet > 1) throw new QString("Zastávka musí ležet na ulici");

    if(this->street == NULL) throw new QString("Zastávka musí ležet na ulici");

}

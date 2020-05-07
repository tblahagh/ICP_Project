#include "streetmodel.h"

//************************************************************************
// konstruktory, destruktory, tisk
//------------------------------------------------------------------------

//-----------------------------------------------------------------------
// vytvoření ulice podle zadaných parametrů
StreetModel::StreetModel(unsigned int id, QString name, PointModel* start, PointModel* end) : BaseModel(id)
{
    this->Name = name;
    this->StartPosition = start;
    this->EndPosition = end;

    isCorrect();
}

//-------------------------------------------------------------------------
// vytvoření ulice ze souboru xml
StreetModel::StreetModel(TiXmlElement* xml, vector<PointModel*> points) : BaseModel(xml)
{
    this->Name = xml->Attribute("name");
    unsigned int startId = 0, endId = 0;
    if (xml->QueryUnsignedAttribute("start", &startId) != TIXML_SUCCESS)
        throw new QString("Nepodařilo se načíst startovní bod ulice");
    if (xml->QueryUnsignedAttribute("end", &endId) != TIXML_SUCCESS)
        throw new QString("Nepodařilo se načíst koncový bod ulice");
    if ((StartPosition = BaseModel::GetModelById<PointModel>(points, startId)) == nullptr)
        throw new QString("Nepodařilo se najít startovní bod ulice");
    if ((EndPosition = GetModelById(points, endId)) == nullptr)
        throw new QString("Nepodařilo se najít koncový bod ulice");

    isCorrect();
}

StreetModel::~StreetModel(){
    if(detour != NULL) delete detour;
}

//-------------------------------------------------------------------------------
// tisk ulice
void StreetModel::Print(int indent)
{
    PrintIndent(indent);
    std::cout<<"Street " << this->id << " " << this->Name.toStdString() << std::endl;
    PrintIndent(indent);
    std::cout << "Start:\n";
    this->StartPosition->Print(indent + 1);
    PrintIndent(indent);
    std::cout << "End:\n";
    this->EndPosition->Print(indent + 1);
}

//*****************************************************************************
// metody get, set, add
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// vrací počáteční bod
PointModel* StreetModel::getStartPosition(){
    return this->StartPosition;
}

//-------------------------------------------------------------------------------
// vrací koncový bod
PointModel* StreetModel::getEndPosition(){
    return this->EndPosition;
}

//----------------------------------------------------------------------------
// vrací jméno ulice
QString StreetModel::getName(){
    return this->Name;
}

//-------------------------------------------------------------------------
// vrátí hustotu provozu
int StreetModel::GetTraffic(){
    return this->traffic;
}

//---------------------------------------------------------------------------
// nastaví hustotu provozu
void StreetModel::SetTraffic(int _traffic){
    if(_traffic < 0 || _traffic > 3) throw new QString("Špatná hodnota hustoty provozu");
    if(_traffic != 0 && traffic == 0){
        if(detour != NULL) delete detour;
        detour = NULL;
        delay = 0;
    }

    this->traffic = _traffic;
}

//-----------------------------------------------------------------------------
// vrátí zpoždění
int StreetModel::GetDelay(){
    return this->delay;
}

//-----------------------------------------------------------------------------
// nastaví zpoždění
void StreetModel::SetDelay(int _delay){
    if(_delay < 0) throw new QString("Zpoždění nemůže být záporné");

    this->delay = _delay;
}

//-----------------------------------------------------------------------------
// vrátí trasu objížďky
PathModel* StreetModel::GetDetour(){
    return this->detour;
}

//------------------------------------------------------------------------------
// nastaví trasu objížďky
void StreetModel::SetDetour(PathModel *_detour){

    // pokud byla zadána prázdná objížďka
    if(_detour != NULL && _detour->getStreets().empty()) _detour = NULL;

    if(_detour != NULL){

        // pokud trasa nezačíná nebo nekončí na krajních bodech ulice
        if(!ContainsEndPoint(_detour->getStartPosition())
                || !ContainsEndPoint(_detour->getEndPosition())
                || _detour->getStartPosition() == _detour->getEndPosition()){
            throw new QString("Trasa netvoří objížďku této ulice. Musí začínat a končit na koncích vybrané ulice.");
        }

        for(StreetModel* model : _detour->getStreets()){
            // pokud trasa obsahuje tuto ulici
            if(model == this)
                throw new QString("Vybraná ulice nemůže být součástí objížďky.");

            // pokud trasa obsahuje uzavřenou ulici
            if(model->GetTraffic() == 0)
                throw new QString("Uzavřená ulice nemůže být součástí objížďky");
        }

    }


    // pokud ulice již obsahuje, nějakou objížďku, smažeme ji
    if(this->detour != NULL && this->detour != _detour)
        delete this->detour;

    // nastavíme objížďku
    this->detour = _detour;
}

//****************************************************************************
// výpočetní metody
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
// vrací bod, kterým je ulice propojena s jinou ulicí
PointModel* StreetModel::IsConnectedBy(StreetModel *street)
{
    if (street == nullptr) throw new QString("Nebyla vybrána žádná ulice.");
    else if (street == this) throw new QString("Byla vybrána stejná ulice.");

    if (StartPosition->getId() == street->StartPosition->getId() || StartPosition->getId() == street->EndPosition->getId())
        return StartPosition;
    else if (EndPosition->getId() == street->StartPosition->getId() || EndPosition->getId() == street->EndPosition->getId())
        return EndPosition;
    else
        return nullptr;
}

//-----------------------------------------------------------------------------
// vrátí opačný bod
PointModel* StreetModel::GetOppositePoint(PointModel *point)
{
    if(point == NULL) throw new QString("Nebyl vybrán žádný bod");

    if (point->getId() == StartPosition->getId())
        return EndPosition;
    else if (point->getId() == EndPosition->getId())
        return StartPosition;
    return nullptr;
}

//-----------------------------------------------------------------------------
// vrátí délku ulice
double StreetModel::GetLength()
{
    return StartPosition->GetDistanceFrom(EndPosition);
}

//*****************************************************************************
// kontrolní metody
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// kontrola, zda je vytvořená ulice korektní
void StreetModel::isCorrect(){
    if(this->StartPosition == NULL || this->EndPosition == NULL) throw new QString("Ulice musí obsahovat dva koncové body");
    if(this->StartPosition == this->EndPosition) throw new QString("Ulice musí obsahovat dva různé koncové body");
    if(this->StartPosition->getX() == this->EndPosition->getX()
            && this->StartPosition->getY() == this->EndPosition->getY()) throw new QString("Koncové body ulice musí mít odlišné souřadnice");

    if(this->Name == NULL) this->Name = "";
}

//-----------------------------------------------------------------------------
// vrátí true, pokud jeden z koncových bodů je zadaný bod
bool StreetModel::ContainsEndPoint(PointModel *point){

    if(point == NULL) throw new QString("Nebyl vybrán žádný bod.");

    if(point == StartPosition) return true;
    if(point == EndPosition) return true;
    return false;
}

//-----------------------------------------------------------------------------
// vrátí true, pokud bod lezi na ulici
bool StreetModel::ContainsPoint(PointModel *point, double tolerance){

    if(point == NULL) throw new QString("Nebyl vybrán žádný bod.");

    // jedna se o start position?
    if(point->getX() == StartPosition->getX() && point->getY() == StartPosition->getY()) return true;

    // jedna se o end position?
    if(point->getX() == EndPosition->getX() && point->getY() == EndPosition->getY()) return true;

    // je souradnice X v oblasti?
    if(StartPosition->getX() < EndPosition->getX()){
        if(StartPosition->getX() > point->getX()) return false;
        if(EndPosition->getX() < point->getX()) return false;
    }
    else if(StartPosition->getX() > EndPosition->getX()){
        if(StartPosition->getX() < point->getX()) return false;
        if(EndPosition->getX() > point->getX()) return false;
    }

    // je souradnice Y v oblasti?
    if(StartPosition->getY() < EndPosition->getY()){
        if(StartPosition->getY() > point->getY()) return false;
        if(EndPosition->getY() < point->getY()) return false;
    }
    else if(StartPosition->getY() > EndPosition->getY()){
        if(StartPosition->getY() < point->getY()) return false;
        if(EndPosition->getY() > point->getY()) return false;
    }

    // pokud je primka vodorovne nebo svisle, lezi na primce, protoze oblast je pouze primka
    if(StartPosition->getX() == EndPosition->getX() && (StartPosition->getX()-tolerance) <= point->getX() && point->getX() <= (StartPosition->getX()+tolerance)) return true;
    if(StartPosition->getY() == EndPosition->getY() && (StartPosition->getY()-tolerance) <= point->getY() && point->getY() <= (StartPosition->getY()+tolerance)) return true;

    // výpočet úhlu a odchylky na ose x
    double x = EndPosition->getX() - StartPosition->getX();
    double y = EndPosition->getY() - StartPosition->getY();

    double alfa = atan(y/x);

    double deviation = tolerance / sin(alfa);

    // bod na ose v urovni x kontrolovaneho bodu
    double a = EndPosition->getX() - ((EndPosition->getY() - point->getY())/tan(alfa));

    if(deviation > 0 && (a-deviation) <= point->getX() && point->getX() <= (a+deviation)) return true;
    else if(deviation <= 0 && (a+deviation) <= point->getX() && point->getX() <= (a-deviation)) return true;
    else return false;

}

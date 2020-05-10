#include "pathmodel.h"

//******************************************************************************
// konstruktory, destruktory, tisk
//-----------------------------------------------------------------------------

//-------------------------------------------------------------------------
// Základní konstruktor
PathModel::PathModel(unsigned int id) : BaseModel(id)
{

}

//---------------------------------------------------------------------------
// Ladící metoda pro výpis obsahu modelu na standartní výstup
void PathModel::Print(int indent)
{
    PrintIndent(indent);
    std::cout<<"Path " << this->id << std::endl;
    PrintIndent(indent);
    std::cout << "Start:\n";
    if(this->startPosition != NULL)
        this->startPosition->Print(indent + 1);
    PrintIndent(indent);
    std::cout << "End:\n";
    if(this->endPosition != NULL)
        this->endPosition->Print(indent + 1);
    std::cout << "Streets:\n";
    for(StreetModel* street: this->streets){
        street->Print(indent + 1);
    }
}

//*****************************************************************************
// metody get, set, add
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Funkce vrací seznam ulic, které tvoří trasu
vector<StreetModel*> PathModel::getStreets(){
    return this->streets;
}

//-----------------------------------------------------------------------------
// Funkce vrací počáteční bod trasy
PointModel* PathModel::getStartPosition(){
    return this->startPosition;
}

//--------------------------------------------------------------------
// Funkce vrací koncový bod trasy
PointModel* PathModel::getEndPosition(){
    return this->endPosition;
}

//-----------------------------------------------------------------
// Metoda přidá ulici na konec trasy
void PathModel::addStreet(StreetModel* street){
    if(street == NULL) throw new QString("Nebyla vybrána žádná ulice");

    if(std::count(this->streets.begin(), this->streets.end(), street))
        throw new QString("Cesta už tuto ulici obsahuje (pathmodel, street: " + QString::number(street->getId()) + ")");

    this->streets.push_back(street);

    try{
        isCorrect();
    }
    catch(const QString *exc){
        this->streets.pop_back();
        throw exc;
    }
}

//-------------------------------------------------------------------
// Funkce vrací počet ulic, které tvoří trasu
unsigned int PathModel::getNumberOfStreets(){
    return this->streets.size();
}

//-------------------------------------------------------------------
// Metoda vymaže ulici na konci trasy
void PathModel::clearStreet(){
    this->streets.pop_back();
}

//---------------------------------------------------------------------
// Metoda vymaže všechny ulice v trase
void PathModel::clearStreets(){
    this->streets.clear();
    this->startPosition = NULL;
    this->endPosition = NULL;
}

//**************************************************************************************
// výpočetní metody
//---------------------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Funkce vrací délku trasy
double PathModel::getLenght(){
    double lenght = 0;

    for(StreetModel* street: streets){
        lenght += street->GetLength();
    }
    return lenght;
}

//*************************************************************************************
// kontrolní metody
//-------------------------------------------------------------------------------------

//-----------------------------------------------------------------
// Metoda vyhodí výjimku, pokud je trasa špatně inicializována
void PathModel::isCorrect(){

    if(this->streets.empty()) return;

    if(this->streets.size() == 1){
        startPosition = this->streets[0]->getStartPosition();
        endPosition = this->streets[0]->getEndPosition();
        return;
    }

    StreetModel* lastStreet = NULL;
    PointModel* point = NULL;

    for(StreetModel* street: this->streets){
        if(lastStreet != NULL){
            PointModel* common = lastStreet->IsConnectedBy(street);
            if(common == nullptr) throw new QString("Cesta není propojená. (pathmodel, street: " + QString::number(lastStreet->getId()) + ", street: " + QString::number(street->getId()) + ")");

            if(point == NULL){
                point = street->GetOppositePoint(common);
                startPosition = lastStreet->GetOppositePoint(common);
            }
            else if(point != common) throw new QString("Cesta obsahuje větvení. (pathmodel, point: " + QString::number(common->getId()) + ")");
            else{
                point = street->GetOppositePoint(common);
            }
        }
        lastStreet = street;
    }
    endPosition = point;
}

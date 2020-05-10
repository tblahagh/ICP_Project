#include "pointmodel.h"

//*************************************************************************
// konstruktory, destruktory, tisk
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Základní konstruktor pro vytvoření bodu
PointModel::PointModel(unsigned int id, double x, double y) : BaseModel(id)
{
    this->X = x;
    this->Y = y;
}

//----------------------------------------------------------------------------
// Konstruktor pro vytvoření modelu bodu z XML uzlu
PointModel::PointModel(TiXmlElement* xml) : BaseModel(xml)
{
    if (xml->QueryDoubleAttribute("x", &X) != TIXML_SUCCESS)
        throw new QString("Nepodařilo se načíst souřadnici x.");
    if (xml->QueryDoubleAttribute("y", &Y) != TIXML_SUCCESS)
        throw new QString("Nepodařilo se načíst souřadnici y.");
}

//----------------------------------------------------------------------------
// Ladící metoda pro výpis obsahu modelu na standartní výstup
void PointModel::Print(int indent)
{
    PrintIndent(indent);
    std::cout << this->id << " [ " << X << " , " << Y << " ]\n";
}

//**************************************************************************
// metody get, set, add
//----------------------------------------------------------------------------

//--------------------------------------------------------------------
// Vrací souřadnici X
double PointModel::getX(){
    return X;
}

//---------------------------------------------------------------------
// Vrací souřadnici Y
double PointModel::getY(){
    return Y;
}

//*******************************************************************************
// výpočetní metody
//------------------------------------------------------------------------

//----------------------------------------------------------------------
// Funkce vypočte vzdálenost bodu od jiného
double PointModel::GetDistanceFrom(PointModel *point)
{
    if(point == NULL) throw new QString("Nebyl vybrán žádný bod");

    double a = X - point->X;
    double b = Y - point->Y;
    return sqrt((a*a) + (b*b));
}



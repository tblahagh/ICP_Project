#include "pointmodel.h"

//*************************************************************************
// konstruktory, destruktory, tisk
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// vytvoří bod podle parametrů
PointModel::PointModel(unsigned int id, double x, double y) : BaseModel(id)
{
    this->X = x;
    this->Y = y;
}

//----------------------------------------------------------------------------
// vytvoří bod ze souboru xml
PointModel::PointModel(TiXmlElement* xml) : BaseModel(xml)
{
    if (xml->QueryDoubleAttribute("x", &X) != TIXML_SUCCESS)
        throw new QString("Nepodařilo se načíst souřadnici x.");
    if (xml->QueryDoubleAttribute("y", &Y) != TIXML_SUCCESS)
        throw new QString("Nepodařilo se načíst souřadnici y.");
}

//----------------------------------------------------------------------------
// tisk bodu
void PointModel::Print(int indent)
{
    PrintIndent(indent);
    std::cout << this->id << " [ " << X << " , " << Y << " ]\n";
}

//**************************************************************************
// metody get, set, add
//----------------------------------------------------------------------------

//--------------------------------------------------------------------
// vrátí souřadnici x
double PointModel::getX(){
    return X;
}

//---------------------------------------------------------------------
// vrátí souřadnici y
double PointModel::getY(){
    return Y;
}

//*******************************************************************************
// výpočetní metody
//------------------------------------------------------------------------

//----------------------------------------------------------------------
// vrátí vzdálenost od jiného bodu
double PointModel::GetDistanceFrom(PointModel *point)
{
    if(point == NULL) throw new QString("Nebyl vybrán žádný bod");

    double a = X - point->X;
    double b = Y - point->Y;
    return sqrt((a*a) + (b*b));
}



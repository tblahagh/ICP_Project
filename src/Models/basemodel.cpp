#include "basemodel.h"

//*******************************************************************************
// konstruktory, destruktory a tisk
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
// vytvoření základního modelu podle parametrů
BaseModel::BaseModel(unsigned int id)
{
    this->id = id;
}

//-------------------------------------------------------------------------------
// vytvoření základního modelu podle souboru xml
BaseModel::BaseModel(TiXmlElement* xml)
{
    if (xml->QueryUnsignedAttribute("id", &id) != TIXML_SUCCESS)
        throw new QString("Nepodařilo se načíst soubor XML.");
}

//-----------------------------------------------------------------------------
// destruktor
BaseModel::~BaseModel(){}

//-----------------------------------------------------------------------------
// tisk modelu
void BaseModel::PrintIndent(int indent)
{
    while (indent-- > 0)
        cout <<"\t";
}

//********************************************************************************
// metody get, set, add
//--------------------------------------------------------------------------------

//---------------------------------------------------------------------------------
// vrátí id modelu
int BaseModel::getId(){
    return this->id;
}


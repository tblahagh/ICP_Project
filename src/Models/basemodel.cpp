/*
 * Autor: Tomáš Blaha
 * Datum: 9.5.2020
 * */
#include "basemodel.h"

//*******************************************************************************
// konstruktory, destruktory a tisk
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
// Základní konstruktor
BaseModel::BaseModel(unsigned int id)
{
    this->id = id;
}

//-------------------------------------------------------------------------------
// Konstruktor pro vytvoření modelu z XML uzlu
BaseModel::BaseModel(TiXmlElement* xml)
{
    if (xml->QueryUnsignedAttribute("id", &id) != TIXML_SUCCESS)
        throw new QString("Nepodařilo se načíst soubor XML.");
}

//-----------------------------------------------------------------------------
// Destruktor
BaseModel::~BaseModel(){}

//-----------------------------------------------------------------------------
// Ladící metoda výpis pro odsazení na standartní výstup
void BaseModel::PrintIndent(int indent)
{
    while (indent-- > 0)
        cout <<"\t";
}

//********************************************************************************
// metody get, set, add
//--------------------------------------------------------------------------------

//---------------------------------------------------------------------------------
// Funkce vrátí identifikátor modelu
int BaseModel::getId(){
    return this->id;
}


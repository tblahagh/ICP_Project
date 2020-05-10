/*
 * Autoři: Tomáš Blaha, Vojtěch Wawreczka
 * Datum: 9.5.2020
 * */
#include "timetablemodel.h"
#include <iostream>
#include "src/TimeLib.h"

//**********************************************************************************************
// konstruktory, destruktory, tisk
//-----------------------------------------------------------------------------------------------

//--------------------------------------------------------------------
// Základní kostruktor
TimeTableModel::TimeTableModel(unsigned int id, BusLineModel* busLine, vector<tm> startTimes) : BaseModel(id)
{
    this->id = id;
    this->BusLine = busLine;
    this->StartTimes = startTimes;
    isCorrect();
}

//--------------------------------------------------------------------
// Konstruktor pro vytvoření řádu z XML uzlu
TimeTableModel::TimeTableModel(TiXmlElement* xml, vector<BusLineModel*> busLines) : BaseModel(xml)
{

    unsigned int busLineId = 0;
    if (xml->QueryUnsignedAttribute("busline", &busLineId) != TIXML_SUCCESS)
        throw new QString("Nepodařilo se načíst autobusovou linku.");

    if ((BusLine = GetModelById(busLines, busLineId)) == nullptr)
        throw new QString("Nepodařilo se najít autobusovou linku.");

    TiXmlNode* xmlTime = nullptr;
    tm time;
    this->StartTimes = {};
    while ((xmlTime = xml->IterateChildren(xmlTime)) != nullptr)
    {

        TiXmlElement* xmlTimeElement = xmlTime->ToElement();
        if (xmlTimeElement->QueryIntAttribute("hours", &time.tm_hour) != TIXML_SUCCESS)
            throw new QString("Nepodařilo se načíst hodinu.");

        if (xmlTimeElement->QueryIntAttribute("minutes", &time.tm_min) != TIXML_SUCCESS)
            throw new QString("Nepodařilo se načíst minutu.");

        if (xmlTimeElement->QueryIntAttribute("seconds", &time.tm_sec) != TIXML_SUCCESS)
            throw new QString("Nepodařilo se načíst sekundu.");
        this->StartTimes.push_back(time);

    }

    isCorrect();

}

//----------------------------------------------------------------------------
// Destruktor
TimeTableModel::~TimeTableModel()
{

}

//---------------------------------------------------------------------------
// Ladící metoda pro výpis obsahu modelu na standartní výstup
void TimeTableModel::Print(int indent)
{
    PrintIndent(indent);
    cout << "Time Table " << id << " " << "\n";
    BusLine->Print(indent + 1);
    PrintIndent(indent);
    cout << "Start Times:\n";
    for (tm time : StartTimes)
    {
        PrintIndent(indent + 1);
        cout  << time.tm_hour << ":" << time.tm_min << ":" << time.tm_sec << "\n";
    }


}


//******************************************************************************************
// metody get, set, add
//------------------------------------------------------------------------------------------

//----------------------------------------------------------------------
// Funkce vrací autobusovou linku
BusLineModel* TimeTableModel::getBusLine(){
    return this->BusLine;
}

//------------------------------------------------------------------------
// Funkce vrací časy zastávek
vector<tm> TimeTableModel::getStartTimes(){
    return this->StartTimes;
}

//************************************************************************************************
// kontrolní metody
//-------------------------------------------------------------------------------------------

//------------------------------------------------------------------------
// Funkce vyhodí výjimku, pokud je linka špatně inicializována
void TimeTableModel::isCorrect(){
    for(tm time : StartTimes){
        IsCorrectTime(time);
    }
}

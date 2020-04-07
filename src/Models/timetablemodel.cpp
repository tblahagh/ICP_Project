#include "timetablemodel.h"
#include <iostream>
#include "src/TimeLib.h"

TimeTableModel::TimeTableModel(unsigned int id, BusLineModel* busLine, vector<vector<TimeSetModel*>> timeSets) : BaseModel(id)
{
    this->id = id;
    this->BusLine = busLine;

    this->TimeSets = timeSets;
}
TimeTableModel::TimeTableModel(TiXmlElement* xml, vector<BusLineModel*> busLines) : BaseModel(xml)
{

    for (int i = 0; i < 7; i++)
        TimeSets.push_back(vector<TimeSetModel*>());
    TiXmlNode* xmlDay = nullptr;
    vector<TimeSetModel*> timeSet;
    TiXmlNode* xmlTimeSet = nullptr;
    int day = 0;
    unsigned int busLineId = 0;
    if (xml->QueryUnsignedAttribute("busline", &busLineId) != TIXML_SUCCESS)
        throw exception();
    if ((BusLine = GetModelById(busLines, busLineId)) == nullptr)
        throw exception();
    while ((xmlDay = xml->IterateChildren(xmlDay)) != nullptr)
    {
        TiXmlElement* xmlDayElement = xmlDay->ToElement();
        if (xmlDayElement->QueryIntAttribute("value", &day) != TIXML_SUCCESS)
            throw exception();
        if (day < 0 || day > 6)
            throw exception();
        while ((xmlTimeSet = xmlDay->IterateChildren(xmlTimeSet)) != nullptr)
        {
            TimeSets[day].push_back(new TimeSetModel(xmlTimeSet->ToElement()));
        }
    }
}

TimeTableModel::~TimeTableModel()
{
    for (vector<TimeSetModel*> timeSets: TimeSets)
    {
        for (TimeSetModel* timeSet: timeSets)
        {
            delete timeSet;
        }
    }
}

vector<TimeSetModel*> TimeTableModel::GetTodayTimeSets()
{
    int today = TimeNow().tm_wday;
    return TimeSets[today];
}
vector<TimeSetModel*> TimeTableModel::GetTodayActualTimeSets()
{
    int yesterday = (TimeNow().tm_wday - 1) % 7;
    vector<TimeSetModel*> todayTimeSets = GetTodayTimeSets();
    vector<TimeSetModel*> todayActualTimeSets = {};
    for (TimeSetModel* yTimeSet : TimeSets[yesterday])
    {
        if (yTimeSet->CrossesDay() && CompareTime(yTimeSet->GetLastTime(), TimeNow()) > 0)
            todayActualTimeSets.push_back(yTimeSet);
    }
    for (TimeSetModel* timeSet : todayTimeSets)
    {
        if (timeSet->IsActual() == true)
            todayActualTimeSets.push_back(timeSet);
    }
    return todayActualTimeSets;
}
vector<BusModel> TimeTableModel::GetActiveBuses()
{
    vector<BusModel> buses = {};
    unsigned int id = 1;
    for (TimeSetModel* timeSet: GetTodayActualTimeSets())
    {
        buses.push_back(BusModel(id++, BusLine, timeSet));
    }
    return buses;
}
BusStopModel* TimeTableModel::GetBusStopById(const unsigned int id)
{
    return BusLine->GetBusStopById(id);
}
BusStopModel* TimeTableModel::GetBusStopByIndex(const unsigned int index)
{
    if (index < BusLine->BusStops.size())
        return BusLine->BusStops[index];
    return nullptr;
}
void TimeTableModel::Print(int indent)
{
    PrintIndent(indent);
    cout << "Time Table " << id << " " << "\n";
    BusLine->Print(indent + 1);
    PrintIndent(indent);
    cout << "Time Sets:\n";
    for (int i = 0; i < 7; i++)
    {
        cout << "Day: "<< i << endl;
        for (TimeSetModel* timeSet : TimeSets[i])
        {
            timeSet->Print(indent + 1);
        }
    }


}

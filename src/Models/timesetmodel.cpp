#include "timesetmodel.h"
#include <iostream>
#include <algorithm>
#include "src/TimeLib.h"
TimeSetModel::TimeSetModel(unsigned int id, vector<tm> times) : BaseModel(id)
{
    this->Times = times;
}
TimeSetModel::TimeSetModel(TiXmlElement* xml) : BaseModel(xml)
{
    TiXmlNode* xmlTime = nullptr;
    tm time;
    this->Times = {};
    while ((xmlTime = xml->IterateChildren(xmlTime)) != nullptr)
    {
        TiXmlElement* xmlTimeElement = xmlTime->ToElement();
        if (xmlTimeElement->QueryIntAttribute("hours", &time.tm_hour) != TIXML_SUCCESS)
            throw exception();
        if (xmlTimeElement->QueryIntAttribute("minutes", &time.tm_min) != TIXML_SUCCESS)
            throw exception();
        if (xmlTimeElement->QueryIntAttribute("seconds", &time.tm_sec) != TIXML_SUCCESS)
            throw exception();
        this->Times.push_back(time);
    }
}
tm TimeSetModel::GetFirstTime()
{
    return Times[0];
}
tm TimeSetModel::GetLastTime()
{
    return Times.back();
}
bool TimeSetModel::IsEmpty()
{
    return Times.size() == 0;
}
tm TimeSetModel::GetTimeByIndex(const unsigned int index)
{
    if (index < Times.size())
        return Times[index];
    throw exception();
}
bool TimeSetModel::IsActual()
{
    time_t now = time(0);
    if (IsEmpty() == false)
    {
        bool startOk = CompareTime(*localtime(&now),Times[0]) >= 0;
        bool endOk = CrossesDay() == false ? CompareTime(Times.back(), *localtime(&now)) > 0 : true;
        return  startOk && endOk;
    }
    return false;
}
bool TimeSetModel::CrossesDay()
{
    if (IsEmpty() == false)
    {
        for (unsigned int i = 0; i < Times.size() - 1; i++)
        {
            if (CompareTime(Times[i], Times[i +1]) > 0)
                    return true;
        }

    }
    return false;
}
tm TimeSetModel::GetActualTime()
{
    return Times[GetIndexOfActualTime()];
}
unsigned int TimeSetModel::GetIndexOfActualTime()
{
    unsigned int index = Times.size();
    if (IsActual() == true)
    {
        time_t now = time(0);
        for (vector<tm>::reverse_iterator i = Times.rbegin(); i != Times.rend(); ++i )
        {

            if (CompareTime(*localtime(&now), *i) > 0)
                return index - 1;
            index--;
        }
     }
    throw exception();
}
tm TimeSetModel::GetTimeBetween(unsigned int left, unsigned int right)
{
    return SubtractTime(Times[right], Times[left]);
}

void TimeSetModel::PrintTime(tm time)
{
    cout << time.tm_hour << ":" << time.tm_min << ":" << time.tm_sec << endl;
}
void TimeSetModel::Print(int indent)
{
    PrintIndent(indent);
    cout << "Time Set " << id << "\n";
    for (tm time : Times)
    {
        PrintIndent(indent + 1);
        cout  << time.tm_hour << ":" << time.tm_min << ":" << time.tm_sec << "\n";
    }
}

#include "buslinemodel.h"

BusLineModel::BusLineModel(unsigned int id, string name, vector<BusStopModel*> busStops) : BaseModel(id)
{
    this->BusStops = busStops;
    this->Name = name;
}
BusLineModel::BusLineModel(TiXmlElement* xml, vector<BusStopModel*> busStops, vector<StreetModel*> streets) : BaseModel(xml)
{
    this->Name = xml->Attribute("name");
    TiXmlNode* xmlBusStops = xml->FirstChild("busstops");
    TiXmlNode* xmlPath = xml->FirstChild("path");
    if (xmlBusStops == nullptr || xmlPath == nullptr)
        throw exception();
    BusStops = GetByXml(xmlBusStops, busStops, "busstopid");
    Path = GetByXml(xmlPath, streets, "streetid");

}
BusStopModel* BusLineModel::GetBusStopById(const unsigned int id)
{
    for (BusStopModel* busStop : BusStops)
    {
        if (busStop->id == id)
            return busStop;
    }
    return nullptr;
}
unsigned int BusLineModel::GetIndexByBusStop(const BusStopModel* busStop)
{
    unsigned int index = 0;
    for (BusStopModel* _busStop : BusStops)
    {
        if (_busStop->id == busStop->id)
            return index;
        index++;
    }
    return index;
}

unsigned int BusLineModel::GetStreetIndexByBusStop(BusStopModel *busStop)
{
    unsigned int index = 0;
    for (index = 0; index < Path.size(); index++)
    {
        if (Path[index]->id == busStop->Street->id)
            return index;
    }
    return index;
}
vector<StreetModel*> BusLineModel::GetStreetsBetweenBusStops( BusStopModel *leftBusStop, BusStopModel *rightBusStop, bool skip)
{
    vector<StreetModel*> streets = {};
    unsigned int leftStreetIndex = GetStreetIndexByBusStop(leftBusStop);
    unsigned int rightStreetIndex = GetStreetIndexByBusStop(rightBusStop);
    if (skip == false)
        streets.push_back(leftBusStop->Street);
    for (leftStreetIndex += 1; leftStreetIndex < rightStreetIndex; leftStreetIndex++)
    {
        streets.push_back(Path[leftStreetIndex]);
    }
    if (skip == false)
        streets.push_back(rightBusStop->Street);
    return streets;
}
vector<PointModel*> BusLineModel::GetPointsBetweenBusStops(BusStopModel *leftBusStop, BusStopModel *rightBusStop)
{
    vector<PointModel*> points = {};
    unsigned int leftBusStopIndex = GetIndexByBusStop(leftBusStop);
    unsigned int rightBusStopIndex = GetIndexByBusStop(rightBusStop);
    StreetModel* leftStreet = leftBusStop->Street;
    points.push_back(BusStops[leftBusStopIndex]->Position);
    for (; leftBusStopIndex < rightBusStopIndex; leftBusStopIndex++)
    {
        for (StreetModel* street : GetStreetsBetweenBusStops(BusStops[leftBusStopIndex], BusStops[leftBusStopIndex + 1], true))
        {
            PointModel* point = leftStreet->IsConnectedBy(street);
            if (point == nullptr)
                throw exception();
            points.push_back(point);
            leftStreet = street;
        }
        points.push_back(leftStreet->IsConnectedBy(BusStops[leftBusStopIndex+1]->Street));
        points.push_back(BusStops[leftBusStopIndex+1]->Position);
        leftStreet = BusStops[leftBusStopIndex + 1]->Street;
    }

    return points;
}
double BusLineModel::GetDistanceOfBusStops(unsigned int leftIndex, unsigned int rightIndex)
{

    if (leftIndex < BusStops.size() && rightIndex < BusStops.size() && leftIndex <= rightIndex)
    {
        return GetDistanceOfBusStops(BusStops[leftIndex], BusStops[rightIndex]);
    }
    return 0;

}
double BusLineModel::GetDistanceOfBusStops(BusStopModel *leftBusStop, BusStopModel *rightBusStop)
{
    double distance = 0;
    vector<PointModel*> points = GetPointsBetweenBusStops(leftBusStop, rightBusStop);
    for (unsigned int i = 0; i < points.size() - 1; i++)
    {
        distance += points[i]->GetDistanceFrom(points[i+1]);
    }
    return distance;
}
void BusLineModel::Print(int indent)
{
    PrintIndent(indent);
    cout << "Bus Line " << id << "\n";
    PrintIndent(indent);
    cout << "Path:\n";
    for (StreetModel* street : Path)
    {
        street->Print(indent + 1);
    }
    PrintIndent(indent);
    cout << "BusStops:\n";
    for (BusStopModel * busStop : BusStops)
    {
        busStop->Print(indent + 1);
    }
}

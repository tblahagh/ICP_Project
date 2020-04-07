#include "busstopmodel.h"

BusStopModel::BusStopModel(unsigned int id, double position, StreetModel* street) : BaseModel(id)
{
    this->Street = street;
    CalculatePosition(position);
}
BusStopModel::BusStopModel(TiXmlElement* xml, vector<StreetModel*> streets) : BaseModel(xml)
{
    unsigned int streetId = 0;
    double position = 0;
    if (xml->QueryDoubleAttribute("position", &position))
        throw exception();
    if (xml->QueryUnsignedAttribute("street", &streetId) != TIXML_SUCCESS)
        throw exception();
    if ((Street = GetModelById(streets, streetId)) == nullptr)
        throw exception();
    CalculatePosition(position);
}
BusStopModel::~BusStopModel()
{
    delete Position;
}
void BusStopModel::CalculatePosition(double position)
{
    double x = Street->StartPosition->X +  ((Street->EndPosition->X - Street->StartPosition->X) * position);
    double y = Street->StartPosition->Y + ((Street->EndPosition->Y - Street->StartPosition->Y) * position);
    Position = new PointModel(0, x, y);
}
double BusStopModel::DistanceFromStart()
{
    return Position->GetDistanceFrom(Street->StartPosition);
}
double BusStopModel::DistanceFromEnd()
{
    return Position->GetDistanceFrom(Street->EndPosition);
}
void BusStopModel::Print(int indent)
{
    PrintIndent(indent);
    cout << "Bus Stop " << id << "\n";
    PrintIndent(indent);
    cout << "Position: " << Position << endl;
    Position->Print(indent + 1);
    PrintIndent(indent);
    cout << "Street:\n";
    Street->Print(indent + 1);
}

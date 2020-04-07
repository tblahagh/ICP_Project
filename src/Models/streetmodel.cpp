#include "streetmodel.h"



StreetModel::StreetModel(unsigned int id, string name, PointModel* start, PointModel* end) : BaseModel(id)
{
    this->Name = name;
    this->StartPosition = start;
    this->EndPosition = end;
}

StreetModel::StreetModel(TiXmlElement* xml, vector<PointModel*> points) : BaseModel(xml)
{
    this->Name = xml->Attribute("name");
    unsigned int startId = 0, endId = 0;
    if (xml->QueryUnsignedAttribute("start", &startId) != TIXML_SUCCESS)
        throw exception();
    if (xml->QueryUnsignedAttribute("end", &endId) != TIXML_SUCCESS)
        throw exception();
    if ((StartPosition = BaseModel::GetModelById<PointModel>(points, startId)) == nullptr)
        throw exception();
    if ((EndPosition = GetModelById(points, endId)) == nullptr)
        throw exception();

}
PointModel* StreetModel::IsConnectedBy(StreetModel *street)
{
    if (StartPosition != nullptr && EndPosition != nullptr && street != nullptr && street->StartPosition != nullptr && street->EndPosition != nullptr)
    {
       // bool b1 = StartPosition->id == street->StartPosition->id || StartPosition->id == street->EndPosition->id;
        //bool b2 = EndPosition->id == street->StartPosition->id || EndPosition->id == street->StartPosition->id;
        if (StartPosition->id == street->StartPosition->id || StartPosition->id == street->EndPosition->id)
            return StartPosition;
        else if (EndPosition->id == street->StartPosition->id || EndPosition->id == street->EndPosition->id)
            return EndPosition;

    }
    return nullptr;
}
void StreetModel::Print(int indent)
{
    PrintIndent(indent);
    std::cout<<"Street " << this->id << " " << this->Name << std::endl;
    PrintIndent(indent);
    std::cout << "Start:\n";
    this->StartPosition->Print(indent + 1);
    PrintIndent(indent);
    std::cout << "End:\n";
    this->EndPosition->Print(indent + 1);
}
PointModel* StreetModel::GetOppositePoint(PointModel *point)
{
    if (point->id == StartPosition->id)
        return EndPosition;
    else if (point->id == EndPosition->id)
        return StartPosition;
    return nullptr;
}
double StreetModel::GetLength()
{
    return StartPosition->GetDistanceFrom(EndPosition);
}

#include "pointmodel.h"
#include <iostream>
#include <math.h>

PointModel::PointModel(unsigned int id, int x, int y) : BaseModel(id)
{
    this->X = x;
    this->Y = y;
}

PointModel::PointModel(TiXmlElement* xml) : BaseModel(xml)
{
    if (xml->QueryIntAttribute("x", &X) != TIXML_SUCCESS)
        throw std::exception();
    if (xml->QueryIntAttribute("y", &Y) != TIXML_SUCCESS)
        throw std::exception();
}

void PointModel::Print(int indent)
{
    PrintIndent(indent);
    std::cout << this->id << " [ " << X << " , " << Y << " ]\n";
}

double PointModel::GetDistanceFrom(PointModel *point)
{
    double a = X - point->X;
    double b = Y - point->Y;
    return sqrt((a*a) + (b*b));
}



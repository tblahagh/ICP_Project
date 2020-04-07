#include "basemodel.h"

BaseModel::BaseModel(unsigned int id)
{
    this->id = id;
}
BaseModel::BaseModel(TiXmlElement* xml)
{
    if (xml->QueryUnsignedAttribute("id", &id) != TIXML_SUCCESS)
        throw std::exception();
}
BaseModel::~BaseModel()
{

}
void BaseModel::PrintIndent(int indent)
{
    while (indent-- > 0)
        cout <<"\t";
}



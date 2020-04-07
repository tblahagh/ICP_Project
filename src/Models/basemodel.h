#ifndef BASEMODEL_H
#define BASEMODEL_H

#include "src/tinyxml/tinystr.h"
#include "src/tinyxml/tinyxml.h"
#include <iostream>
#include <vector>
using namespace std;
// Base class from which inherits another model classes
class BaseModel
{
public:
    // unique identifier of the model
    unsigned int id;
    // destructor
    virtual ~BaseModel();
    // basic constructor
    BaseModel(unsigned int id = 0);
    // constructor for creating object from xml
    BaseModel(TiXmlElement* xml);
    // debug function for printing models content on stdout
    virtual void Print(int indent) = 0;
    // templated function that select pointer to model from vector MODELS identified by ID and returns it
    template<class T = BaseModel>
    T* GetModelById(vector<T*> models, unsigned int id)
    {
        for ( auto i = models.begin(); i != models.end(); i++ )
        {
            if ((*i)->id == id)
            {
                return (*i);
            }
        }
        return nullptr;
    }
    // templated function that gets identifiers of models from XML and return vector of pointers to models given by these identifiers
    template<class T = BaseModel>
    vector<T*> GetByXml(TiXmlNode* xml, vector<T*> models, string  idAttribute)
    {
        vector<T*> selectedModels = {};
        T* selectedModel;
        TiXmlNode* xmlModel = nullptr;
        unsigned int id = 0;
        while ((xmlModel = xml->IterateChildren(xmlModel)) != nullptr)
        {
            TiXmlElement* xmlModelElement = xmlModel->ToElement();
            if (xmlModelElement->QueryUnsignedAttribute(idAttribute.c_str(), &id) != TIXML_SUCCESS)
                throw exception();
            if ((selectedModel = GetModelById(models, id)) == nullptr)
                throw exception();
            selectedModels.push_back(selectedModel);
        }
        return selectedModels;
    }
    protected:
    void PrintIndent(int indent);
};


#endif // BASEMODEL_H

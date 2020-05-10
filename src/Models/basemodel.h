/*
 * Autoři: Tomáš Blaha, Vojtěch Wawreczka
 * Datum: 9.5.2020
 * */
#ifndef BASEMODEL_H
#define BASEMODEL_H

#include "src/tinyxml/tinystr.h"
#include "src/tinyxml/tinyxml.h"
#include <iostream>
#include <vector>
#include <QString>
using namespace std;
/**
* Základni třída, ze které dědí ostatní modely
*/
class BaseModel
{
public:

    /**
    * Destruktor
    */
    virtual ~BaseModel();

    /**
     * Základní konstruktor
     * @param id Identifikátor modelu
     */
    BaseModel(unsigned int id = 0);

    /**
     * Konstruktor pro vytvoření modelu z XML uzlu
     * @param xml XML uzel, ze kterého se model vytvoří
     */
    BaseModel(TiXmlElement* xml);

    /**
     * Funkce vrátí identifikátor modelu
     * @return Hodnota vlastnosti id
     */
    int getId();

    /**
     * Ladící metoda pro výpis obsahu modelu na standartní výstup
     * @param Počet tabulátorů před výpisem
     */
    virtual void Print(int indent) = 0;

    /**
     * Šablonová funkce, která vybere ukazatel na model z pole podle identifikátoru
     * @tparam T Typ modelu
     * @param models Pole modelů
     * @param id Identifikátor modelu
     * @return Ukazatel na model vybraný z pole podle identifikátoru
     */
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


    /**
     * Šablonová funkce, která vybere z pole models všechny modely, na které je odkazováno v XML uzlu xml
     * @tparam T Typ modelů
     * @param xml XML uzel
     * @param models Pole již existujích modelů
     * @param idAttribute Řetězec značící atribut v poduzlech obsahující identifikátor modelu
     * @return Pole s ukazateli na vybrané modely
     */
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
                throw new QString("Nepodařilo se načíst položku XML souboru.");
            if ((selectedModel = GetModelById(models, id)) == nullptr)
                throw new QString("Nepodařilo se najít položku XML souboru.");
            selectedModels.push_back(selectedModel);
        }
        return selectedModels;
    }

    // templated function that gets identifiers of models from XML and return vector of pointers to models given by these identifiers
    /**
     * Šablonová funkce, která vybere z identifikátory modelů, na které je odkazováno v XML uzlu xml
     * @tparam T Typ modelů
     * @param xml XML uzel
     * @param idAttribute Řetězec značící atribut v poduzlech obsahující identifikátor modelu
     * @return Pole s vybranými identifikátory
     */
    vector<int> GetIntByXml(TiXmlNode* xml, string  idAttribute)
    {
        vector<int> selectedModels = {};
        TiXmlNode* xmlModel = nullptr;
        unsigned int i = 0;
        while ((xmlModel = xml->IterateChildren(xmlModel)) != nullptr)
        {
            TiXmlElement* xmlModelElement = xmlModel->ToElement();
            if (xmlModelElement->QueryUnsignedAttribute(idAttribute.c_str(), &i) != TIXML_SUCCESS)
                throw new QString("Nepodařilo se načíst položku XML souboru.");
            selectedModels.push_back(i);
        }
        return selectedModels;
    }

protected:
    /**
     * Unikátní identifikátor modelu
     */
    unsigned int id;
    /**
     * Ladící metoda výpis pro odsazení na standartní výstup
     * @param indent Počet tabulátorů
     */
    void PrintIndent(int indent);

};


#endif // BASEMODEL_H

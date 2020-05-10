/*
 * Autoři: Tomáš Blaha, Vojtěch Wawreczka
 * Datum: 9.5.2020
 * */
#ifndef POINTMODEL_H
#define POINTMODEL_H

#include "src/tinyxml/tinystr.h"
#include "src/tinyxml/tinyxml.h"
#include "src/Models/basemodel.h"
#include <iostream>
#include <math.h>



/**
* Třída reprezentující bod ve dvourozměrném prostoru
*/
class PointModel : public BaseModel
{
public:

    /**
     * Základní konstruktor pro vytvoření bodu
     * @param id identifikátor modelu
     * @param x Souřadnice X
     * @param y Souřadnice Y
     */
    PointModel(unsigned int id = 0, double x = 0, double y = 0);

    /**
     * Konstruktor pro vytvoření modelu bodu z XML uzlu
     * @param xml XML uzel, ze kterého se model vytvoří
     */
    PointModel(TiXmlElement* xml);

    /**
     * Vrací souřadnici X
     * @return Hodnota souřadnice X
     */
    double getX();

    /**
     * Vrací souřadnici Y
     * @return Hodnota souřadnice Y
     */
    double getY();

    /**
     * Funkce vypočte vzdálenost bodu od jiného
     * @param point Bod, od kterého se má vypočítat vzdálenost
     * @return Vzdálenost mezi body
     */
    double GetDistanceFrom(PointModel* point);

    /**
     * Ladící metoda pro výpis obsahu modelu na standartní výstup
     * @param počet tabulátorů před výpisem
     */
    virtual void Print(int indent) override;

private:

    /**
     * Souřadnice X
     */
    double X;

    /**
     * Souřadnice Y
     */
    double Y;


};

#endif // POINTMODEL_H

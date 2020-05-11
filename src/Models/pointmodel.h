/*
 * Autoři: Tomáš Blaha, Vojtěch Wawreczka
 * Datum: 9.5.2020
 *
 * Třída reprezentující bod ve dvourozměrném prostoru
 * */
#ifndef POINTMODEL_H
#define POINTMODEL_H

#include "src/tinyxml/tinystr.h"
#include "src/tinyxml/tinyxml.h"
#include "src/Models/basemodel.h"
#include <iostream>
#include <math.h>



/**
* @brief Třída reprezentující bod ve dvourozměrném prostoru
*/
class PointModel : public BaseModel
{
public:

    /**
     * @brief Základní konstruktor pro vytvoření bodu
     * @param id identifikátor modelu
     * @param x Souřadnice X
     * @param y Souřadnice Y
     */
    PointModel(unsigned int id = 0, double x = 0, double y = 0);

    /**
     * @brief Konstruktor pro vytvoření modelu bodu z XML uzlu
     * @param xml XML uzel, ze kterého se model vytvoří
     */
    PointModel(TiXmlElement* xml);

    /**
     * @brief Vrací souřadnici X
     * @return Hodnota souřadnice X
     */
    double getX();

    /**
     * @brief Vrací souřadnici Y
     * @return Hodnota souřadnice Y
     */
    double getY();

    /**
     * @brief Funkce vypočte vzdálenost bodu od jiného
     * @param point Bod, od kterého se má vypočítat vzdálenost
     * @return Vzdálenost mezi body
     */
    double GetDistanceFrom(PointModel* point);

    /**
     * @brief Ladící metoda pro výpis obsahu modelu na standartní výstup
     * @param indent Počet tabulátorů před výpisem
     */
    virtual void Print(int indent) override;

private:

    /**
     * @brief Souřadnice X
     */
    double X;

    /**
     * @brief Souřadnice Y
     */
    double Y;


};

#endif // POINTMODEL_H

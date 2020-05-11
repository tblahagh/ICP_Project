/*
 * Autoři: Tomáš Blaha, Vojtěch Wawreczka
 * Datum: 9.5.2020
 *
 * Třída reprezentující trasu vytvořenou z ulic
 * */
#ifndef PATHMODEL_H
#define PATHMODEL_H
#include "pointmodel.h"
#include <iostream>
#include <vector>
#include <QString>
#include "basemodel.h"
#include "streetmodel.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

class StreetModel;

/**
* @brief Třída reprezentující trasu vytvořenou z ulic
*/
class PathModel : public BaseModel
{
public:
    /**
     * @brief Základní konstruktor
     * @param id Identifikátor modelu
     */
    PathModel(unsigned int id = 0);

    /**
     * @brief Ladící metoda pro výpis obsahu modelu na standartní výstup
     * @param indent počet tabulátorů před výpisem
     */
    virtual void Print(int indent);

    /**
     * @brief Funkce vrací seznam ulic, které tvoří trasu
     * @return Hodnota vlastnosti streets
     */
    vector<StreetModel*> getStreets();

    /**
     * @brief Funkce vrací počáteční bod trasy
     * @return Ukazatel na bod, kterým trasa začíná
     */
    PointModel* getStartPosition();

    /**
     * @brief Funkce vrací koncový bod trasy
     * @return Ukazatel na bod, kterým trasa končí
     */
    PointModel* getEndPosition();

    /**
     * @brief Metoda přidá ulici na konec trasy
     * @param street Ukazatel na přidávanou ulici
     */
    void addStreet(StreetModel* street);

    /**
     * @brief Metoda vymaže všechny ulice v trase
     */
    void clearStreets();

    /**
     * @brief Metoda vyhodí výjimku, pokud je trasa špatně inicializována
     */
    void isCorrect();

    /**
     * @brief Funkce vrací délku trasy
     * @return Délka všech ulic v trase
     */
    double getLenght();

    /**
     * @brief Metoda vymaže ulici na konci trasy
     */
    void clearStreet();

    /**
     * @brief Funkce vrací počet ulic, které tvoří trasu
     * @return Počet ulic
     */
    unsigned int getNumberOfStreets();

private:

    /**
     * @brief Seznam ulic, které tvoří cestu
     */
    vector<StreetModel*> streets;

    /**
     * @brief Ukazatel na bod, který trasa začíná
     */
    PointModel* startPosition = NULL;

    /**
     * @brief Ukazatel na bod, který trasa končí
     */
    PointModel* endPosition = NULL;
};

#endif // PATHMODEL_H

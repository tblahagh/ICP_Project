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

class PathModel : public BaseModel
{
public:
    // konstruktor
    PathModel(unsigned int id = 0);
    // tiskne cestu
    void Print(int indent);
    // vrátí seznam ulic, které tvoří cestu
    vector<StreetModel*> getStreets();
    // vrátí počáteční bod cesty
    PointModel* getStartPosition();
    // vrátí koncový bod cesty
    PointModel* getEndPosition();
    // přidá ulici na konec cesty
    void addStreet(StreetModel* street);
    void clearStreets();
    // zkontroluje, zda je cesta korektní
    void isCorrect();
    double getLenght();
    void clearStreet();
    unsigned int getNumberOfStreets();

private:
    // seznam ulic, které tvoří cestu
    vector<StreetModel*> streets;
    // počáteční bod cesty
    PointModel* startPosition = NULL;
    // koncový bod cesty
    PointModel* endPosition = NULL;
};

#endif // PATHMODEL_H

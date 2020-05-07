#ifndef STREETMODEL_H
#define STREETMODEL_H
#include "src/tinyxml/tinystr.h"
#include "src/tinyxml/tinyxml.h"
#include <cmath>
#include "pointmodel.h"
#include "pathmodel.h"
#include <iostream>
#include <vector>
#include <QString>
#include "basemodel.h"
using namespace std;

class PathModel;

class StreetModel : public BaseModel
{
public:
    // basic constructor
    StreetModel(unsigned int id = 0, QString Name = "", PointModel* start = nullptr, PointModel* end = nullptr);
    // constructor for creating object from xml
    StreetModel(TiXmlElement* xml, vector<PointModel*> points);
    ~StreetModel();
    // vrátí počáteční bod
    PointModel* getStartPosition();
    // vrátí koncový bod
    PointModel* getEndPosition();
    // vrátí jméno
    QString getName();
    // debug function for printing models content on stdout
    virtual void Print(int indent) override;
    // if street is connected by StartPosition or EndPosition with STREET
    // returns pointer to one of this points, nullptr otherwise
    PointModel* IsConnectedBy(StreetModel* street);
    // returns lenght of the street
    double GetLength();
    // if POINT is StartPoint, returns EndPoint and conversely, nullptr otherwise
    PointModel* GetOppositePoint(PointModel* point);
    // get traffic quality on street
    int GetTraffic();
    // set traffic quality on street
    void SetTraffic(int _traffic);
    int GetDelay();
    void SetDelay(int _delay);
    PathModel* GetDetour();
    void SetDetour(PathModel* _detour);

    // returns true if contains end point
    bool ContainsEndPoint(PointModel *point);
    // returns true if contains point
    bool ContainsPoint(PointModel *point, double tolerance = 0);
    // throw exception if street is not correct
    void isCorrect();

private:
    // name of the street
    QString Name = NULL;
    // point, where street starts
    PointModel* StartPosition = NULL;
    // point, where street ends
    PointModel* EndPosition = NULL;
    // traffic quality - 0: closed, 3: excellent
    int traffic = 3;
    // delay of detour
    int delay = 0;
    // path of detour
    PathModel* detour = NULL;

};

#endif // STREETMODEL_H

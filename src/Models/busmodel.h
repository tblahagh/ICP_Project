#ifndef BUSMODEL_H
#define BUSMODEL_H

#include "basemodel.h"
#include "buslinemodel.h"
#include "busstopmodel.h"
#include "pointmodel.h"
#include "clockmodel.h"
// class representing bus

using namespace std;

class ClockModel;
/**
* Třídá reprezentující autobus
*/
class BusModel : public BaseModel
{
public:

    /**
     * Základní konstruktor
     * @param id Identifikátor modelu
     * @param _startTime Čas začátku jízdy autobusu
     * @param busLine Autobusová linka, po které autobus jede
     * @param _clockModel Hodiny, podle kterých se autobus řídí
     */
    BusModel(unsigned int id = 0, tm _startTime = {}, BusLineModel* _busLine = nullptr, ClockModel* _clockModel = nullptr);

    /**
     * Funkce vrací bod, kde se autobus současně nachází
     * @return Bod, kde se autobus nachází
     */
    PointModel CurrentPosition();

    /**
     * Ladící metoda pro výpis obsahu modelu na standartní výstup
     * @param Počet tabulátorů před výpisem
     */
    void Print(int indent) override;

    /**
     * Funkce aktualizuje pozici autobusu
     * @return True, pokud aktualizace proběhla úspěšně, jinak false
     */
    bool actualizePosition();

    /**
     * Funkce posune autobus na další ulici
     * @return True, pokud přechod proběhl úspěšně, jinak false
     */
    bool goToNextStreet();

    /**
     * Metoda posune autobus na zastávku
     */
    void goToNextStop();

    /**
     * Funkce vrací autobusovou linku, po které autobus jede
     * @return Ukazatel na autobusovou linku
     */
    BusLineModel* getBusLine();

    /**
     * Funkce vrací jestli je otevřen detail autobusu
     * @return True, pokud je detail otevřen, jinak false
     */
    bool getOpenedDetail();

    /**
     * Funkce vrací jestli je otevřen detail autobusu
     * @param op Nová hodnota
     */
    void setOpenedDetail(bool op);

    /**
     * Funkce vrací startovní čas jízdy autobusu
     * @return 4as začátku cesty autobusu
     */
    tm getStartTime();

    /**
     * Funkce vrací index další zastávky
     * @return Index do pole zastávek linky
     */
    int getNextStopIndex();

private:
    // pointer to bus line, which is related to this bus
    BusLineModel* busLine = NULL;

    ClockModel* clockModel = NULL;
    int delay;
    tm startTime;

    tm lastActualizeTime;
    double actualSpeed = 0; // in points / seconds

    unsigned int indexOfNextStop = 0;
    double positionOnActualStreet = 0;
    bool directionStartToEnd = true; // direction on actual street


    vector<double> usualSpeedOnPath = {};
    vector<unsigned int> indexOfActualStreetOnPath = {};
    vector<PathModel*> actualPaths = {};
    vector<bool> actualDirectionOnPath = {};


    bool openedDetail = false;
    bool qdebug = false;
};

#endif // BUSMODEL_H

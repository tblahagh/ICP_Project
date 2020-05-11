/*
 * Autoři: Tomáš Blaha, Vojtěch Wawreczka
 * Datum: 9.5.2020
 *
 * Třída reprezentující autobus
 * */
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
* @brief Třída reprezentující autobus
*/
class BusModel : public BaseModel
{
public:

    /**
     * @brief Základní konstruktor
     * @param id Identifikátor modelu
     * @param _startTime Čas začátku jízdy autobusu
     * @param _busLine Autobusová linka, po které autobus jede
     * @param _clockModel Hodiny, podle kterých se autobus řídí
     */
    BusModel(unsigned int id = 0, tm _startTime = {}, BusLineModel* _busLine = nullptr, ClockModel* _clockModel = nullptr);

    /**
     * @brief Funkce vrací bod, kde se autobus současně nachází
     * @return Bod, kde se autobus nachází
     */
    PointModel CurrentPosition();

    /**
     * @brief Ladící metoda pro výpis obsahu modelu na standartní výstup
     * @param indent Počet tabulátorů před výpisem
     */
    void Print(int indent) override;

    /**
     * @brief Funkce aktualizuje pozici autobusu
     * @return True, pokud aktualizace proběhla úspěšně, jinak false
     */
    bool actualizePosition();

    /**
     * @brief Funkce posune autobus na další ulici
     * @return True, pokud přechod proběhl úspěšně, jinak false
     */
    bool goToNextStreet();

    /**
     * @brief Metoda posune autobus na zastávku
     */
    void goToNextStop();

    /**
     * @brief Funkce vrací autobusovou linku, po které autobus jede
     * @return Ukazatel na autobusovou linku
     */
    BusLineModel* getBusLine();

    /**
     * @brief Funkce vrací jestli je otevřen detail autobusu
     * @return True, pokud je detail otevřen, jinak false
     */
    bool getOpenedDetail();

    /**
     * @brief Funkce vrací jestli je otevřen detail autobusu
     * @param op Nová hodnota
     */
    void setOpenedDetail(bool op);

    /**
     * @brief Funkce vrací startovní čas jízdy autobusu
     * @return 4as začátku cesty autobusu
     */
    tm getStartTime();

    /**
     * @brief Funkce vrací index další zastávky
     * @return Index do pole zastávek linky
     */
    int getNextStopIndex();

private:
    /**
     * @brief Model autobusové linky
     */
    BusLineModel* busLine = NULL;

    /**
     * @brief Model hodin, podle kterých se autobus řídí
     */
    ClockModel* clockModel = NULL;

    /**
     * @brief Aktuální zpoždění autobusu
     */
    int delay;

    /**
     * @brief Čas, kdy autobus vyjel na trasu
     */
    tm startTime;

    /**
     * @brief Čas poslední aktualizace pozice autobusu
     */
    tm lastActualizeTime;

    /**
     * @brief Aktuální rychlost autobusu (v bodech za sekundu)
     */
    double actualSpeed = 0;

    /**
     * @brief Index následující zastávky
     */
    unsigned int indexOfNextStop = 0;

    /**
     * @brief Pozice na ulici, kterou autobus právě projíždí
     */
    double positionOnActualStreet = 0;

    /**
     * @brief Směr, kterým autobus právě jede po ulici
     */
    bool directionStartToEnd = true;

    /**
     * @brief Normální rychlost autobusu na trase
     */
    vector<double> usualSpeedOnPath = {};

    /**
     * @brief Index ulice, po ktere autobus právě jede
     */
    vector<unsigned int> indexOfActualStreetOnPath = {};

    /**
     * @brief Trasa, po které autobus právě jede
     */
    vector<PathModel*> actualPaths = {};

    /**
     * @brief Směr, kterým autobus po trase jede
     */
    vector<bool> actualDirectionOnPath = {};

    /**
     * @brief Informuje, zda je otevřený detail autobusu
     */
    bool openedDetail = false;

    /**
     * @brief Ladící proměnná
     */
    bool qdebug = false;
};

#endif // BUSMODEL_H

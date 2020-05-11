/*
 * Autoři: Tomáš Blaha, Vojtěch Wawreczka
 * Datum: 9.5.2020
 *
 * Třída reprezentující autobusovou linku
 * */
#ifndef BUSLINE_H
#define BUSLINE_H

#include "basemodel.h"
#include "busstopmodel.h"
#include <vector>
using namespace std;
/**
 * @brief Třída reprezentující autobusovou linku
 */
class BusLineModel : public BaseModel
{
public:

    /**
     * @brief Základní konstruktor
     * @param id identifikátor modelu
     * @param name Název linky
     * @param busStops Pole autobusových zastávek, ze který se linka skládá
     * @param times Pole časů, za jak dlouho se dostane autobus od jedné zastávky k následující
     * @param path Cesta, po které má autobus jet při jízdě linky
     */
    BusLineModel(unsigned int id = 0, QString name = "", vector<BusStopModel*> busStops = {}, vector<int> times = {}, PathModel* path = NULL);

    /**
     * @brief Konstruktor pro vytvoření modelu z XML uzlu
     * @param xml XML uzel, ze kterého se model vytvoří
     * @param points Pole již existujících zastávek, ze kterých se vyberou zastávky odpovídající dané lince
     * @param streets Pole již existujících ulic, ze kterých se vyberou ulice pro vytvoření cesty
     */
    BusLineModel(TiXmlElement* xml, vector<BusStopModel*> busStops, vector<StreetModel*> streets);

    /**
    * @brief Destruktor
    */
    ~BusLineModel();

    /**
     * @brief Ladící metoda pro výpis obsahu modelu na standartní výstup
     * @param počet tabulátorů před výpisem
     */
    virtual void Print(int indent) override;

    /**
     * @brief Funkce vrací index zastávky v autobusové lince
     * @param busStop Hledaná zastávka
     * @return Index zastávky v poli BusStops
     */
    unsigned int GetIndexByBusStop(BusStopModel* busStop);

    /**
     * @brief Funkce vrací pole bodů, které jsou mezi zastávkami
     * @param leftBusStop Zastávka která je v lince dříve
     * @param rightBusStop Zastávka, která je v lince později
     * @return Pole bodů na cestě mezi leftBusStop a rightBusStop
     */
    vector<PointModel*> GetPointsBetweenBusStops(BusStopModel* leftBusStop, BusStopModel* rightBusStop);

    /**
     * @brief Funkce vrací ulice mezi zastávkami
     * @param leftBusStop Zastávka která je v lince dříve
     * @param rightBusStop Zastávka, která je v lince později
     * @param skip Pokud je true, vynechají se ulice, na kterých leží zastávky
     * @return Pole ulic mezi zastávkami
     */
    vector<StreetModel*> GetStreetsBetweenBusStops(BusStopModel* leftBusStop , BusStopModel* rightBusStop, bool skip = false);

    /**
     * @brief Funkce vrací index ulice v cestě
     * @param street Hledaná ulice
     * @return Index ulice v poli
     */
    unsigned int GetIndexOfStreet(StreetModel* street);

    /**
     * @brief Funkce vrací index ulice v cestě podle zastávky
     * @param busStop Zastávka na hledané ulici
     * @return Index ulice v poli
     */
    unsigned int GetStreetIndexByBusStop(BusStopModel* busStop);

    /**
     * @brief Funkce vrací vzdálenost na cestě mezi zastávkami
     * @param leftIndex Index zastávky, která je v lince dříve
     * @param rightIndex Index zastávky, která je v lince později
     * @return Vzdálenost mezi zastávkami
     */
    double GetDistanceOfBusStops(unsigned int leftIndex, unsigned int rightIndex);

    /**
     * @brief Funkce vrací vzdálenost na cestě mezi zastávkami
     * @param leftIndex Zastávka, která je v lince dříve
     * @param rightIndex Zastávka, která je v lince později
     * @return Vzdálenost mezi zastávkami
     */
    double GetDistanceOfBusStops(BusStopModel* leftBusStop, BusStopModel* rightBusStop);

    /**
     * @brief Funkce vrací jak dlouho trvá jízda linky v minutách
     * @return Délka jízdy v minutách
     */
    int getDurationInMinutes();

    /**
     * @brief Funkce vrací název linky
     * @return Hodnota vlastnosti name
     */
    QString getName();

    /**
     * @brief Funkce vrací zastávky linky
     * @return Hodnota vlastnosti busStops
     */
    vector<BusStopModel*> getBusStops();

    /**
     * @brief Funkce vrací minuty mezi zastávkami
     * @return Hodnota vlastnosti times
     */
    vector<int> getTimes();

    /**
     * @brief Funkce vrací trasu linky
     * @return Hodnota vlastnosti path
     */
    PathModel* getPath();

    /**
     * @brief Funkce vyhodí výjimku, pokud je linka špatně inicializována
     */
    void isCorrect();

private:
    /**
     * @brief Název linky
     */
    QString name = "";

    /**
     * @brief Zastávky linky
     */
    vector<BusStopModel*> busStops;

    /**
     * @brief Cesta linky
     */
    PathModel* path = NULL;

    /**
     * @brief Minuty mezi zastávkami
     */
    vector<int> times;

};

#endif // BUSLINE_H

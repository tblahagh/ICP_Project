/*
 * Autoři: Tomáš Blaha, Vojtěch Wawreczka
 * Datum: 9.5.2020
 * */
#ifndef BUSSTOPMODEL_H
#define BUSSTOPMODEL_H
#include "src/Models/streetmodel.h"
#include "src/Models/basemodel.h"
#include "src/tinyxml/tinystr.h"
#include "src/tinyxml/tinyxml.h"
using namespace std;
/**
 * Třída reprezentující autobusovou zástávku
 */
class BusStopModel : public BaseModel
{
public:

    /**
     * Základní konstruktor
     * @param id Identifikátor modelu
     * @param name Jméno zastávky
     * @param position Pozice, jak daleko od počátečního bodu ulice se zastávka nachází
     * @param street Ukazatel na model ulice, kde se zastávka nachází
     */
    BusStopModel(unsigned int id = 0, QString name = "", double position = 0, StreetModel* street = nullptr);

    /**
     * Konstruktor pro vytvoření modelu z XML uzlu
     * @param xml XML uzel, ze kterého se model vytvoří
     * @param streets Pole s ukazateli na ulice, ze kterého se vybere ulice, kde se zastávka nachází
     */
    BusStopModel(TiXmlElement* xml, vector<StreetModel*> streets);

    /**
    * Destruktor
    */
    ~BusStopModel();

    /**
     * Funkce vrací ulici kde se zastávka nachází
     * @return Hodnota vlastnosti street
     */
    StreetModel* getStreet();

    /**
     * Funkce vrací bod, kde se zastávka nachází
     * @return Hodnota vlastnosti position
     */
    PointModel* getPosition();
    /**
     * Funkce vrací hodnotu, jak daleko se zastávka nachází od počátečního bodu
     * @return Hodnota vlastnosti positionOnStreet
     */
    double getPositionOnStreet();

    /**
     * Funkce vrací název zastávky
     * @return Hodnota vlastnosti name
     */
    QString getName();

    /**
     * Metoda vyhodí výjimku, pokud je zastávka špatně inicializována
     */
    void isCorrect();

    /**
     * Ladící metoda pro výpis obsahu modelu na standartní výstup
     * @param indent počet tabulátorů před výpisem
     */
    virtual void Print(int indent) override;

    /**
     * Funkce vrací vzdálenost mezi zástávkou a počátečním bodem ulice
     * @return Číslo značící vzdálenost mezi zastávkou a počátečním bodem ulice
     */
    double DistanceFromStart();

    /**
     * Funkce vrací vzdálenost mezi zástávkou a koncovým bodem ulice
     * @return Číslo značící vzdálenost mezi zastávkou a koncovým bodem ulice
     */
    double DistanceFromEnd();
private:

    /**
     * Funkce vrací hodnotu, jak daleko se zastávka nachází od počátečního bodu
     * @param position vzdálenost od počátečního bodu, kde 0 znamená, že bod se nachází přesně na na začátku ulice a 1, že se nachází na konci ulice
     */
    void CalculatePosition(double position);

    /**
     * Ulice, kde se zastávka nachází
     */
    StreetModel* street;
    /**
     * Bod, kde se zastávka nachází
     */
    PointModel* position;
    /**
     * Procentuální vzdálenost od počátečního bodu
     * 0 - Zastávka leží na počátečním bodu
     * 1 - Zastávka leží na koncovém bodu
     */
    double positionOnStreet = 0;
    /**
     * Jméno zastávky
     */
    QString name;

};

#endif // BUSSTOPMODEL_H

/*
 * Autoři: Tomáš Blaha, Vojtěch Wawreczka
 * Datum: 9.5.2020
 *
 * Třída, která reprezentuje ulici
 * */
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
/**
* @brief Třída, která reprezentuje ulici
*/
class StreetModel : public BaseModel
{
public:
    /**
     * @brief Základní konstruktor
     * @param id identifikátor modelu
     * @param name Název ulice
     * @param start Bod, kde ulice začíná
     * @param end Bod, kde ulice končí
     */
    StreetModel(unsigned int id = 0, QString name = "", PointModel* start = nullptr, PointModel* end = nullptr);

    /**
     * @brief Konstruktor pro vytvoření modelu z XML uzlu
     * @param xml XML uzel, ze kterého se model vytvoří
     * @param points Pole již existujících ukazatelů na body, ze kterých se vybere začínající i koncový bod ulice
     */
    StreetModel(TiXmlElement* xml, vector<PointModel*> points);

    /**
    * @brief Destruktor
    */
    ~StreetModel();

    /**
     * @brief Vrací počáteční bod
     * @return Ukazatel na bod, kde ulice začíná
     */
    PointModel* getStartPosition();

    /**
     * @brief Vrací koncový bod
     * @return Ukazatel na bod, kde ulice končí
     */
    PointModel* getEndPosition();

    /**
     * @brief Vrací jméno ulice
     * @return Řetězec obsahující jméno ulice
     */
    QString getName();

    /**
     * @brief Ladící metoda pro výpis obsahu modelu na standartní výstup
     * @param indent počet tabulátorů před výpisem
     */
    virtual void Print(int indent) override;

    /**
     * @brief Funkce vrací bod, kterým je ulice propojena s jinou ulicí
     * @param street ukazatel na ulici, se kterou se kontroluje spojení
     * @return Ukazatel na počáteční nebo koncový bod ulice nebo nullptr
     */
    PointModel* IsConnectedBy(StreetModel* street);

    /**
     * @brief Funkce vypočítá délku ulice neboli vzdálenost mezi počátečním a koncovým bodem
     * @return Vzdálenost mezi počátečním a koncovám bodem
     */
    double GetLength();

    /**
     * @brief Funkce vrací opačný bod k bodu point, tedy pokud je point počáteční bod, vrací koncový a naopak, pokud point není počáteční ani koncový, vrací nullptr
     * @param point Bod, ke kterému má být vrácen bod opačný
     * @return Počáteční nebo koncový bod ulice nebo nullptr
     */
    PointModel* GetOppositePoint(PointModel* point);

    /**
     * @brief Funkce vrací hustotu provozu na ulici
     * @return Hustota provozu na ulici
     */
    int GetTraffic();

    /**
     * @brief Metoda nastaví hustotu provozu na ulici
     * @param _traffic Nová hodnota hustoty provozu
     */
    void SetTraffic(int _traffic);

    /**
     * @brief Funkce vrací hodnotu zpoždění při jízdě odbočkou
     * @return Celé číslo reprezentující míru zpoždění při jízdě odbočkou
     */
    int GetDelay();

    /**
     * @brief Metoda nastaví hodnotu zpoždění při jízdě odbočkou
     * @param _delay Nová hodnota zpoždění při jízdě odbočkou
     */
    void SetDelay(int _delay);

    /**
     * @brief Funkce vrací trasu odbočky, pokud je ulice uzavřená
     * @return PathModel reprezentující ulice, po kterých se má autobus vydat, pokud je ulice uzavřená
     */
    PathModel* GetDetour();

    /**
     * @brief Metoda nastaví trasu odbočky, pokud je ulice uzavřená
     * @param _detour PathModel reprezentující ulice, po kterých se má autobus vydat, pokud je ulice uzavřená
     */
    void SetDetour(PathModel* _detour);

    /**
     * @brief Funkce kontroluje jestli bod point je buď počáteční nebo koncový bod
     * @param point Bod ke kontrole
     * @return True, pokud je point počáteční nebo koncový bod, jinak false
     */
    bool ContainsEndPoint(PointModel *point);

    /**
     * @brief Funkce kontroluje jestli bod point leží na ulici s určitou tolerancí
     * @param point Bod ke kontrole
     * @param tolerance Tolerance, jak moc může bod být mimo úsečku ulice
     * @return True, pokud bod leží na ulici, jinak false
     */
    bool ContainsPoint(PointModel *point, double tolerance = 0);
    /**
     * Metoda vyhodí výjimku, pokud je s ulice špatně inicializována
     */
    void isCorrect();

private:
    /**
     * @brief Jméno ulice
     */
    QString Name = NULL;

    /**
     * @brief Počáteční bod ulice
     */
    PointModel* StartPosition = NULL;

    /**
     * Koncový bod ulice
     */
    PointModel* EndPosition = NULL;

    /**
     * @brief Míra zácpy v ulici: 0 - Zavřeno, 3 - Volno
     */
    int traffic = 3;

    /**
     * @brief Zpoždění při jízdě odbočkou
     */
    int delay = 0;
    /**
     * @brief Odbočka
     */
    PathModel* detour = NULL;

};

#endif // STREETMODEL_H

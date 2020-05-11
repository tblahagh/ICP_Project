/*
 * Autoři: Tomáš Blaha, Vojtěch Wawreczka
 * Datum: 9.5.2020
 *
 * Třída reprezentující jízdní řád
 * */
#ifndef TIMETABLEMODEL_H
#define TIMETABLEMODEL_H

#include "basemodel.h"
#include "buslinemodel.h"
#include "busmodel.h"
#include <vector>

using namespace std;
/**
 * @brief Třída reprezentující jízdní řád
 */
class TimeTableModel : public BaseModel
{
public:


    /**
     * @brief Základní kostruktor
     * @param id Identifikátor model
     * @param busLine Autobusová linka, které se řád týka
     * @param startTimes Časy příjezdu autobusu na zastávky
     */
    TimeTableModel(unsigned int id = 0, BusLineModel* busLine = nullptr, vector<tm> startTimes = {});

    /**
     * @brief Konstruktor pro vytvoření řádu z XML uzlu
     * @param xml XML uzel
     * @param busLines Ukazatele na autobusové linky
     */
    TimeTableModel(TiXmlElement* xml, vector<BusLineModel*> busLines);

    /**
     * @brief Destruktor
     */
    ~TimeTableModel();

    /**
     * @brief Funkce vrací časy zastávek
     * @return Časy zastávek
     */
    vector<tm> getStartTimes();

    /**
     * @brief Funkce vrací autobusovou linku
     * @return Ukazatel na autobusovou linku
     */
    BusLineModel* getBusLine();

    /**
     * @brief Funkce vyhodí výjimku, pokud je linka špatně inicializována
     */
    void isCorrect();

    /**
     * @brief Ladící metoda pro výpis obsahu modelu na standartní výstup
     * @param Počet tabulátorů před výpisem
     */
    virtual void Print(int indent) override;

private:

    /**
     * @brief Časy zastávek
     */
    vector<tm> StartTimes;
    /**
     * @brief Autobusová linka
     */
    BusLineModel* BusLine;
};

#endif // TIMETABLEMODEL_H

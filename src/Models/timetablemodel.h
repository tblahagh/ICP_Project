/*
 * Autoři: Tomáš Blaha, Vojtěch Wawreczka
 * Datum: 9.5.2020
 * */
#ifndef TIMETABLEMODEL_H
#define TIMETABLEMODEL_H

#include "basemodel.h"
#include "buslinemodel.h"
#include "busmodel.h"
#include <vector>

using namespace std;
/**
 * Třída reprezentující jízdní řád
 */
class TimeTableModel : public BaseModel
{
public:


    /**
     * Základní kostruktor
     * @param id Identifikátor model
     * @param busLine Autobusová linka, které se řád týka
     * @param startTimes Časy příjezdu autobusu na zastávky
     */
    TimeTableModel(unsigned int id = 0, BusLineModel* busLine = nullptr, vector<tm> startTimes = {});

    /**
     * Konstruktor pro vytvoření řádu z XML uzlu
     * @param xml XML uzel
     * @param busLines Ukazatele na autobusové linky
     */
    TimeTableModel(TiXmlElement* xml, vector<BusLineModel*> busLines);

    /**
     * Destruktor
     */
    ~TimeTableModel();

    /**
     * Funkce vrací časy zastávek
     * @return Časy zastávek
     */
    vector<tm> getStartTimes();

    /**
     * Funkce vrací autobusovou linku
     * @return Ukazatel na autobusovou linku
     */
    BusLineModel* getBusLine();

    /**
     * Funkce vyhodí výjimku, pokud je linka špatně inicializována
     */
    void isCorrect();

    /**
     * Ladící metoda pro výpis obsahu modelu na standartní výstup
     * @param Počet tabulátorů před výpisem
     */
    virtual void Print(int indent) override;

private:

    /**
     * Časy zastávek
     */
    vector<tm> StartTimes;
    /**
     * Autobusová linka
     */
    BusLineModel* BusLine;
};

#endif // TIMETABLEMODEL_H

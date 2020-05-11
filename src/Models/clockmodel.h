/*
 * Autoři: Tomáš Blaha, Vojtěch Wawreczka
 * Datum: 9.5.2020
 *
 * Třída reprezentující hodiny v systému
 * */
#ifndef CLOCKMODEL_H
#define CLOCKMODEL_H
#include <QString>
#include <iostream>
#include <time.h>
#include "src/mainwindow.h"

using namespace std;

class MainWindow;
class ClockView;
class ClockDetailView;
class BusModel;
/**
 * @brief Třída reprezentující hodiny v systému
 */
class ClockModel
{
public:

    /**
     * @brief Základní konstruktor, který nastaví hodiny na aktuální čas
     */
    ClockModel();

    /**
     * @brief Metoda inicializuje hodiny na zadaný čas
     * @param _hour Nové hodiny
     * @param _minute Nové minuty
     * @param _second Nové sekundy
     */
    void initialize(int _hour, int _minute, int _second);

    /**
     * @brief Funkce převede hodiny na text
     * @return Řetězec s časem hodin
     */
    QString getString();

    /**
     * @brief Metoda provede tiknutí hodin
     */
    void tick();

    /**
     * @brief Metoda přičte sekundu
     */
    void increase();

    /**
     * @brief Metoda nastaví rychlost hodin
     * @param _speed Nová rychlost
     */
    void setSpeed(int _speed);

    /**
     * @brief Funkce vrací rychlost hodin
     * @return Rychlost hodin
     */
    int getSpeed();

    /**
     * @brief Funkce vrací počet hodin
     * @return Počet hodin
     */
    int getHour();

    /**
     * @brief Funkce vrací počet sekund
     * @return Počet minut
     */
    int getMinute();

    /**
     * @brief Funkce vrací počet sekund
     * @return Počet sekund
     */
    int getSecond();

    /**
     * @brief Funkce vrátí čas převedený na typ tm
     * @return Čas převedený na typ tm
     */
    tm getTime();



private:
    /**
     * @brief Hodiny
     */
    int hour = 1;
    /**
     * @brief Minuty
     */
    int minute = 1;
    /**
     * @brief Sekundy
     */
    int second = 1;
    /**
     * @brief Rychlost
     */
    int speed = 1;
};

#endif // CLOCKMODEL_H

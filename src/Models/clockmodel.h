/*
 * Autor: Vojtěch Wawreczka
 * Datum: 9.5.2020
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
 * Třída reprezentující hodiny v systému
 */
class ClockModel
{
public:

    /**
     * Základní konstruktor, který nastaví hodiny na aktuální čas
     */
    ClockModel();

    /**
     * Metoda inicializuje hodiny na zadaný čas
     * @param Nové hodiny
     * @param Nové minuty
     * @param Nové sekundy
     */
    void initialize(int _hour, int _minute, int _second);

    /**
     * Funkce převede hodiny na text
     * @return Řetězec s časem hodin
     */
    QString getString();

    /**
     * Metoda provede tiknutí hodin
     */
    void tick();

    /**
     * Metoda přičte sekundu
     */
    void increase();

    /**
     * Metoda nastaví rychlost hodin
     */
    void setSpeed(int _speed);

    /**
     * Funkce vrací rychlost hodin
     * @return Rychlost hodin
     */
    int getSpeed();

    /**
     * Funkce vrací počet hodin
     * @return Počet hodin
     */
    int getHour();

    /**
     * Funkce vrací počet sekund
     * @return Počet minut
     */
    int getMinute();

    /**
     * Funkce vrací počet sekund
     * @return Počet sekund
     */
    int getSecond();

    /**
     * Funkce vrátí čas převedený na typ tm
     * @return Čas převedený na typ tm
     */
    tm getTime();



private:
    /**
     * Hodiny
     */
    int hour = 1;
    /**
     * Minuty
     */
    int minute = 1;
    /**
     * Sekundy
     */
    int second = 1;
    /**
     * Rychlost
     */
    int speed = 1;
};

#endif // CLOCKMODEL_H

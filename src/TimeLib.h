/*
 * Autoři: Tomáš Blaha, Vojtěch Wawreczka
 * Datum: 9.5.2020
 *
 * Jednoduchá knihovna pro práci s časem
 * */
#ifndef TIMELIB_H
#define TIMELIB_H
#include <time.h>
#include <QString>


/**
 * @brief Funkce převede typ tm na počet sekund
 * @param time Čas typu tm
 * @return Počet sekund
 */
int TimeToSeconds(tm time);

/**
 * @brief Funkce převede počet sekund na typ tm
 * @param seconds Počet sekund
 * @return Čas typu tm
 */
tm SecondsToTime(int seconds);

/**
 * @brief Funkce porovná časy
 * @param time1 První čas
 * @param time2 Druhý čas
 * @return Kladné číslo, pokud je první čas později než druhý, 0 pokud jsou stejné, jinak záporné číslo
 */
int CompareTime(tm time1, tm time2);

/**
 * @brief Funkce vytvoří nový čas, který je rozdílem dvou časů
 * @param time1 První čas
 * @param time2 Druhý čas
 * @return Čas, který je rozdílem časů daných parametry
 */
tm SubtractTime(tm time1, tm time2);
/**
 * @brief Funkce vrací aktuální čas
 * @return Aktuální čas
 */
tm TimeNow();
/**
 * @brief Funkce ověří, jestli je jeden čas mezi dvoumi dalšími
 * @param time1 První čas
 * @param time2 Druhý čas
 * @param time Čas, který má být mezi prvním a druhám časem
 * @return True, pokud je mezi, jinak false
 */
bool IsTimeBetween(tm time1, tm time2, tm time);
/**
 * @brief Metoda provede kontrolu času, pokud je špatný, vyhodí výjimku
 * @param time Kontrolovaný čas
 */
void IsCorrectTime(tm time);
/**
 * @brief Funkce vrací čas jako řetězec
 * @param i
 * @return Čas převedený na řetězec
 */
QString timeNumberToStr(int i);
#endif // TIMELIB_H

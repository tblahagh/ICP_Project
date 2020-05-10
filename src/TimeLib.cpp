/*
 * Autoři: Tomáš Blaha, Vojtěch Wawreczka
 * Datum: 9.5.2020
 * */
#include "TimeLib.h"

//------------------------------------------------------------------
// Funkce převede typ tm na počet sekund
int TimeToSeconds(tm time)
{
    return time.tm_hour * 3600 + time.tm_min * 60 + time.tm_sec;
}

//--------------------------------------------------------------------
// Funkce převede počet sekund na typ tm
tm SecondsToTime(int seconds)
{
    tm time;

    time.tm_hour = seconds / 3600;
    seconds -= time.tm_hour * 3600;
    time.tm_min = seconds / 60;
    seconds -= time.tm_min * 60;
    time.tm_sec = seconds;
    return time;
}

//---------------------------------------------------------------------
// Funkce porovná časy
int CompareTime(tm time1, tm time2)
{
    return TimeToSeconds(time1) - TimeToSeconds(time2);
}

//-------------------------------------------------------------------
// Funkce ověří, jestli je jeden čas mezi dvoumi dalšími
bool IsTimeBetween(tm time1, tm time2, tm time){
    int t1 = TimeToSeconds(time1);
    int t2 = TimeToSeconds(time2);
    if(t2 < t1) t2 += 24*60*60;

    int t = TimeToSeconds(time);
    if(t1 < t && t <= t2) return true;
    return false;
}

//----------------------------------------------------------------------
// Funkce vytvoří nový čas, který je rozdílem dvou časů
tm SubtractTime(tm time1, tm time2)
{

    int seconds = TimeToSeconds(time1) - TimeToSeconds(time2);
    return SecondsToTime(seconds);
}

//-----------------------------------------------------------------------
// Funkce vrací aktuální čas
tm TimeNow()
{
    time_t now = time(0);
    return *localtime(&now);
}

//-------------------------------------------------------------------------
//  Metoda provede kontrolu času, pokud je špatný, vyhodí výjimku
void IsCorrectTime(tm time){
    if(time.tm_hour < 0 || time.tm_hour > 23) throw new QString("Hodina musí být v rozmezí 0 - 23.");
    if(time.tm_min < 0 || time.tm_min > 59) throw new QString("Minuta musí být v rozmezí 0 - 59.");
    if(time.tm_sec < 0 || time.tm_sec > 59) throw new QString("Sekunda musí být v rozmezí 0 - 59.");

}

//-------------------------------------------------------------------------
// Funkce vrací čas jako řetězec
QString timeNumberToStr(int i){
    if(i < 0 && i > -10) return QString ("-0" + QString::number(i));
    else if(i < 10) return QString ("0" + QString::number(i));
    else return QString::number(i);
}

#include "clockmodel.h"

//***********************************************************************************
// kontruktory, destruktory, tisk
//------------------------------------------------------------------------------------

//----------------------------------------------------------------
// Základní konstruktor, který nastaví hodiny na aktuální čas
ClockModel::ClockModel(){

    time_t Time = time(NULL);
    struct tm *tm = localtime(&Time);

    initialize(tm->tm_hour, tm->tm_min, tm->tm_sec);

}
//---------------------------------------------------------------
// Metoda inicializuje hodiny na zadaný čas
void ClockModel::initialize(int _hour, int _minute, int _second)
{
    if(_hour < 0 || _hour > 23) throw new QString("Hodina musí být v intervalu 0 - 23");
    if(_minute < 0 || _minute > 59) throw new QString("Minuta musí být v intervalu 0 - 59");
    if(_second < 0 || _second > 59) throw new QString("Sekunda musí být v intervalu 0 - 59");

    this->hour = _hour;
    this->minute = _minute;
    this->second = _second;
}
//*******************************************************************************
// metody get, set, add
//-------------------------------------------------------------------------------



//------------------------------------------------------------------
// Metoda nastaví rychlost hodin
void ClockModel::setSpeed(int _speed){
    if(_speed < 0 || _speed > 50) throw new QString("Rychlost musí být v intervalu 0 - 50.");

    speed = _speed;
}

//-----------------------------------------------------------------
// Funkce vrací rychlost hodin
int ClockModel::getSpeed(){
    return speed;
}


//--------------------------------------------------------------------
// Funkce vrací počet hodin
int ClockModel::getHour(){
    return hour;
}

//------------------------------------------------------------------
// Funkce vrací počet sekund
int ClockModel::getMinute(){
    return minute;
}

//-------------------------------------------------------------------
// Funkce vrací počet sekund
int ClockModel::getSecond(){
    return second;
}

//------------------------------------------------------------------
// Funkce převede hodiny na text
QString ClockModel::getString(){
    QString string = QString(13);

    if(hour <= 9) string.append("0");
    string.append(QString::number(hour));
    string.append(":");

    if(minute <= 9) string.append("0");
    string.append(QString::number(minute));
    string.append(":");

    if(second <= 9) string.append("0");
    string.append(QString::number(second));

    return string;
}

//-------------------------------------------------------------------
// Funkce vrátí čas převedený na typ tm
tm ClockModel::getTime(){
    tm time;
    time.tm_hour = this->hour;
    time.tm_min = this->minute;
    time.tm_sec = this->second;
    return time;
}

//************************************************************************************
// výpočetní metody
//----------------------------------------------------------------------------------

//------------------------------------------------------------
// provede kliknutí hodin - přičte 1-n sekund podle rychlosti
void ClockModel::tick(){
    for(int i=0;i<speed;i++) increase();
}

//-------------------------------------------------------------
// přičte sekundu
void ClockModel::increase(){
    second++;
    if(second >= 60){
        second = 0;
        minute++;
        if(minute >= 60){
            minute = 0;
            hour++;
            if(hour >= 24){
                hour = 0;
            }
        }
    }
}


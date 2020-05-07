#include "clockmodel.h"

//***********************************************************************************
// kontruktory, destruktory, tisk
//------------------------------------------------------------------------------------

//----------------------------------------------------------------
// konstruktor
ClockModel::ClockModel(){

    time_t Time = time(NULL);
    struct tm *tm = localtime(&Time);

    initialize(tm->tm_hour, tm->tm_min, tm->tm_sec);

}

//*******************************************************************************
// metody get, set, add
//-------------------------------------------------------------------------------

//---------------------------------------------------------------
// inicializace podle zadaného času
void ClockModel::initialize(int _hour, int _minute, int _second)
{
    if(_hour < 0 || _hour > 23) throw new QString("Hodina musí být v intervalu 0 - 23");
    if(_minute < 0 || _minute > 59) throw new QString("Minuta musí být v intervalu 0 - 59");
    if(_second < 0 || _second > 59) throw new QString("Sekunda musí být v intervalu 0 - 59");

    this->hour = _hour;
    this->minute = _minute;
    this->second = _second;
}

//------------------------------------------------------------------
// nastavení rychlosti
void ClockModel::setSpeed(int _speed){
    if(_speed < 0 || _speed > 50) throw new QString("Rychlost musí být v intervalu 0 - 50.");

    speed = _speed;
}

//-----------------------------------------------------------------
// vrátí rychlost
int ClockModel::getSpeed(){
    return speed;
}


//--------------------------------------------------------------------
// vrátí hodinu
int ClockModel::getHour(){
    return hour;
}

//------------------------------------------------------------------
// vrátí minutu
int ClockModel::getMinute(){
    return minute;
}

//-------------------------------------------------------------------
// vrátí sekundu
int ClockModel::getSecond(){
    return second;
}

//------------------------------------------------------------------
// vrátí textovou hodnotu hodin
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
// vrátí sekundu
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


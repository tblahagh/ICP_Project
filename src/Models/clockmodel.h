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

class ClockModel
{
public:
    ClockModel();
    void initialize(int _hour, int _minute, int _second);
    QString getString();
    void tick();
    void increase();

    void setSpeed(int _speed);
    int getSpeed();
    int getHour();
    int getMinute();
    int getSecond();
    tm getTime();



private:
    int hour = 1;
    int minute = 1;
    int second = 1;
    int speed = 1;
};

#endif // CLOCKMODEL_H

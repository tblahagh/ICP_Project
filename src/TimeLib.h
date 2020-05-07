#ifndef TIMELIB_H
#define TIMELIB_H
#include <time.h>
#include <QString>
// simple library for working with time

// converts TIME to seconds
int TimeToSeconds(tm time);
// converts SECONDS to tm
tm SecondsToTime(int seconds);
// compares two times, if TIME1 > TIME2 return positive number
// else negative or zero
int CompareTime(tm time1, tm time2);
// returns new difference between TIME1 and TIME2
tm SubtractTime(tm time1, tm time2);
// returns present time
tm TimeNow();
bool IsTimeBetween(tm time1, tm time2, tm time);

void IsCorrectTime(tm time);

QString timeNumberToStr(int i);
#endif // TIMELIB_H

#include "TimeLib.h"

int TimeToSeconds(tm time)
{
    return time.tm_hour * 3600 + time.tm_min * 60 + time.tm_sec;
}
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
int CompareTime(tm time1, tm time2)
{
    return TimeToSeconds(time1) - TimeToSeconds(time2);
}
tm SubtractTime(tm time1, tm time2)
{

    int seconds = TimeToSeconds(time1) - TimeToSeconds(time2);
    return SecondsToTime(seconds);
}
tm TimeNow()
{
    time_t now = time(0);
    return *localtime(&now);
}

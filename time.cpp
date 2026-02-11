#include "time.h"

Time::Time() :passedTime(0), year(0), month(0), day(0), hour(0), minute(0), second(0)
{
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    passedTime = currentTime;
    std::tm *localTime;
    localTime = std::localtime(&currentTime);
    populateFromTm(*localTime);
}

Time::Time(std::time_t passedTime, int year, int month, int day, int hour, int minute, int second) : passedTime(passedTime), year(year), month(month), day(day), hour(hour), minute(minute), second(second)
{}

void Time::populateFromTm(std::tm &t)
{
    year = t.tm_year + 1900; // tm_year is years since 1900
    month = t.tm_mon + 1;  // tm_mon is months since January (0-11)
    day = t.tm_mday;
    hour = t.tm_hour;
    minute = t.tm_min;
    second = t.tm_sec;
}

void Time::displayTime()
{
    printf("%d-%.2d-%.2d %.2d:%.2d:%.2d\n", year, month, day, hour, minute, second);
}

int Time::operator-(Time &other)
{
    return abs(this->passedTime - other.passedTime);
}


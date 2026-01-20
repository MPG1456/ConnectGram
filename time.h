#pragma once

#include <iostream>
#include <chrono>
#include <ctime>

using namespace std;

class Time
{
private:
    std::time_t passedTime; //Time passed 1970-01-01 00:00:00 UTC
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;

    void populateFromTm(std::tm &t);

public:
    Time();
    Time(std::time_t passedTime, int year, int month, int day, int hour, int minute, int second);
    void displayTime();
    int operator-(Time &other);
};
#include "date.h"

Date::Date(int day, int month, int year)
{
    this->day = day;
    this->month = month;
    this->year = year;
}

int Date::getDay()
{
    return day;
}

int Date::getMonth()
{
    return month;
}

int Date::getYear()
{
    return year;
}

int getDiffInDates(Date oldDate, Date newDate)
{
    int totalDaysInOldDate = (365 * oldDate.getYear()) + (30 * oldDate.getMonth()) + oldDate.getDay();
    int totalDaysInNewDate = (365 * newDate.getYear()) + (30 * newDate.getMonth()) + newDate.getDay();
    return totalDaysInNewDate - totalDaysInOldDate;
}
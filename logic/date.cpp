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
    int diffInYears = newDate.getYear() - oldDate.getYear();
    int diffInMonths = newDate.getMonth() - oldDate.getMonth();
    int diffInDays = newDate.getDay() - oldDate.getDay();

    return (diffInYears * 365) + (diffInMonths * 30) + diffInDays;
}
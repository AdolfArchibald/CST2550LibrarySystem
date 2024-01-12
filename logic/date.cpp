#include "date.h"
#include <cmath>

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

int getDiffInDates(Date date1, Date date2)
{
    // Set the number of days in each month
    const int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Convert each date to total days
    int totalDays1 = date1.getYear() * 365 + date1.getDay();
    for (int month = 0; month < date1.getMonth(); month++) {
        totalDays1 += daysInMonth[month];
    }

    int totalDays2 = date2.getYear() * 365 + date2.getDay();
    for (int month = 0; month < date2.getMonth(); month++) {
        totalDays2 += daysInMonth[month];
    }
    
     // Calculate the absolute difference in days
    if (totalDays2 - totalDays1 <= 0) {
        return std::abs(totalDays2 - totalDays1);
    }
    return 0;
}
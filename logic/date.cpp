#include "date.h"

Date::Date()
{
    // Get the time since the epoch.
    time_t now = std::time(0);
    // Convert the time to a readable format.
    this->instantiatedTime = *std::localtime(&now);
}

std::tm Date::getInstantiationTime()
{
    return instantiatedTime;
}

std::tm Date::getCurrentDateAndTime()
{
    // Get the time since the epoch.
    time_t now = std::time(0);
    // Convert the time to a readable format and return it.
    return *std::localtime(&now);
}

double Date::calcTimeDiff(std::tm newTime, std::tm oldTime)
{   
    // Cast the given times into time_t to calculate the difference.
    std::time_t newTimeT = std::mktime(&newTime);
    std::time_t oldTimeT = std::mktime(&oldTime);

    return std::difftime(newTimeT, oldTimeT);
}

#include "date.h"

Date::Date(std::time_t offset)
{
    // Set the time to monitor based on the epoch and offset.
    this->timeToMonitor = std::time(0) + offset;
}

std::time_t Date::getTimeToMonitor()
{
    return timeToMonitor;
}

std::time_t Date::getCurrentDateAndTime()
{
    // Get the time since the epoch.
    std::time_t now = std::time(0);
    return now;
}

double Date::calcTimeDiff(time_t newTime, time_t oldTime)
{   
    return std::difftime(newTime, oldTime);
}

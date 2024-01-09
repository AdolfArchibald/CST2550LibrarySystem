#ifndef _DATE_H_
#define _DATE_H_

#include <ctime>

class Date {
    private:
        std::time_t timeToMonitor;

    public:
        Date::Date(std::time_t offset = 0);

        std::time_t getTimeToMonitor();
        std::time_t getCurrentDateAndTime();

        // void addDays(std::time_t currentDay, int days);

        double calcTimeDiff(std::time_t newTime, std::time_t oldTime);
};

#endif
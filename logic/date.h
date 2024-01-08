#ifndef _DATE_H_
#define _DATE_H_

#include <ctime>

class Date {
    private:
        std::tm instantiatedTime;
    
    public:
        std::tm getInstantiationTime();
        std::tm getCurrentDateAndTime();

        double calcTimeDiff(std::tm newTime, std::tm oldTime);
};

#endif
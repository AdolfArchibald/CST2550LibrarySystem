#ifndef _DATE_H_
#define _DATE_H_

class Date {
    private:
        int day;
        int month;
        int year;

    public:
        Date(int day, int month, int year);

        int getDay();
        int getMonth();
        int getYear();
};

int getDiffInDates(Date oldDate, Date  newDate);

#endif
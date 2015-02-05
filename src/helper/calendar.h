#ifndef CALENDAR_H
#define CALENDAR_H

#include <time.h>

class Calendar {
  
  public:
    // constructor
    Calendar();

    // enum days, months
    enum WEEKDAY_TYPE { SUNDAY, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY };

    enum MONTH_TYPE { JANUARY, FEBRUARY, MARCH, APRIL, MAY, JUNE,
                      JULY, AUGUST, SEPTEMBER, OCTOBER, NOVEMBER, DECEMBER };

    // methods
    void outputDate();     
    
    bool isLeapYear(int year);
    int totalDaysInMonth(int month, int year);

    // getter   
    int getWeekDay();
    int getDay();
    int getMonth();
    int getYear();

    char* getTimeToString();
    char* getDayToString(int weekday);
    char* getMonthToString(int month);

    // setter
    

  private:
    // private variables
    time_t t;    

    // private methods
    
};

#endif

#ifndef CALENDAR_H
#define CALENDAR_H

#include <time.h>
#include <string>
using namespace std;

class Calendar {
  
  public:
    // constructor
    Calendar();

    // enum days, months
    enum WEEKDAY_TYPE { NOT_USED_D, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY };

    enum MONTH_TYPE { NOT_USED_M , JANUARY, FEBRUARY, MARCH, APRIL, MAY, JUNE,
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
    char* getDate(int);

    // setter
 
    // parse date
    int parseDay(const char *date);
    int parseMonth(const char *date);
    int parseYear(const char *date); 

    bool is_number(string str);

  private:
    // private variables
    time_t t;

    int tmp_day;
    int tmp_month;
    int tmp_year;
    int tmp_limit;
    int tmp_count;

    // private methods
    void scanForward();
    void scanBackward();
};

#endif

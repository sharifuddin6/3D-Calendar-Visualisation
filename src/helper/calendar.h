/*
 * The calendar class interface for the visualisation software. 
 * Skeleton code of the structure of the calendar with accessors 
 * and other calendar related functions.
 *
 * Copyright (c) 2015 Sharif UDDIN
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR
 * ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */


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

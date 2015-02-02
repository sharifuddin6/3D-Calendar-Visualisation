#include "calendar.h"
#include <stdio.h>
#include <string.h>

#include <iostream>
using namespace std;

// constructor
Calendar::Calendar() { 
  t = time(NULL);
}

// methods
void Calendar::outputDate() {
  // ouput datetime to console 	
	tm* timePtr = localtime(&t);

  cout << "seconds= " << timePtr->tm_sec << endl;
  cout << "minutes = " << timePtr->tm_min << endl;
  cout << "hours = " << timePtr->tm_hour << endl;
  cout << "day of month = " << timePtr->tm_mday << endl;
  cout << "month of year = " << timePtr->tm_mon+1 << endl;
  cout << "year = " << timePtr->tm_year+1900 << endl;
  cout << "weekday = " << timePtr->tm_wday << endl;
  cout << "day of year = " << timePtr->tm_yday << endl;
  cout << "daylight savings = " << timePtr->tm_isdst << endl;
}

bool Calendar::isLeapYear(int year) {
  // returns boolean for the leap year case
  bool value = false;
  if(year%4==0 && (year%100!=0 || year%400==0)) {
    value = true;
  }
  printf("%d:%s\n", year, value?"true":"false");
  return value;
}

int Calendar::totalDaysInMonth(int month, int year) {
  int totalDays = 0;
  
  if(month==APRIL || month==JUNE || month==SEPTEMBER || month==NOVEMBER) {
    totalDays = 30;
  } else if(month==JANUARY || month==MARCH || month==MAY || month==JULY ||
            month==AUGUST || month==OCTOBER || month==DECEMBER) {
    totalDays = 31;
  } else if(month==2) {
    if(isLeapYear(year)) {
      totalDays = 29;
    } else {
      totalDays = 28;
    }
  }
  printf("%d,%d : %d\n", month, year, totalDays);
  return totalDays;
}

// getters
int Calendar::getWeekDay() {
  // returns current weekday
	tm* timePtr = localtime(&t);
  int weekday = timePtr->tm_wday;
}

int Calendar::getDay() {
  // returns current day
	tm* timePtr = localtime(&t);
  int day = timePtr->tm_mday;
  return day;
}

int Calendar::getMonth() {
  // returns current month
	tm* timePtr = localtime(&t);
  int month = timePtr->tm_mon;
  return month;
}

int Calendar::getYear() {
  // returns current year
	tm* timePtr = localtime(&t);
  int year = timePtr->tm_year+1900;
  return year;
}


char* Calendar::getTimeToString() {
  // returns time in char* form
  tm* timePtr = localtime(&t);
  // char buffer for time
  char *buff = new char[16];

  int min = timePtr->tm_min;
  int hour = timePtr->tm_hour;
  char* timezone;

  // decide PM/AM
  if(hour>12) {
    timezone = "PM";
  } else {
    timezone = "AM";
  }

  // quick fix for single digit minutes to natural form
  if(min<10) {
    sprintf(buff, "%d:%d%d%s", hour, 0, min, timezone);
  } else {
    sprintf(buff, "%d:%d%s", hour, min, timezone);
  }

  return buff;
}

char* Calendar::getDayToString(int weekday) {
  // returns day in name form given index
  // char buffer for weekday
  char *buff = new char[10];
  
  switch(weekday) {
    case SUNDAY:
      strcpy(buff, "SUNDAY");
      break;
    case MONDAY:
      strcpy(buff, "MONDAY");
      break;
    case TUESDAY:
      strcpy(buff, "TUESDAY");
      break;
    case WEDNESDAY:
      strcpy(buff, "WEDNESDAY");
      break;
    case THURSDAY:
      strcpy(buff, "THURSDAY");
      break;
    case FRIDAY:
      strcpy(buff, "FRIDAY");
      break;
    case SATURDAY:
      strcpy(buff, "SATURDAY");
      break;
    default:
      strcpy(buff, "UNKNOWN");
      break;
  };

  return buff;
}

char* Calendar::getMonthToString(int month) {
  // returns month in name form given index
  // char buffer for month
  char *buff = new char[10];
  
  switch(month) {
    case JANUARY:
      strcpy(buff, "JANUARY");
      break;
    case FEBRUARY:
      strcpy(buff, "FEBRUARY");
      break;
    case MARCH:
      strcpy(buff, "MARCH");
      break;
    case APRIL:
      strcpy(buff, "APRIL");
      break;
    case MAY:
      strcpy(buff, "MAY");
      break;
    case JUNE:
      strcpy(buff, "JUNE");
      break;
    case JULY:
      strcpy(buff, "JULY");
      break;
    case AUGUST:
      strcpy(buff, "AUGUST");
      break;
    case SEPTEMBER:
      strcpy(buff, "SEPTEMBER");
      break;
    case OCTOBER:
      strcpy(buff, "OCTOBER");
      break;
    case NOVEMBER:
      strcpy(buff, "NOVEMBER");
      break;
    case DECEMBER:
      strcpy(buff, "DECEMBER");
      break;
    default:
      strcpy(buff, "UNKNOWN");
      break;
  };

  return buff;
}

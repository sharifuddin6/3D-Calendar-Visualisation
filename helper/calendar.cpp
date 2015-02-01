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
  
  if(month==4 || month==6 || month==9 || month==11) {
    totalDays = 30;
  } else if(month==1 || month==3 || month==5 || month==7 || month==8 || month==10 || month==12) {
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
  int month = timePtr->tm_mon+1;
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
  sprintf(buff, "%d:%d", timePtr->tm_hour, timePtr->tm_min);
  return buff;
}

char* Calendar::getDayToString(int weekday) {
  // returns day in name form given index
  // char buffer for weekday
  char *buff = new char[10];
  
  switch(weekday) {
    case 0:
      strcpy(buff, "SUNDAY");
      break;
    case 1:
      strcpy(buff, "MONDAY");
      break;
    case 2:
      strcpy(buff, "TUESDAY");
      break;
    case 3:
      strcpy(buff, "WEDNESDAY");
      break;
    case 4:
      strcpy(buff, "THURSDAY");
      break;
    case 5:
      strcpy(buff, "FRIDAY");
      break;
    case 6:
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
    case 1:
      strcpy(buff, "JANUARY");
      break;
    case 2:
      strcpy(buff, "FEBRUARY");
      break;
    case 3:
      strcpy(buff, "MARCH");
      break;
    case 4:
      strcpy(buff, "APRIL");
      break;
    case 5:
      strcpy(buff, "MAY");
      break;
    case 6:
      strcpy(buff, "JUNE");
      break;
    case 7:
      strcpy(buff, "JULY");
      break;
    case 8:
      strcpy(buff, "AUGUST");
      break;
    case 9:
      strcpy(buff, "SEPTEMBER");
      break;
    case 10:
      strcpy(buff, "OCTOBER");
      break;
    case 11:
      strcpy(buff, "NOVEMBER");
      break;
    case 12:
      strcpy(buff, "DECEMBER");
      break;
    default:
      strcpy(buff, "UNKNOWN");
      break;
  };

  return buff;
}

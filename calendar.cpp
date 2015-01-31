#include "calendar.h"
#include <stdio.h>
#include <time.h>

#include <iostream>
using namespace std;

Calendar::Calendar() { }

void Calendar::outputDate() {
  // ouput datetime to console
 	time_t t = time(NULL);
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

int Calendar::getDay() {
  time_t t = time(NULL);
	tm* timePtr = localtime(&t);
  int day = timePtr->tm_mday;
  return day;
}

int Calendar::getMonth() {
  time_t t = time(NULL);
	tm* timePtr = localtime(&t);
  int month = timePtr->tm_mon+1;
  return month;
}

int Calendar::getYear() {
  time_t t = time(NULL);
	tm* timePtr = localtime(&t);
  int year = timePtr->tm_year+1900;
  return year;
}

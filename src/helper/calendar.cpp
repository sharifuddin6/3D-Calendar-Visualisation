#include "calendar.h"
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iostream>
#include <vector>
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
//  printf("%d:%s\n", year, value?"true":"false");
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
//  printf("%d,%d : %d\n", month, year, totalDays);
  return totalDays;
}

// getters
int Calendar::getWeekDay() {
  // returns current weekday
	tm* timePtr = localtime(&t);
  int weekday = timePtr->tm_wday;
  
  if(weekday == 0) { // by default sunday's value is 0, 
    return 7;        // but this application sunday has value 7
  } else {
    return weekday;
  }

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
  char *buffer = new char[32];

  int min = timePtr->tm_min;
  int hour = timePtr->tm_hour;
  char timezone[3];

  // decide PM/AM
  if(hour>12) {
    strcpy(timezone, "PM");
  } else {
    strcpy(timezone, "AM");
  }

  // quick fix for single digit minutes to natural form
  if(min<10) {
    sprintf(buffer, "%d:%d%d%s", hour, 0, min, timezone);
  } else {
    sprintf(buffer, "%d:%d%s", hour, min, timezone);
  }

  return buffer;
}

char* Calendar::getDayToString(int weekday) {
  // returns day in name form given index
  // char buffer for weekday
  char *buff = new char[11];
  
  switch(weekday) {
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
    case SUNDAY:
      strcpy(buff, "SUNDAY");
      break;
    default:
      strcpy(buff, "UNKNOWN");
      printf("%d\n", weekday);
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

char* Calendar::getDate(int index) {
  // returns date from today to given index
  // char buffer for date
  char *buff = new char[12];

  tmp_count = index;
  tmp_day = getDay();
  tmp_month = getMonth();
  tmp_year = getYear();
  tmp_limit = totalDaysInMonth(tmp_month, tmp_year);
  //printf("%d,%d,%d->%d,%d\n", tmp_day, tmp_month, tmp_year, tmp_count, tmp_limit);

  // calculates date from today
  if(index == 0) {
    // Do nothing.
  } else if(tmp_count>0) {
    scanForward();
  } else {
    scanBackward();
  }

  snprintf(buff, 12, "%d,%d,%d", tmp_day, tmp_month, tmp_year);
  return buff;
}

void Calendar::scanForward() {
  while(tmp_count>0) {
    if(tmp_day+1<=tmp_limit) {                                // case where next day is within this month
      tmp_day+=1;
    } else {                                                  // case where next day is first of next month
      tmp_day = 1;
      if(tmp_month+1<=12) {                                   // case where next month is within this year 
        tmp_month+=1;
        tmp_limit = totalDaysInMonth(tmp_month, tmp_year);
      } else {                                                // case where next month is first month of next year
        tmp_month = 1;
        tmp_year+=1;
        tmp_limit = totalDaysInMonth(tmp_month, tmp_year);
      }
    }
    tmp_count-=1;
  }
}

void Calendar::scanBackward() {
  while(tmp_count<0) {
    if(tmp_day-1 > 0) {                                       // case where previous day is within this month
      tmp_day-=1;
    } else {                                                  // case where previous day is last of previous month
      if(tmp_month-1>0) {                                     // case where previous month is within this year 
        tmp_month-=1;
        tmp_limit = totalDaysInMonth(tmp_month, tmp_year);
        tmp_day = tmp_limit;
      } else {                                                // case where previous month is last month of previous year
        tmp_month = 12;
        tmp_year-=1;
        tmp_limit = totalDaysInMonth(tmp_month, tmp_year);
        tmp_day = tmp_limit;
      }
    }
    tmp_count+=1;
  }
}

int Calendar::parseDay(const char* date) {
  int day=0;
  vector<string> tmpDate;
  istringstream ss(date);
  while (!ss.eof()) {
    string out;               // here's a nice, empty string
    getline(ss, out, ',');    // try to read the next field into it
    //printf("OUT: %s\n", out.c_str());  // output parsed data from line to console
    tmpDate.push_back(out);
  }

  string string_day = tmpDate[0];
  istringstream buffer(string_day);
  buffer >> day;
  buffer.clear(); ss.clear(); // clear stream
  return day;
}

int Calendar::parseMonth(const char* date) {
  int month=0;
  vector<string> tmpDate;
  istringstream ss(date);
  while (!ss.eof()) {
    string out;               // here's a nice, empty string
    getline(ss, out, ',');    // try to read the next field into it
    //printf("OUT: %s\n", out.c_str());  // output parsed data from line to console
    tmpDate.push_back(out);
  }

  string string_month = tmpDate[1];
  istringstream buffer(string_month);
  buffer >> month;
  buffer.clear(); ss.clear(); // clear stream
  return month;
}

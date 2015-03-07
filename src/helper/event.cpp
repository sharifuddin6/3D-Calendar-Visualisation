#include "event.h"
#include "string"
#include "string.h"
#include "stdio.h"
using namespace std;

// constructor
Event::Event() { }

// getters
char* Event::getSubject() {
  return subject;
}

char* Event::getStartDate() {
  return startDT;
}

char* Event::getStartTime() {
  return startTM;
}

char* Event::getEndDate() {
  return endDT;
}

char* Event::getEndTime() {
  return endTM;
}

char* Event::getDescription() {
  return description;
}

char* Event::getLocation() {
  return location;
}

// setters
void Event::setSubject(const char* newSubject) {
  string tmp = string(newSubject);
  subject = new char[tmp.length() + 1];
  strcpy(subject, tmp.c_str());
  tmp.clear();
}

void Event::setStartDate(const char* newStartDate) {
  string tmp = string(newStartDate);
  startDT = new char[tmp.length() + 1];
  strcpy(startDT, tmp.c_str());
  tmp.clear();
}

void Event::setStartTime(const char* newStartTime) {
  string tmp = string(newStartTime);
  startTM = new char[tmp.length() + 1];
  strcpy(startTM, tmp.c_str());
  tmp.clear();
}

void Event::setStartDateTime(const char* newStartDateTime) {
  string dateString = string(newStartDateTime);
  string year = dateString.substr(2,2);
  string month = dateString.substr(4,2);
  string day = dateString.substr(6,2);

  string hour = dateString.substr(9,2);
  string min = dateString.substr(11,2);
  string sec = dateString.substr(13,2);

  char dateBuff[10];
  char timeBuff[10];
  sprintf(dateBuff, "%s/%s/%s", day.c_str(), month.c_str(), year.c_str());
  sprintf(timeBuff, "%s:%s:%s", hour.c_str(), min.c_str(), sec.c_str());
  string date(dateBuff);
  string time(timeBuff);

  setStartDate(date.c_str());
  setStartTime(time.c_str());
}

void Event::setEndDate(const char* newEndDate) {
  string tmp = string(newEndDate);
  endDT = new char[tmp.length() + 1];
  strcpy(endDT, tmp.c_str());
  tmp.clear();
}

void Event::setEndTime(const char* newEndTime) {
  string tmp = string(newEndTime);
  endTM = new char[tmp.length() + 1];
  strcpy(endTM, tmp.c_str());
  tmp.clear();
}

void Event::setEndDateTime(const char* newEndDateTime) {
  string dateString = string(newEndDateTime);
  string year = dateString.substr(0,4);
  string month = dateString.substr(4,2);
  string day = dateString.substr(6,2);

  string hour = dateString.substr(9,2);
  string min = dateString.substr(11,2);
  string sec = dateString.substr(13,2);

  char dateBuff[10];
  char timeBuff[10];
  sprintf(dateBuff, "%s/%s/%s", day.c_str(), month.c_str(), year.c_str());
  sprintf(timeBuff, "%s:%s:%s", hour.c_str(), min.c_str(), sec.c_str());
  string date(dateBuff);
  string time(timeBuff);

  setEndDate(date.c_str());
  setEndTime(time.c_str());
}

void Event::setDescription(const char* newDescription) {
  string tmp = string(newDescription);
  description = new char[tmp.length() + 1];
  strcpy(description, tmp.c_str());
  tmp.clear();
}

void Event::setLocation(const char* newLocation) {
  string tmp = string(newLocation);
  location = new char[tmp.length() + 1];
  strcpy(location, tmp.c_str());
  tmp.clear();
}


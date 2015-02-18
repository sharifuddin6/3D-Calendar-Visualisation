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
//  string tmp = string(newDescription);
//  description = new char[tmp.length() + 1];
//  strcpy(description, tmp.c_str());
//  tmp.clear();
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
//  string tmp = string(newEndDateTime);
//  endDT = new char[tmp.length() + 1];
//  strcpy(endDT, tmp.c_str());
//  tmp.clear();
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


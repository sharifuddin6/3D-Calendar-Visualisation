/*
 * The event class implementation for the visualisation software. 
 * Implementation code of the structure of an event container with accessors 
 * and setters for the items in event class.
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

int Event::getIcon() {
  return icon;
}

int Event::getImportance() {
  return importance;
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

void Event::setIcon(int newIcon) {
  icon = newIcon;
}

void Event::setImportance(int newImportance) {
  importance = newImportance;
}

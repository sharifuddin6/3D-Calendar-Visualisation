#include "event.h"
#include "string.h"
#include "stdio.h"

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

}

void Event::setStartDate(const char* newStartDate) {

}

void Event::setStartTime(const char* newStartTime) {

}

void Event::setStartDateTime(const char* newStartDateTime) {

}

void Event::setEndDate(const char* newEndDate) {

}

void Event::setEndTime(const char* newEndTime) {

}

void Event::setEndDateTime(const char* newEndDateTime) {

}

void Event::setDescription(const char* newDescription) {
  description = new char[sizeof(newDescription)+1];
  strcpy(description, newDescription);
}

void Event::setLocation(const char* newLocation) {

}

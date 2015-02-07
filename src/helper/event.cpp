#include "event.h"

// constructor
Event::Event( char *new_subject, char *new_startDT, char *new_startTM,
              char *new_endDT, char *new_endTM, 
              char *new_description, char *new_location) {

  subject = new_subject;
  startDT = new_startDT;
  startTM = new_startTM;
  endDT = new_endDT;
  endTM = new_endTM;
  description = new_description;
  location = new_location;

}

// getters
char *Event::getSubject() {
  return subject;
}

char *Event::getStartDate() {
  return startDT;
}

char *Event::getStartTime() {
  return startTM;
}

char *Event::getEndDate() {
  return endDT;
}

char *Event::getEndTime() {
  return endTM;
}

char *Event::getDescription() {
  return description;
}

char *Event::getLocation() {
  return location;
}

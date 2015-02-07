#ifndef EVENT_H
#define EVENT_H

class Event {
  
  public:
    // constructor
    Event(
      char *new_subject,
      char *new_startDT,
      char *new_startTM,
      char *new_endDT,
      char *new_endTM,
      char *new_description,
      char *new_location
    );

    // getters
    char *getSubject();
    char *getStartDate();
    char *getStartTime();
    char *getEndDate();
    char *getEndTime();
    char *getDescription();
    char *getLocation();

  private:
    char *startDT;
    char *endDT;
    char *startTM;
    char *endTM;

    char *subject;
    char *description;
    char *location;

};

#endif

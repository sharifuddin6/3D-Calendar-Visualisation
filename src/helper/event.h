#ifndef EVENT_H
#define EVENT_H

class Event {
  
  public:
    // constructor
    Event();

    // getters
    char* getSubject();
    char* getStartDate();
    char* getStartTime();
    char* getEndDate();
    char* getEndTime();
    char* getDescription();
    char* getLocation();

    // setters
    void setSubject(const char* newSubject);
    void setStartDate(const char* newStartDate);
    void setStartTime(const char* newStartTime);
    void setStartDateTime(const char* newStartDateTime);
    void setEndDate(const char* newEndDate);
    void setEndTime(const char* newEndTime);
    void setEndDateTime(const char* newEndDateTime);
    void setDescription(const char* newDescription);
    void setLocation(const char* newLocation);

  private:
    char* startDT;
    char* endDT;
    char* startTM;
    char* endTM;

    char* subject;
    char* description;
    char* location;

};

#endif

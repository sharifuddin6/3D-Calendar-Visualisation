/*
 * The event class interface for the visualisation software. 
 * Skeleton code of the structure of an event container with accessors 
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

    int getIcon();
    int getImportance();

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

    void setIcon(int newIcon);
    void setImportance(int newImportance);

  private:
    char* startDT;
    char* endDT;
    char* startTM;
    char* endTM;

    char* subject;
    char* description;
    char* location;

    int icon;
    int importance;

};

#endif

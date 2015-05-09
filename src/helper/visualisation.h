/*
 * The visualisation class interface for the visualisation software. 
 * Skeleton code of various structures and draw methods for related
 * visualisations.
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


#ifndef VISUALISATION_H
#define VISUALISATION_H

#include "../appModel.h"
#include "../../include/objmodelloader/objectLoader.h"
#include "calendar.h"

#include <GL/freeglut.h>
#include <vector>
using namespace std;


class Visualisation {
  // stucture for a day object
  struct aDay {
    aDay() {
      event_id = -1;    
    }
  
    int day;
    int month;
    int year;
    int weekday;
    int week;
    int event_id;
    int event_icon;
    int event_importance;

    char* event_subject;
    char* event_startDate;
    char* event_startTime;
    char* event_endDate;
    char* event_endTime;
    char* event_location;
  };

  // structure for unique colour id per object
  struct object_id {
    object_id() { }

    // set unique colour depending on index for picker
    void set_index(int index) {
      r = 64;
      g = index+1;
      b = index+1;
    }

    void set_colour() {
      glColor3f((double)r/256.0f, (double)g/256.0f, (double)b/256.0f);
    }

    // colour id
    int r;
    int g;
    int b;
  };


  public:
    // constructor
    Visualisation(AppModel *newAppModel);

    // methods
    void init();
    void initDate();
    void initLoad();

    // draw methods
    void render(int frame);

    void drawDate(int weekday, int day);
    void drawDay(int weekday, int day);
    void drawText(const char* text);

    void draw_giftbox(float alpha); // draw id : 1
    void draw_memo(float alpha);    // draw id :
    void draw_work(float alpha);    // draw id :
    void draw_holiday(float alpha); // draw id :
    void draw_meeting(float alpha); // draw id :

 
    void draw_radialtile();         // draw id : 
    void draw_radialface();
    void draw_flattile();

    void draw_icon(int value, int scale, float alpha, bool highlight);
    void draw_importance(int value);

    void draw_outline(int draw_id, float alpha, bool highlight);

    // getter
    char* getPrototypeName();
    int getPrototypeNameLen();

    char* getEventSubject();
    char* getEventStartDateTime();
    char* getEventEndDateTime();
    char* getEventLocation();
    
    // setter
    void setPrototype(int newMode);

  private:
    // private variables
    int mode;
    float selected;
    char* prototype_name;
    int name_length;

    float tile_dimension;
    float scale;
    float gap;

    vector<aDay> days;
    vector<object_id> object_id_array;

    // private objects
    AppModel *appModel;
    ObjectLoader *objLoader;  
    Calendar calendar;   

    // private methods
    void prototype_1();
    void prototype_2();
    void prototype_3();
    void prototype_4();
    void prototype_5();

    void radial_pos(int index);
    void curve_pos(float index);
    void grid_pos(int week, int weekday, int day);


    float computeScale(const char *text);
    void smooth_selection(int frame);
    void pickerCheck();
    bool pickerMode;
    bool pickerModeDebug;
    bool wire_mode;
    bool hasEvent;

};

#endif

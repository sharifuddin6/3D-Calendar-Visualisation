#ifndef VISUALISATION_H
#define VISUALISATION_H

#include <GL/glut.h>
#include "../appModel.h"
#include "calendar.h"
#include <vector>
using namespace std;


class Visualisation {
  // stucture for a day object
  struct aDay {
    aDay() { }
  
    int day;
    int month;
    int weekday;
    int week;
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
    void draw(int frame);
    void drawTile(int weekday, int day);
    void drawText(const char* text);
    void drawMarker();
    
    // getter
    char* getPrototypeName();
    int getPrototypeNameLen();
    
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
    Calendar calendar;   

    // private methods
    void init();
    
    void prototype_1();
    void prototype_2();
    void prototype_3();
    void prototype_4();
    void prototype_5();

    void prototype_1_curve(float index);
    void prototype_2_drawTile(int week, int weekday, int day);
    
    float computeScale(const char *text);
    void smooth_selection(int frame);
    void pickerCheck();
    bool pickerMode;
    bool pickerModeDebug;
    
};

#endif

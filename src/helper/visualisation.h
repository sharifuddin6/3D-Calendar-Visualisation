#ifndef VISUALISATION_H
#define VISUALISATION_H

#include "calendar.h"
#include <vector>
using namespace std;


class Visualisation {
  
  struct aDay {
    aDay() { }
  
    int day;
    int month;
    int weekday;
    int week;
  };

  public:
    // constructor
    Visualisation();

    // methods
    void draw(int frame);
    void drawTile(int weekday, int day);

    void drawText(const char* text);
    float computeScale(const char *text);

    // getter
    char* getPrototypeName();
    int getPrototypeNameLen();
    
    // setter
    void setPrototype(int newMode);


  private:
    // private variables
    int mode;
    char* prototype_name;
    int name_length;

    float tile_dimension;
    float scale;
    float gap;

    vector<aDay> days;

    // private objects
    Calendar calendar;   

    // private methods
    void init();
    
    void prototype_1();
    void prototype_2();
    void prototype_3();
    void prototype_4();

    void prototype_1_drawTile(int week, int weekday, int day);
    

};

#endif

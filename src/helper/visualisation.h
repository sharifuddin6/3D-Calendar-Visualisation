#ifndef VISUALISATION_H
#define VISUALISATION_H

#include "calendar.h"

class Visualisation {
  
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

    int days;
    int weeks;

    // private objects
    Calendar calendar;   

    // private methods
    void prototype_1();
    void prototype_2();
    void prototype_3();
    void prototype_4();

    void drawTile_prototype_1(int weekday, int week);

};

#endif

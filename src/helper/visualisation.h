#ifndef VISUALISATION_H
#define VISUALISATION_H

#include <GL/glut.h>

#include "calendar.h"

class Visualisation {
  
  public:
    // constructor
    Visualisation();

    // methods
    void draw(int frame);
    void drawTile(int weekday, int day);

    // getter
    char* getPrototypeName();
    
    // setter
    void setPrototype(int newMode);


  private:
    // private variables
    int mode;
    char* prototype_name;

    float tile_dimension;
    int days;
    int weeks;

    // private objects
    Calendar calendar;   

    // private methods
    void prototype_1();
    void prototype_2();
    void prototype_3();
    void prototype_4();

};

#endif

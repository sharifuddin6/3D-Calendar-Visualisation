#ifndef CALENDAR_H
#define CALENDAR_H

#include <GL/glut.h>

class Calendar {
  
  public:
    Calendar();
    void draw(int frame);
    void drawText(float x, float y, const char *string);

    void setPrototype(int newMode);


  private:
    int mode;

    float tile_dimension;
    int days;
    int weeks;

    void prototype_1();
    void prototype_2();
    void prototype_3();
    void prototype_4();

};

#endif

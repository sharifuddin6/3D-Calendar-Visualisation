#ifndef APPCONTROLLER_H
#define APPCONTROLLER_H

#include <stdio.h>
#include <GL/glut.h>

#include "appModel.h"

class AppController {

  public:
    // constructor
    AppController(AppModel *newAppModel);

    // enum menu options
    enum MENU_TYPE { MENU_1, MENU_2, MENU_3, MENU_4, MENU_5 };

    virtual void menu(int item);
    virtual void mouse(int button, int state, int x, int y);
    virtual void keyboard(unsigned char key, int x, int y);
    virtual void specialInput(int key, int x, int y);

  private:
    AppModel *appModel;
    float pos_x, pos_y, pos_z;
    float selected;

};

#endif

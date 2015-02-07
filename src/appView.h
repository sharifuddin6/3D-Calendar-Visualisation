#ifndef APPVIEW_H
#define APPVIEW_H

#include <GL/glut.h>
#include <stdio.h>
#include <string.h>

#include "appModel.h"
#include "appController.h"

#include "helper/visualisation.h"
#include "helper/calendar.h"

class AppView {

  private:
    static AppView *instanceView;
    static AppController *instanceController;

  public:
    // constructor
    AppView(AppController *newAppController, AppModel *newAppModel);

    int start(int argc, char *argv[]);

    
    // setters
    void setInstance();
    void setWindowSize(int w, int h);    
    void setWindowTitle(char* title);

    virtual void display();
    virtual void reshape(int w, int h);
    virtual void timer(int extra);

    static void displayWrapper();
    static void reshapeWrapper(int w, int h);
    static void timerWrapper(int extra);
    static void menuWrapper(int item);
    static void mouseWrapper(int button, int state, int x, int y);
    static void keyboardWrapper(unsigned char key, int x, int y);

    // enum menu options
    enum MENU_TYPE { MENU_1, MENU_2, MENU_3, MENU_4 };
 
    // draw methods
    void drawText(float x, float y, const char *string);
    void drawAxis();
    void drawVisualisation();
    void drawAllText();
  
    
  private:
    // private objects
    AppController *appController;
    AppModel *appModel;
    Visualisation visualisation;
    Calendar calendar;

    // private variables
    int width, height;
    char* windowTitle;
    int frame;
    float pos_z;

    char buffer1[32];
    char buffer2[32];

    char* prototype_name;
    int name_size;
    int mode;
    
    // private methods
    void init();  
    void update();
    void updateText();
    void reset();  

  

};

#endif

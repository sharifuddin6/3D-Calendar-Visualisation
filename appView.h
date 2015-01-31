#ifndef APPVIEW_H
#define APPVIEW_H

#include <GL/glut.h>
#include <stdio.h>
#include <string.h>

#include "appModel.h"
#include "appController.h"
#include "visualisation.h"

class AppView {

  private:
    static AppView *instance; 

  public:
    // constructor
    AppView(AppController *newAppController, AppModel *newAppModel);

    // enum menu options
    enum MENU_TYPE { MENU_1, MENU_2, MENU_3, MENU_4 };

    int start(int argc, char *argv[]);

    // draw text method
    void drawText(float x, float y, const char *string);    

    // setters
    void setInstance();
    void setWindowSize(int w, int h);    
    void setWindowTitle(char* title);

    virtual void display();
    virtual void reshape(int w, int h);
    virtual void timer(int extra);
    virtual void menu(int item);
    virtual void mouse(int button, int state, int x, int y);

    static void displayWrapper();
    static void reshapeWrapper(int w, int h);
    static void timerWrapper(int extra);
    static void menuWrapper(int item);
    static void mouseWrapper(int button, int state, int x, int y);

    

  private:
    // private objects
    AppController *appController;
    AppModel *appModel;
    Visualisation visualisation;

    // private variables
    int width, height;
    char* windowTitle;
    int frame;
    float pos_z;

    char* prototype_name;
    int name_size;
    
    // private methods
    void init();  
    void reset();  
  

};

#endif

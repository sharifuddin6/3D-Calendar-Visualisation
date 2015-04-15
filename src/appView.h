#ifndef APPVIEW_H
#define APPVIEW_H

#include "appModel.h"
#include "appController.h"

#include "../include/tinyfiledialogs/tinyfiledialogs.h"
#include "helper/visualisation.h"
#include "helper/calendar.h"


class AppView {

  public:
    // constructor
    AppView(AppController *newAppController, AppModel *newAppModel, Visualisation *newVisualisation);

    // methods
    int start(int argc, char *argv[]);  // initialise and starts glut for graphics window
    void openfileDialogBox();    // dialog box for open file, parses data in appmodel
    
    // setters
    void setInstance();
    void setWindowSize(int w, int h);    
    void setWindowTitle(const char* title);

    // glut functions
    virtual void display();
    virtual void reshape(int w, int h);
    virtual void timer(int extra);

    static void displayWrapper();
    static void reshapeWrapper(int w, int h);
    static void timerWrapper(int extra);
    static void menuWrapper(int item);
    static void mouseWrapper(int button, int state, int x, int y);
    static void keyboardWrapper(unsigned char key, int x, int y);
    static void specialInputWrapper(int key, int x, int y);

    // enum menu options
    enum MENU_TYPE { MENU_1, MENU_2, MENU_3, MENU_4, MENU_5 };
 
    // draw methods
    void drawText(float x, float y, const char *string);
    void drawAxis();
    void drawVisualisation();
    void drawAllText();
  
    
  private:
    // private objects
    static AppView *instanceView;
    static AppController *instanceController;

    AppController *appController;
    AppModel *appModel;
    Visualisation *visualisation;
    Calendar calendar;

    // private variables
    int width, height;
    const char* windowTitle;
    int frame;
    float pos_x, pos_y, pos_z;
    float angle;

    char date_buffer1[32];
    char date_buffer2[32];
    char event_subject[32];
    char event_startdate[64];
    char event_enddate[64];
    char event_location[32];

    char* prototype_name;
    int name_size;
    int mode, selected;
    
    // private methods
    void init();
    void update();
    void updateText();
    void updateEventText();
    void reset();
  

};

#endif

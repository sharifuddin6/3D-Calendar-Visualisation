/*
 * The view class implementation for the visualisation software. 
 * Implementation code for rendering and other graphics related functions.
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


#include "appView.h"

#include <GL/freeglut.h>
#include <pthread.h>
#include <stdio.h>
using namespace std;


AppView::AppView(AppController *newAppController, AppModel *newAppModel, Visualisation *newVisualisation) {
  // initialise class objects
  appController = newAppController; 
  appModel = newAppModel;
  visualisation = newVisualisation;
  
  // initialise variables
  mode = appModel->getVisualisationMode();
  frame = 0;
  width = 800; height = 600;
  windowTitle = "3D Calendar Visualisation";
  prototype_name = visualisation->getPrototypeName();
  name_size = visualisation->getPrototypeNameLen();

  // update current date and text
  updateText();
  updateEventText();
}

// public methods
void AppView::init() {
  // enable depth, and culling
  glEnable (GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_NORMALIZE);
  glShadeModel(GL_SMOOTH);

  // initialise lighting
  glEnable(GL_LIGHT0);
  GLfloat ambientColor[] = {0.4f, 0.4f, 0.4f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
	
	GLfloat lightColor0[] = {0.6f, 0.6f, 0.6f, 1.0f};
	GLfloat lightPos0[] = {-0.5f, 0.5f, 1.0f, 0.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
  glEnable(GL_LIGHTING);

  // initialise fog
  GLuint fogMode[]= { GL_EXP, GL_EXP2, GL_LINEAR };   // Storage For Three Types Of Fog
  GLuint fogfilter= 1;                                // Which Fog To Use
  GLfloat fogColor[4]= {0.0f, 0.0f, 0.0f, 1.0f};      // Fog Color
  
  glFogi(GL_FOG_MODE, fogMode[fogfilter]);        // Fog Mode
  glFogfv(GL_FOG_COLOR, fogColor);                // Set Fog Color
  glFogf(GL_FOG_DENSITY, 0.25f);                  // How Dense Will The Fog Be
  glHint(GL_FOG_HINT, GL_DONT_CARE);              // Fog Hint Value
  glFogf(GL_FOG_START, 1.0f);                     // Fog Start Depth
  glFogf(GL_FOG_END, -200.0f);                    // Fog End Depth

  // alpha blending
  glEnable(GL_BLEND);                                //Enable alpha blending
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //Set the blend function

  // smoothing on lines
  glEnable(GL_LINE_SMOOTH);
  glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
  glEnable(GL_MULTISAMPLE);

  // initialise render  
  glClearColor(0.1, 0.1, 0.1, 1.0);
}

// glut functions
void AppView::display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  
  // get viewport dimensions, set perspective  
  GLint viewport[4];
  glGetIntegerv(GL_VIEWPORT, viewport);
  double aspect = (double)viewport[2] / (double)viewport[3];
  gluPerspective(45.0, aspect, 1.0, 100.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // update frame
  update();  

  // draw scene
  glPushMatrix();
    glTranslatef(0+pos_x, 0+pos_y, 0+pos_z);
    //drawAxis();
    drawVisualisation();    
  glPopMatrix();

  // draw text  
  drawAllText(); 

  if(appModel->getSwapBuffer()) {
    glutSwapBuffers();
  }
}

void AppView::reshape(int w, int h) {
  glViewport(0, 0, w, h);
  appModel->setWindowSize(w,h);
}

void AppView::timer(int extra) {
  glutPostRedisplay();
  glutTimerFunc(16, timerWrapper, 0);
}

// main glut operations for graphics window
int AppView::start(int argc, char *argv[]) {
  // initialise static object
  setInstance();
  pthread_getconcurrency();

  // init glut
  glutInit(&argc, argv);
  glutInitWindowSize(width, height);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE | GLUT_MULTISAMPLE);
  glutCreateWindow(windowTitle);

  glutDisplayFunc(displayWrapper);
  glutReshapeFunc(reshapeWrapper);
  glutTimerFunc(0, timerWrapper, 0);

  // Create a menu
  glutCreateMenu(menuWrapper);
 
  // Add menu items
  glutAddMenuEntry("Prototype 1", MENU_1);
  glutAddMenuEntry("Prototype 2", MENU_2);
  glutAddMenuEntry("Prototype 3", MENU_3);
  glutAddMenuEntry("Prototype 4", MENU_4);
  glutAddMenuEntry("Prototype 5", MENU_5);

  // Associate a mouse button with menu
  glutAttachMenu(GLUT_RIGHT_BUTTON); 

  // add keyboard/mouse listener
  glutMouseFunc(mouseWrapper);
  glutKeyboardFunc(keyboardWrapper);
  glutSpecialFunc(specialInputWrapper);
  
  init();
  glutMainLoop();

  return 0;
}

void AppView::setWindowSize(int w, int h) {
  width = w;
  height = h;
  appModel->setWindowSize(w,h);
}

void AppView::setWindowTitle(const char* title) {
  windowTitle = title;
}




// void method access via wrapper
AppView *AppView::instanceView = NULL;
AppController *AppView::instanceController = NULL;

void AppView::setInstance() {
  instanceView = this;
  instanceController = appController;
}

void AppView::displayWrapper() {
  instanceView->display();
}

void AppView::reshapeWrapper(int w, int h) {
  instanceView->reshape(w,h);
}

void AppView::timerWrapper(int extra) {
  instanceView->timer(extra);
}

void AppView::menuWrapper(int item) {
  instanceController->menu(item);
}

void AppView::mouseWrapper(int button, int state, int x, int y) {
  instanceController->mouse(button, state, x, y);
}

void AppView::keyboardWrapper(unsigned char key, int x, int y) {
  instanceController->keyboard(key, x, y);
}

void AppView::specialInputWrapper(int key, int x, int y) {
  instanceController->specialInput(key, x, y);
}

// draw methods: text, axis, visualisation
void AppView::drawText(float x, float y, const char *string) {
  const char *c;

  glMatrixMode(GL_PROJECTION) ;
  glPushMatrix() ; // save
  glLoadIdentity();// and clear
  glMatrixMode(GL_MODELVIEW) ;
  glPushMatrix() ;
  glLoadIdentity() ;
  
  gluOrtho2D(0.0f, 800.0f, 0.0f, 600.0f);
  glDisable(GL_DEPTH_TEST) ; // also disable the depth test so renders on top 
  glDisable(GL_LIGHTING);

  glColor3f(1.0f,1.0f,1.0f);
  glRasterPos2f(x, y);
  for (c=string; *c != '\0'; c++) {
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *c);
  }
  
  glEnable(GL_DEPTH_TEST) ; // Turn depth testing back on
  glEnable(GL_LIGHTING);

  glMatrixMode(GL_PROJECTION) ;
  glPopMatrix() ; // revert back to the matrix I had before.
  glMatrixMode(GL_MODELVIEW) ;
  glPopMatrix() ;
}

void AppView::drawAxis() {
  // axis for sense of orientation
  glBegin(GL_LINES); // vertical axis
    glColor3f(0,1,0);
    glVertex3f(0, 1000, -10);
    glVertex3f(0,-1000, -10);
  glEnd();
  
  glBegin(GL_LINES); // horizontal axis
    glColor3f(1,0,0);
    glVertex3f(1000, 0, -10);
    glVertex3f(-1000,0, -10);
  glEnd();
}

void AppView::drawVisualisation() {
  // draws current visualisation mode
  int new_mode = appModel->getVisualisationMode();
  // if mode changed update scene and text
  if(mode != new_mode) {
    mode = new_mode;
    visualisation->setPrototype(mode);    
    reset();
  } else {
    visualisation->setPrototype(mode);    
  }

  visualisation->render(frame); // render visualisation

  // if selected date changes, update text
  int new_selected = appModel->getSelectedDateIndex();
  if(selected != new_selected) {
    selected = new_selected;
    // update text
    updateEventText();
  }
}

void AppView::drawAllText() {
  //drawText(0, 0, "CALENDAR VISUALISATION PROTOTYPE");
  drawText(width*(0.5f)-name_size*(10*0.25), height-12, prototype_name);

  // display current date
  drawText(0, height-12, date_buffer1);
  drawText(0, height-24, date_buffer2);

  // display selected event information
  drawText(0, height-48, event_subject);
  drawText(0, height-60, event_startdate);
  drawText(0, height-72, event_enddate);
  drawText(0, height-84, event_location);
 
}

// private methods: init, update, reset
void AppView::update() {
  frame++;
  if(frame > 60) { frame = 0; }
  pos_x = appModel->getPosition_x();
  pos_y = appModel->getPosition_y();
  pos_z = appModel->getPosition_z();

  // rotation animation
  angle += 0.6f;
	if (angle > 360) {
		angle -= 360;
	}
  appModel->setRotationAngle(angle);
}

void AppView::updateText() {
  // get todays day in string format
  int weekday = calendar.getWeekDay();
  int day = calendar.getDay();
  int month = calendar.getMonth();
  int year = calendar.getYear();

  char *weekdayString = calendar.getDayToString(weekday);
  char *monthString = calendar.getMonthToString(month);
  char *timeString = calendar.getTimeToString();

  // store into buffer
  sprintf(date_buffer1, "%s, %s", weekdayString, timeString);
  sprintf(date_buffer2, "%d %s %d", day, monthString, year);
}

void AppView::updateEventText() {
  char* subject = visualisation->getEventSubject();
  char* startdate = visualisation->getEventStartDateTime();
  char* enddate = visualisation->getEventEndDateTime();
  char* location = visualisation->getEventLocation();

  // store into buffer
  sprintf(event_subject, "SUBJECT:%s", subject);
  sprintf(event_startdate, "START:%s", startdate);
  sprintf(event_enddate, "END:  %s", enddate);
  sprintf(event_location, "LOCATION:%s", location);
}

void AppView::reset() {
  prototype_name = visualisation->getPrototypeName();
  name_size = visualisation->getPrototypeNameLen();
  pos_z = 0;
  appModel->setPosition_z(pos_z);
  updateText();
}


// dialog box for open file, returns filepath
void AppView::openfileDialogBox() {
  // parameters for tiny file dialogs [by Guillaume Vareille]
  const char *title = "Open Calendar data file";
  const char *defaultPath = "data";
  const char *filePath; 
  int const numOfFilters = 2; 
  char const *fileFilters[numOfFilters] = {"*.csv", "*.ics"}; // accepted file formats
  filePath = tinyfd_openFileDialog(title, defaultPath, numOfFilters, fileFilters, 0);
  
  if(filePath != NULL) {
    printf("filepath:%s\n", filePath);
    // determine file type; either csv or ics
    const char *suffix = ".csv";
    bool isCSV = appModel->has_suffix(filePath, suffix);

    // use correct parser
    if(isCSV) {
      printf("Parsing CSV file...\n");
      appModel->parseCSV(filePath); // PARSE CSV FORMAT
      printf("Parsing complete...\n");
    } else {
      printf("Parsing ICS file...\n");
      appModel->parseICS(filePath); // PARSE ICS FORMAT
      printf("Parsing complete...\n");
    }

  } else {
    printf("No input data supplied...\n");
  }
}


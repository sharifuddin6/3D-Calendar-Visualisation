#include "appView.h"
#include <stdio.h>

AppView::AppView(AppController *newAppController, AppModel *newAppModel) {
  // init variables
  appController = newAppController; 
  appModel = newAppModel;
  
  frame = 0;
  width = 800; height = 600;
  windowTitle = "3D Calendar Visualisation";
  prototype_name = "Prototype 1: Flat Perspective view";
  name_size = strlen(prototype_name);

  // assign a default value
  MENU_TYPE show = MENU_1;
  
  // get current date into memory
  update();

  calendar.totalDaysInMonth(2,2015);
  calendar.totalDaysInMonth(2,2016);
  calendar.totalDaysInMonth(3,2015);
  calendar.totalDaysInMonth(3,2016);
  calendar.totalDaysInMonth(4,2015);
//  calendar.isLeapYear(2016);

}

void AppView::init() {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_COLOR_MATERIAL);

  // initialise fog
  GLuint filter;                      // Which Filter To Use
  GLuint fogMode[]= { GL_EXP, GL_EXP2, GL_LINEAR };   // Storage For Three Types Of Fog
  GLuint fogfilter= 0;                    // Which Fog To Use
  GLfloat fogColor[4]= {0.0f, 0.0f, 0.0f, 1.0f};      // Fog Color
  
  glFogi(GL_FOG_MODE, fogMode[fogfilter]);        // Fog Mode
  glFogfv(GL_FOG_COLOR, fogColor);            // Set Fog Color
  glFogf(GL_FOG_DENSITY, 0.30f);              // How Dense Will The Fog Be
  glHint(GL_FOG_HINT, GL_DONT_CARE);          // Fog Hint Value
  glFogf(GL_FOG_START, -10.0f);             // Fog Start Depth
  glFogf(GL_FOG_END, -5.0f);               // Fog End Depth
  glEnable(GL_FOG);                   // Enables GL_FOG

}

void AppView::display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  GLint viewport[4];
  glGetIntegerv(GL_VIEWPORT, viewport);
  double aspect = (double)viewport[2] / (double)viewport[3];
  gluPerspective(60, aspect, 1, 100);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // update frame
  frame++;

  // move back a bit
  glTranslatef(0, 0, 0+pos_z);

  // draw objects
  visualisation.draw(frame);
  
  // vertical axis
  glBegin(GL_LINES);
    glColor3f(0,1,0);
    glVertex3f(0, 1000, -10);
    glVertex3f(0,-1000, -10);
  glEnd();
  // horizontal axis
  glBegin(GL_LINES);
    glColor3f(1,0,0);
    glVertex3f(1000, 0, -10);
    glVertex3f(-1000,0, -10);
  glEnd();


  // draw text
  drawText(0, 0, "CALENDAR VISUALISATION PROTOTYPE");
  drawText(width*(0.5f)-name_size*(10*0.5), height-12, prototype_name);

  // display current date
  update();
  drawText(0, height-12, buffer1);
  drawText(0, height-24, buffer2);

  glutSwapBuffers();
}

void AppView::reshape(int w, int h) {
  glViewport(0, 0, w, h);
}

void AppView::timer(int extra) {
  glutPostRedisplay();
  glutTimerFunc(16, timerWrapper, 0);
}

void AppView::menu(int item) {
  switch (item) {
    case MENU_1:
      visualisation.setPrototype(1);
      prototype_name = "Prototype 1: Flat Perspective view";
      reset();
      break;
    case MENU_2:
      visualisation.setPrototype(2);
      prototype_name = "Prototype 2: Time Tunnel view";
      reset();
      break;
    case MENU_3:
      visualisation.setPrototype(3);
      prototype_name = "Prototype 3: 3D Lexis Pencil";
      reset();
      break;
    case MENU_4:
      visualisation.setPrototype(4);
      prototype_name = "Prototype 4: 3D Fibonacci Spiral";
      reset();
      break;
    default:
      break;
   }

  glutPostRedisplay();
  return;
}

void AppView::mouse(int button, int state, int x, int y) {
  // Wheel reports as button 3(scroll up) and button 4(scroll down)
  if ((button == 3) || (button == 4)) // It's a wheel event
  {
    // Each wheel event reports like a button click, GLUT_DOWN then GLUT_UP
    if (state == GLUT_UP) return; // Disregard redundant GLUT_UP events
     
    // scroll wheel actions
    if(button == 3) { // scroll up
      pos_z += 0.25f;
    } else {          // scroll down
      pos_z -= 0.25f;
    }
    glutSwapBuffers();

  } else {  // normal button event
    printf("Button %s At %d %d\n", (state == GLUT_DOWN) ? "Down" : "Up", x, y);
  }
}

// void method access via wrapper
AppView *AppView::instance = NULL;

void AppView::displayWrapper() {
  instance->display();
}

void AppView::reshapeWrapper(int w, int h) {
  instance->reshape(w,h);
}

void AppView::timerWrapper(int extra) {
  instance->timer(extra);
}

void AppView::menuWrapper(int item) {
  instance->menu(item);
}

void AppView::mouseWrapper(int button, int state, int x, int y) {
  instance->mouse(button, state, x, y);
}

void AppView::setInstance() {
  instance = this;
}

// public methods
int AppView::start(int argc, char *argv[]) {
  
  setInstance();

  // init glut
  glutInit(&argc, argv);
  glutInitWindowSize(width, height);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
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

  // Associate a mouse button with menu
  glutAttachMenu(GLUT_RIGHT_BUTTON); 

  // add mouse listener
  glutMouseFunc(mouseWrapper); 
  
  init();
  glutMainLoop();

  return 0;
}

void AppView::drawText(float x, float y, const char *string) {
  const char *c;

  glMatrixMode( GL_PROJECTION ) ;
  glPushMatrix() ; // save
  glLoadIdentity();// and clear
  glMatrixMode( GL_MODELVIEW ) ;
  glPushMatrix() ;
  glLoadIdentity() ;
  
  gluOrtho2D (0.0f, 800.0f, 0.0f, 600.0f);
  glDisable( GL_DEPTH_TEST ) ; // also disable the depth test so renders on top

  glColor3f(1.0f,1.0f,1.0f);
  glRasterPos2f(x, y);
  for (c=string; *c != '\0'; c++) {
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *c);
  }
  
  glEnable( GL_DEPTH_TEST ) ; // Turn depth testing back on

  glMatrixMode( GL_PROJECTION ) ;
  glPopMatrix() ; // revert back to the matrix I had before.
  glMatrixMode( GL_MODELVIEW ) ;
  glPopMatrix() ;
  
}

void AppView::setWindowSize(int w, int h) {
  width = w;
  height = h;
}

void AppView::setWindowTitle(char* title) {
  windowTitle = title;
}

void AppView::reset() {
  name_size = strlen(prototype_name);
  pos_z = 0;
}

void AppView::update() {
  // get todays day in string format
  int weekday = calendar.getWeekDay();
  int day = calendar.getDay();
  int month = calendar.getMonth();
  int year = calendar.getYear();

  char *weekdayString = calendar.getDayToString(weekday);
  char *monthString = calendar.getMonthToString(month);

  // store into buffer
  sprintf(buffer1, "%s, %s", weekdayString, calendar.getTimeToString());
  sprintf(buffer2, "%d %s %d", day, monthString, year);
}

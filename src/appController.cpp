/*
 * The controller class implementation for the visualisation sofware. 
 * Implementation for handling various mouse and keyboard actions
 * as well as handling right-click context menu.
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

#include "appController.h"


// constructor
AppController::AppController(AppModel *newAppModel) { 
  appModel = newAppModel;
}

// handle menu selection
void AppController::menu(int item) {
  switch (item) {
    case MENU_1:
      appModel->setVisualisationMode(1);
      break;
    case MENU_2:
      appModel->setVisualisationMode(2);
      break;
    case MENU_3:
      appModel->setVisualisationMode(3);
      break;
    case MENU_4:
      appModel->setVisualisationMode(4);
      break;
    case MENU_5:
      appModel->setVisualisationMode(5);
      break;
    default:
      break;
   }
  glutPostRedisplay();
  return;
}

// handle mouse input
void AppController::mouse(int button, int state, int x, int y) {
  if ((button == 3) || (button == 4)) { // mouse wheel event, scroll up and down
    // Each wheel event reports like a button click, GLUT_DOWN then GLUT_UP
    if (state == GLUT_UP) return; // Disregard redundant GLUT_UP events
    // scroll wheel actions
    if(button == 3) { // scroll up
      pos_z = appModel->getPosition_z() +0.25f;
      appModel->setPosition_z(pos_z);
    } else {          // scroll down
      pos_z = appModel->getPosition_z() -0.25f;
      appModel->setPosition_z(pos_z);
    }
    glutSwapBuffers();

  } else {  // click event
    //printf("Button %s At %d %d\n", (state == GLUT_DOWN) ? "Down" : "Up", x, y);
    if(state==GLUT_UP) {
      appModel->setPickingMode(true);
      int winHeight = appModel->getWindowHeight();
      appModel->setPickingLocation(x,winHeight-y);
    }
  }
}

// handle keyboard input
void AppController::keyboard(unsigned char key, int x, int y) {
  switch(key) {
    case 'w':
      pos_z = appModel->getPosition_z() +0.25f;
      appModel->setPosition_z(pos_z);
      break;
    case 's':
      pos_z = appModel->getPosition_z() -0.25f;
      appModel->setPosition_z(pos_z);
      break;
    case 'a':
      pos_x = appModel->getPosition_x() +0.25f;
      appModel->setPosition_x(pos_x);      
      break;
    case 'd':
      pos_x = appModel->getPosition_x() -0.25f;
      appModel->setPosition_x(pos_x);      
      break;
    case 'q':
      pos_y = appModel->getPosition_y() +0.25f;
      appModel->setPosition_y(pos_y);      
      break;
    case 'e':
      pos_y = appModel->getPosition_y() -0.25f;
      appModel->setPosition_y(pos_y);      
      break;
    case 'r':
      appModel->setPosition_x(0.0);
      appModel->setPosition_y(0.0);
      appModel->setPosition_z(0.0);
      change = appModel->getSelectedDateIndex() *-1;
      current = appModel->getCurrentDateIndex();
      //printf("difference: %d %d\n", change, current);    
      appModel->setSelectedDateIndex(change+current);
      appModel->setSelectedWeek(1);
      break;   
    case 27: // Escape key
      printf("See you later..\n");  
      exit(0);    
      break;
    default:
      break;
  }
}

// handle keyboard special key input
void AppController::specialInput(int key, int x, int y) {
  switch(key) {
    case GLUT_KEY_UP:
      appModel->setSelectedDateIndex(-1);
      break;
    case GLUT_KEY_DOWN:
      appModel->setSelectedDateIndex(+1);
      break;
    case GLUT_KEY_LEFT:
      break;
    case GLUT_KEY_RIGHT:
      break;
    default:
      break;
  }
}

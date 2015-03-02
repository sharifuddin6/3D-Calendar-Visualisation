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

//  prototype_name = visualisation.getPrototypeName();
  glutPostRedisplay();
  return;
}

// handle mouse input
void AppController::mouse(int button, int state, int x, int y) {
  // Wheel reports as button 3(scroll up) and button 4(scroll down)
  if ((button == 3) || (button == 4)) // It's a wheel event
  {
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
      break;   
    case 'f':
      if(appModel->getFog()) {
        glDisable(GL_FOG);
        appModel->setFog(false);
      } else {
        glEnable(GL_FOG);
        appModel->setFog(true);
      }
    case 'p':
      if(appModel->getPickingModeDebug()) {
        appModel->setPickingModeDebug(false);
      } else {
        appModel->setPickingModeDebug(true);
      }

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
      appModel->setSelectedBuff(-1.0);
      appModel->setSelectedDateIndex(-1);
      break;
    case GLUT_KEY_DOWN:
      appModel->setSelectedBuff(+1.0);
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

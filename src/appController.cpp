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
    printf("Button %s At %d %d\n", (state == GLUT_DOWN) ? "Down" : "Up", x, y);
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
      printf("A PRESSED\n");
      break;
    case 'd':
      printf("D PRESSED\n");
      break;
    default:
      break;
  }
}



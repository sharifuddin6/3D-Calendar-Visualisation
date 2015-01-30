#include <GL/glut.h>

#include "appModel.h"
#include "appView.h"
#include "appController.h"

int main(int argc, char **argv) {
  // MVC architecture
  AppModel *appModel;
  AppController *appController = new AppController(appModel);
  AppView *appView = new AppView(appController, appModel);

  // initialise window
  appView->setWindowSize(800,600);
  appView->setWindowTitle("[Prototype] 3D Calendar Visualisation");
  appView->start(argc, argv);

  return 0;
}


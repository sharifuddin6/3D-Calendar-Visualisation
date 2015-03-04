#include "appModel.h"
#include "appView.h"
#include "appController.h"
#include "helper/visualisation.h"

#include <GL/glut.h>


int main(int argc, char **argv) {

  // MVC architecture
  AppModel *appModel = new AppModel();

  Visualisation *visualisation = new Visualisation(appModel);
  AppController *appController = new AppController(appModel);
  AppView *appView = new AppView(appController, appModel, visualisation);

  // open file dialog and read selected calendar data file
  appView->openfileDialogBox();
  visualisation->init();
  
  // initialise window
  const char *title = "3D Calendar Visualisation";
  appView->setWindowSize(800,600);
  appView->setWindowTitle(title);
  appView->start(argc, argv);

  return 0;
}

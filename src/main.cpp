#include "appModel.h"
#include "appView.h"
#include "appController.h"
#include "helper/assetloader.h"

#include <GL/glut.h>


int main(int argc, char **argv) {
  // init assetloader
  AssetLoader *assetLoader;

  // MVC architecture
  AppModel *appModel = new AppModel();
  AppController *appController = new AppController(appModel);
  AppView *appView = new AppView(appController, appModel);

  // open file dialog and read selected calendar data file
  appView->openfileDialogBox();
  
  // initialise window
  appView->setWindowSize(800,600);
  appView->setWindowTitle("[Prototype] 3D Calendar Visualisation");
  appView->start(argc, argv);

  return 0;
}

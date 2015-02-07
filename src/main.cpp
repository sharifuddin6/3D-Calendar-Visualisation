#include <GL/glut.h>

#include "appModel.h"
#include "appView.h"
#include "appController.h"

#include "helper/assetloader.h"
#include "../lib/tinyfiledialogs/tinyfiledialogs.h"

int main(int argc, char **argv) {

  // init assetloader
  AssetLoader *assetLoader;

  // MVC architecture
  AppModel *appModel = new AppModel();
  AppController *appController = new AppController(appModel);
  AppView *appView = new AppView(appController, appModel);

  // open file dialog and read selected calendar data file
  const char *title = "Open Calendar file [iCal/CSV]";
  const char *defaultPath = "data";
  const char *filePath;
  int const numOfFilters = 2; 
  char const *fileFilters[numOfFilters] = {"*.csv", "*.ics"}; // accepted file formats
  filePath = tinyfd_openFileDialog(title, defaultPath, numOfFilters, fileFilters, 0);
  appModel->readFile(filePath);

  // initialise window
  appView->setWindowSize(800,600);
  appView->setWindowTitle("[Prototype] 3D Calendar Visualisation");
  appView->start(argc, argv);

  return 0;
}


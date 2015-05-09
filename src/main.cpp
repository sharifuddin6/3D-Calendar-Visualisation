/*
 * 3D Calendar Visualisation software main source file with an 
 * implementation of the software in a ModelViewController architecture.
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

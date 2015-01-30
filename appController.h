#ifndef APPCONTROLLER_H
#define APPCONTROLLER_H

#include "appModel.h"

class AppController {

  public:
    // constructor
    AppController(AppModel *newAppModel);

  private:
    AppModel *appModel;

};

#endif

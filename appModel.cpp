#include "appModel.h"

AppModel::AppModel() {
  position_z = 0.0;
  mode = 1;
}

// getter
float AppModel::getPosition_z() {
  return position_z;
}

int AppModel::getVisualisationMode() {
  return mode;
}

// setter
void AppModel::setPosition_z(float new_z) {
  position_z = new_z;
}

void AppModel::setVisualisationMode(int new_mode) {
  mode = new_mode;
}

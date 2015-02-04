#ifndef APPMODEL_H
#define APPMODEL_H

class AppModel {

  public:
    // constructor
    AppModel();

    // getters
    float getPosition_z();
    int getVisualisationMode();

    // setters
    void setPosition_z(float new_z);
    void setVisualisationMode(int new_mode);

  private:
    float position_z;         // position z is the camera position
    int mode;   // visualisation mode is the chosen mode


};

#endif

#ifndef APPMODEL_H
#define APPMODEL_H

#include "helper/event.h"
#include <string>


class AppModel {

  public:
    // constructor
    AppModel();

    // methods
    void parseCSV(const char* filePath);
    void parseICS(const char* filePath);
    bool has_suffix(const char *str, const char *suffix); // used to determine file type

    // getters
    float getPosition_x();
    float getPosition_y();
    float getPosition_z();
    int getVisualisationMode();
    bool getFog();

    // setters
    void setPosition_x(float new_x);
    void setPosition_y(float new_y);
    void setPosition_z(float new_z);
    void setVisualisationMode(int new_mode);
    void setFog(bool value);

  private:
    // variables
    float position_x, position_y, position_z;       // the camera position
    int mode;               // visualisation mode is the chosen mode
    bool fog_enabled;

    // methods
    void trim(std::string &str);   // used to trim extra spaces
    

};

#endif

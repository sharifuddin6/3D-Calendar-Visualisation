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
    float getPosition_z();
    int getVisualisationMode();

    // setters
    void setPosition_z(float new_z);
    void setVisualisationMode(int new_mode);

  private:
    // variables
    float position_z;       // position z is the camera position
    int mode;               // visualisation mode is the chosen mode

    // methods
    void trim(std::string &str);   // used to trim extra spaces
    

};

#endif

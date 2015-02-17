#ifndef APPMODEL_H
#define APPMODEL_H

#include "helper/event.h"
#include <string>
#include <vector>
using namespace std;

class AppModel {

  public:
    // constructor
    AppModel();

    // methods
    void parseCSV(const char* filePath);
    void parseICS(const char* filePath);
    bool has_suffix(const char *word, const char *suffix); // used to determine file type
    bool has_prefix(const char *word, const char *prefix);

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
    float position_x, position_y, position_z;   // the camera position
    int mode;                                   // visualisation mode is the chosen mode
    bool fog_enabled;

    vector<Event> event_array;  // array holds all events from parsed data file

    // methods
    void trim(std::string &str);   // used to trim extra spaces
    

};

#endif

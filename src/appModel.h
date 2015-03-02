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
    int getWindowWidth();
    int getWindowHeight();
    float getPosition_x();
    float getPosition_y();
    float getPosition_z();
    float getSelected();
    float getSelectedBuff();
    int getSelectedDateIndex();

    int getVisualisationMode();
    bool getFog();
    bool getPickingMode();
    bool getPickingModeDebug();
    int getPicked_x();
    int getPicked_y();

    bool getSwapBuffer();

    // setters
    void setWindowSize(int new_width, int new_height);
    void setPosition_x(float new_x);
    void setPosition_y(float new_y);
    void setPosition_z(float new_z);
    void setSelected(float new_selected);
    void setSelectedBuff(float new_selected_buff);
    void emptySelectedBuff();
    void setSelectedDateIndex(int new_selected_date);

    void setVisualisationMode(int new_mode);
    void setFog(bool value);
    void setPickingMode(bool value);
    void setPickingModeDebug(bool value);
    void setPickingLocation(int x, int y);

    void setSwapBuffer(bool value);

  private:
    // variables
    int width, height;
    float position_x, position_y, position_z;   // the camera position
 
    float selected;
    float selected_buff;
    int selected_date_index;

    int mode;                                   // visualisation mode is the chosen mode
    bool fog_enabled;
    bool pickingMode_enabled;
    bool pickingModeDebug_enabled;
    int clicked_x, clicked_y;
    bool swapBuffer;

    vector<Event> event_array;  // array holds all events from parsed data file

    // methods
    void trim(std::string &str);   // used to trim extra spaces
    

};

#endif

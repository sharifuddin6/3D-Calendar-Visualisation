#ifndef APPMODEL_H
#define APPMODEL_H

class AppModel {

  public:
    // constructor
    AppModel();

    // methods
    void readFile(const char *newFilePath);

    // getters
    float getPosition_z();
    int getVisualisationMode();

    // setters
    void setPosition_z(float new_z);
    void setVisualisationMode(int new_mode);

  private:
    // variables
    const char *filePath;   // filepath of calendar data
    float position_z;       // position z is the camera position
    int mode;               // visualisation mode is the chosen mode

    // methods
    bool has_suffix(const char *str, const char *suffix);

};

#endif

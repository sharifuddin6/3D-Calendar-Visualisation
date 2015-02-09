#include "appModel.h"

#include <stdio.h>
#include <fstream>
#include <sstream>
using namespace std;

// constructor
AppModel::AppModel() {
  position_x = 0.0;
  position_y = 0.0;
  position_z = 0.0;
  mode = 1;
}

// methods
void AppModel::parseCSV(const char* filePath) {
  // read data from file path
  ifstream infile;
  infile.open(filePath);
  char line[256];
  
  while (infile) {
    infile.getline(line, 256);
    //if(infile) printf("%s\n", line); // output lines from file to console
    // parse each line from data
    istringstream ss(line);
    while (!ss.eof()) {
      string out;               // here's a nice, empty string
      getline(ss, out, ',');    // try to read the next field into it
      trim(out);                // trim leaing/trailing/multiple spacing
      //printf("OUT: %s\n", out.c_str());  // output parsed data from line to console
    }
  }
  infile.close();

}

void AppModel::parseICS(const char* filePath) {
  // read data from file path
  ifstream infile;
  infile.open(filePath);
  char line[256];
  
  while (infile) {
    infile.getline(line, 256);
    if(infile) printf("%s\n", line);
    // parse each line from data

  }
  infile.close();

}

void AppModel::trim(string &str) {
  int size=str.size();
  // remove space at the end   
  if (str [size-1] == ' ')
    str.erase(str.end()-1);
  // remove space at the begin
  if (str [0] == ' ')
    str.erase(str.begin());

  //remove spaces which follow another space
  size = 0;
  for (unsigned int i=0; i<str.size(); ++i) {
    if ( (str[i] != ' ') || (str[i] == ' ' && str[i+1] != ' ' )) {
      str [size] = str [i];
      ++size;
    }
  }
  str.resize(size);
}

// returns boolean value, used to determine file type if path ends in suffix
bool AppModel::has_suffix(const char *str, const char *suffix) {
  string path = string(str);
  string suff = string(suffix);

  bool value = false;
  int suff_size = suff.length();
  int str_size = path.length();  
  bool check_1 = false;
  bool check_2 = false;

  // minimal comparison, file name must be atleast the size of its extension name
  if(str_size >= suff_size) { check_1 = true; }  
  // comparison of ending substring, if correct file type
  string substring_1 = path.substr(str_size-suff_size, suff_size);
  string substring_2 = suff;
  if(substring_2.compare(substring_1) == 0) {
    //printf("%s, %s, is equal\n", substring_1.c_str(), substring_2.c_str());
    check_2 = true;
  }

  // both cases must be true
  if(check_1 && check_2) {
    value = true;
  }
  //printf("%s==%s? %s\n", str, suffix, value?"true":"false");
  return value;
}




// getter
float AppModel::getPosition_x() {
  return position_x;
}

float AppModel::getPosition_y() {
  return position_y;
}

float AppModel::getPosition_z() {
  return position_z;
}

int AppModel::getVisualisationMode() {
  return mode;
}

bool AppModel::getFog() {
  return fog_enabled;
}

// setter
void AppModel::setPosition_x(float new_x) {
  position_x = new_x;
}

void AppModel::setPosition_y(float new_y) {
  position_y = new_y;
}

void AppModel::setPosition_z(float new_z) {
  position_z = new_z;
}

void AppModel::setVisualisationMode(int new_mode) {
  mode = new_mode;
}

void AppModel::setFog(bool value) {
  fog_enabled = value;
}



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

  bool event_state = false;
  string line;
  
  while(getline(infile, line)) {

    if(infile) { 
      // search for begin event
      if(has_prefix(line.c_str(), "BEGIN:VEVENT")) {
        Event event;
        event_array.push_back(event);
        event_state = true;
      } 
      // search for end event        
      if (has_prefix(line.c_str(), "END:VEVENT")) {
        // add event to array
        event_state = false;
      }
      // parse data from event
      if(event_state) {
        // if event state add lines to event_buffer
        int index = event_array.size()-1;

        if(has_prefix(line.c_str(), "DTSTART:")) {
          const char* startDateTime = line.substr(8).c_str();
          event_array[index].setStartDateTime(startDateTime);
        } else if(has_prefix(line.c_str(), "DTEND:")) {
          const char* endDateTime = line.substr(8).c_str();
          event_array[index].setEndDateTime(endDateTime);
        } else if(has_prefix(line.c_str(), "SUMMARY:")) {
          const char* subject = line.substr(8).c_str();
          event_array[index].setSubject(subject);
        } else if(has_prefix(line.c_str(), "DESCRIPTION:")) {
          const char* description = line.substr(12).c_str();
          event_array[index].setDescription(description);
        } else if(has_prefix(line.c_str(), "LOCATION:")) {
          const char* location = line.substr(9).c_str();
          event_array[index].setLocation(location);
        }

      }
    }
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
bool AppModel::has_suffix(const char *word, const char *suffix) {
  string str = string(word);
  string suff = string(suffix);

  bool value = false;
  int suff_size = suff.length();
  int str_size = str.length();  
  bool check_1 = false;
  bool check_2 = false;

  // minimal comparison, string must be atleast the size of its suffix
  if(str_size >= suff_size) { check_1 = true; }  
  // comparison of ending substring, if correct file type
  string substring_1 = str.substr(str_size-suff_size, suff_size);
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

bool AppModel::has_prefix(const char *word, const char *prefix) {
  string str = string(word);
  string pref = string(prefix);
  int pref_size = pref.length();
  int str_size = str.length();  

  bool value = false;
  bool check_1 = false;
  bool check_2 = false;

  // minimal comparison, string must be atleast the size of its prefix
  if(str_size >= pref_size) { check_1 = true; } 

  // comparison of ending substring, if correct file type
  string substring_1 = str.substr(0, pref_size);
  string substring_2 = pref;
  if(substring_2.compare(substring_1) == 0) {
    //printf("%s, %s, is equal\n", substring_1.c_str(), substring_2.c_str());
    check_2 = true;
  }

  // both cases must be true
  if(check_1 && check_2) {
    value = true;
  }
  //printf("%s==%s? %s\n", str.c_str(), prefix, value?"true":"false");
  
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



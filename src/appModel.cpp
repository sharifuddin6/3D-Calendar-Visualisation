/*
 * The model class implementation for the visualisation software. 
 * Implementation for handling the methods and accessors on
 * the data model.
 *
 * Copyright (c) 2015 Sharif UDDIN
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR
 * ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */


#include "appModel.h"

#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string.h>
using namespace std;


// constructor
AppModel::AppModel() {
  position_x = 0.0;
  position_y = 0.0;
  position_z = 0.0;
  selected = 0.0;
  selected_buff = 0.0;
  selected_week = 1;
  selected_date_index = 0;
  mode = 1;

  pickingMode_enabled = false;
  swapBuffer = true;
}

// methods
void AppModel::parseCSV(const char* filePath) {
  // read data from file path
  ifstream infile;
  infile.open(filePath);
  char line[256];
  
  while (infile) {
    infile.getline(line, 256);
    if(infile) {
      // parse each line
      const char* text = line;
      istringstream ss(text);
      vector<string> attributes;

      // store each attributes for this event
      while (!ss.eof()) {
        string out;               
        getline( ss, out, ',' );  
        trim(out);
        attributes.push_back(out);
      }

      // create event object and store in array
      Event event;
      int icon, importance;
      stringstream strIcon, strImportance;      
      event.setSubject(attributes.at(0).c_str());
      event.setStartDate(attributes.at(1).c_str());
      event.setStartTime(attributes.at(2).c_str());
      event.setEndDate(attributes.at(3).c_str());
      event.setEndTime(attributes.at(4).c_str());
      event.setDescription(attributes.at(5).c_str());
      event.setLocation(attributes.at(6).c_str());
      // extract and convert integer values
      const char* icon_val = attributes.at(7).c_str();
      strIcon << icon_val;
      strIcon >> icon; 
      const char* impo_val = attributes.at(8).c_str();
      strImportance << impo_val;
      strImportance >> importance;

      event.setIcon(icon);
      event.setImportance(importance);
      event_array.push_back(event);
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
        int icon, importance;
        stringstream strIcon, strImportance;      

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
        } else if(has_prefix(line.c_str(), "ICON:")) {
          const char* icon_val = line.substr(5).c_str();
          strIcon << icon_val;
          strIcon >> icon; 
          event_array[index].setIcon(icon);
        } else if(has_prefix(line.c_str(), "IMPORTANCE:")) {
          const char* impo_val = line.substr(11).c_str();
          strImportance << impo_val;
          strImportance >> importance;
          event_array[index].setImportance(importance);
        }
      }
    }
  }
  infile.close();
}

void AppModel::trim(string &str) {
  // remove space at the end of line  
  int size=str.size();
  if (str [size-1] == ' ')
    str.erase(str.end()-1);
  // remove space at the begin of line
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
int AppModel::getWindowWidth() {
  return width;
}

int AppModel::getWindowHeight() {
  return height;
}

float AppModel::getPosition_x() {
  return position_x;
}

float AppModel::getPosition_y() {
  return position_y;
}

float AppModel::getPosition_z() {
  return position_z;
}

float AppModel::getRotationAngle() {
  return angle;
}

float AppModel::getSelected() {
  return selected;
}

float AppModel::getSelectedBuff() {
  return selected_buff;
}

int AppModel::getSelectedWeek() {
  return selected_week;
}

int AppModel::getSelectedDateIndex() {
  return selected_date_index;
}

int AppModel::getCurrentDateIndex() {
  return current_date_index;
}

// return event details
int AppModel::getEventIcon(int index) { 
  return event_array.at(index).getIcon();
}

int AppModel::getEventImportance(int index) {
  return event_array.at(index).getImportance();
}

char* AppModel::getEventSubject(int index) {
  return event_array.at(index).getSubject();
}

char* AppModel::getEventStartDate(int index) {
  return event_array.at(index).getStartDate();
}

char* AppModel::getEventStartTime(int index) {
  return event_array.at(index).getStartTime();
}

char* AppModel::getEventEndDate(int index) {
  return event_array.at(index).getEndDate();
}

char* AppModel::getEventEndTime(int index) {
  return event_array.at(index).getEndTime();
}

char* AppModel::getEventLocation(int index) {
  return event_array.at(index).getLocation();
}


int AppModel::getVisualisationMode() {
  return mode;
}

bool AppModel::getPickingMode() {
  return pickingMode_enabled;
}

int AppModel::getPicked_x() {
  return clicked_x;
}

int AppModel::getPicked_y() {
  return clicked_y;
}

bool AppModel::getSwapBuffer() {
  return swapBuffer;
}

// setter
void AppModel::setWindowSize(int new_width, int new_height) {
  width = new_width;
  height = new_height;
}

void AppModel::setPosition_x(float new_x) {
  position_x = new_x;
}

void AppModel::setPosition_y(float new_y) {
  position_y = new_y;
}

void AppModel::setPosition_z(float new_z) {
  position_z = new_z;
}

void AppModel::setRotationAngle(float new_angle) {
  angle = new_angle;
}

void AppModel::setSelected(float new_selected) {
  selected = new_selected;
}

void AppModel::setSelectedBuff(float new_selected_buff) {
  selected_buff += new_selected_buff;
}

void AppModel::emptySelectedBuff() {
  selected_buff = 0.0;
}

void AppModel::setSelectedDateIndex(int new_selected_date) {
  selected_date_index += new_selected_date;
  setSelectedBuff((double) new_selected_date);
}

void AppModel::setCurrentDateIndex(int new_current_date) {
  current_date_index = new_current_date;
  setSelectedDateIndex(new_current_date);
}

void AppModel::setSelectedWeek(int new_week) {
  selected_week = new_week;
}

void AppModel::setVisualisationMode(int new_mode) {
  mode = new_mode;
}

void AppModel::setPickingMode(bool value) { 
  pickingMode_enabled = value;
}

void AppModel::setPickingLocation(int x, int y) {
  clicked_x = x;
  clicked_y = y;
}

void AppModel::setSwapBuffer(bool value) {
  swapBuffer = value;
}

int AppModel::compareDateEvent(int day, int month, int year) {
  int d, m, y;
  int index = -1;

  for(unsigned int i=0; i<event_array.size(); i++) {
    char* date = event_array.at(i).getStartDate();
    date[2] = ','; date[5] = ',';
    d = calendar.parseDay(date);
    m = calendar.parseMonth(date);
    y = calendar.parseYear(date)+2000;

    // matched case
    if(day==d && month==m && year==y) {
      //printf("[%d,%d,%d] == [%d,%d,%d]\n", day,month,year, d,m,y);
      index = i;
    }
  }
  return index;
}

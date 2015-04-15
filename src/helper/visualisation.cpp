#include "visualisation.h"
#include "../../include/drawtext/text3d.h"

#include <stdio.h>
#include <string.h>
#include <cmath>


Visualisation::Visualisation(AppModel *newAppModel) {
  appModel = newAppModel;
  mode = 1;
  prototype_name = new char[64];
  getPrototypeName();
}

void Visualisation::init() {
  initLoad();
  initDate();
}

void Visualisation::initDate() {
  // this week from monday
  int total_weeks = 20;
  int upper_limit = 7*total_weeks; // 6 weeks in front
  int week = 0;
  int weekday = calendar.getWeekDay();
    
  int offset = 1-weekday-7; // where monday starts from 1, since 0 is not the initial state
  weekday = 1;
  char date_buff[32];
  
  for(int i=0; i<upper_limit; i++) {
    // create struct day object
    sprintf(date_buff, "%s", calendar.getDate(offset));
    int day = calendar.parseDay(date_buff);
    int month = calendar.parseMonth(date_buff);
    int year = calendar.parseYear(date_buff);
    aDay aday;
    aday.week = week;
    aday.weekday = weekday;

    aday.day = day;
    aday.month = month;
    aday.year = year;

    // test date for event from event_array in model class    
    aday.event_id = appModel->compareDateEvent(day, month, year);
    if(aday.event_id > 0) {
      aday.event_icon = appModel->getEventIcon(aday.event_id);
      aday.event_importance = appModel->getEventImportance(aday.event_id);
      aday.event_subject = appModel->getEventSubject(aday.event_id);
      aday.event_startDate = appModel->getEventStartDate(aday.event_id);
      aday.event_startTime = appModel->getEventStartTime(aday.event_id);
      aday.event_endDate = appModel->getEventEndDate(aday.event_id);
      aday.event_endTime = appModel->getEventEndTime(aday.event_id);
      aday.event_location = appModel->getEventLocation(aday.event_id);
    }

    days.push_back(aday); // push back
    
    // create struct colour id object
    object_id unique_id;
    object_id_array.push_back(unique_id);

    // iterator
    offset++;
    weekday+=1;
    if((i+1)%7 == 0) { week++; weekday = 1; }
  }

  // set unique colour for each object in object_id_array
  for(unsigned int i=0; i<object_id_array.size(); i++) {
    object_id_array.at(i).set_index(i);
    //printf("Index: %d, [%d,%d,%d]\n", i, 
    //      object_id_array.at(i).r, object_id_array.at(i).g, object_id_array.at(i).b);
  }

  // fix offset from today for visualisation
  weekday = calendar.getWeekDay();
  //printf("weekday:%d\n", weekday);
  appModel->setCurrentDateIndex(-weekday+1.0-7.0);
}

void Visualisation::initLoad() {
  // load object
  objLoader = new ObjectLoader();

  objLoader->loadObject("data/model/radial_face.obj");
  objLoader->loadObject("data/model/radial_text.obj");
  objLoader->loadObject("data/model/radial_tile.obj");
  objLoader->loadObject("data/model/radial_level_1.obj");
  objLoader->loadObject("data/model/radial_level_2.obj");
  objLoader->loadObject("data/model/radial_level_3.obj");

  objLoader->loadObject("data/model/gift_box.obj");
  objLoader->loadObject("data/model/gift_wrap.obj");
  objLoader->loadObject("data/model/gift_knot.obj");

  objLoader->loadObject("data/model/memo_back.obj");
  objLoader->loadObject("data/model/memo_paper.obj");
  objLoader->loadObject("data/model/memo_text.obj");

  objLoader->loadObject("data/model/work_cover.obj");
  objLoader->loadObject("data/model/work_paper.obj");
  objLoader->loadObject("data/model/work_text.obj");

  objLoader->loadObject("data/model/holiday_stem.obj");
  objLoader->loadObject("data/model/holiday_shade_1.obj");
  objLoader->loadObject("data/model/holiday_shade_2.obj");

  objLoader->loadObject("data/model/meeting_shirt.obj");
  objLoader->loadObject("data/model/meeting_sleeve.obj");
  objLoader->loadObject("data/model/meeting_hand.obj");
}

void Visualisation::render(int frame) {

  smooth_selection(frame);

  switch(mode) {
    case 1:
      prototype_1();
      break;
    case 2:
      prototype_2();
      break;
    case 3:
      prototype_3();
      break;
    case 4:
      prototype_4();
      break;
    case 5:
      prototype_5();
      break;
    default:
      break;  
  } 

}

void Visualisation::drawDay(int weekday, int day) {
  // init 3dtext
  t3dInit();
  char *buff = new char[4];
  char *buff_day = new char[11];
  snprintf(buff, 4, "%d", day);
  snprintf(buff_day, 11, "%s", calendar.getDayToString(weekday));
  // day in number form
  glPushMatrix();
    glScalef(0.1, 1.0, 0.1);
    glTranslatef(0.0, 0.5, 0.0);
    drawText(buff);    
  glPopMatrix();

}

void Visualisation::drawDate(int weekday, int day) {
  // init 3dtext
  t3dInit();
  char *buff = new char[4];
  char *buff_day = new char[11];
  snprintf(buff, 4, "%d", day);
  snprintf(buff_day, 11, "%s", calendar.getDayToString(weekday));
  // day in number form
  glPushMatrix();
    if(!pickerMode && !pickerModeDebug) { glColor3f(0.8,0.2,0.2); }
    glScalef(0.1, 0.6, 0.1);
    glTranslatef(0.0, 0.5, 0.0);
    drawText(buff);    
  glPopMatrix();
  // weekday in string form
  glPushMatrix(); 
    if(!pickerMode && !pickerModeDebug) { glColor3f(0.8,0.2,0.2); }
    glScalef(0.15, 0.7, 0.2);
    glTranslatef(-10.0, 0.5, 0.0);
    drawText(buff_day);
  glPopMatrix();
}

void Visualisation::drawText(const char* text) {
  // parameters for draw t3ddraw text [by Bill Jacobs]
  float text_scale;
  text_scale = computeScale(text);
  glPushMatrix();
    glTranslatef(0.0, -0.4, 0.0);
    glScalef(2.0, 0.1, 2.0);
    glScalef(text_scale, text_scale, text_scale);
	  glRotatef(90.0, -1.0, 0.0, 0.0);
	  t3dDraw3D(text, 0.0, 0.0, 0.2);
	glPopMatrix();
}

// draw loaded objects
void Visualisation::draw_giftbox(float alpha) {
//  float angle = appModel->getRotationAngle();
  glPushMatrix();
    glScalef(0.4,0.4,0.4);
//    glRotatef(angle, 0.0, -1.0, 0.0);
    if(!pickerMode && !pickerModeDebug && !wire_mode) { glColor4f(0.5,0.9,0.5,alpha); }
    objLoader->renderObject(6);
    if(!pickerMode && !pickerModeDebug && !wire_mode) { glColor4f(1.0,0.6,0.3,alpha); }
    objLoader->renderObject(7);
    if(!pickerMode && !pickerModeDebug && !wire_mode) { glColor4f(1.0,0.3,0.3,alpha); }
    objLoader->renderObject(8);
  glPopMatrix();	
}

void Visualisation::draw_memo(float alpha) {
//  float angle = appModel->getRotationAngle();
  glPushMatrix();
    glScalef(1.0,1.0,1.0);
//    glRotatef(angle, 0.0, -1.0, 0.0);
    if(!pickerMode && !pickerModeDebug && !wire_mode) { glColor4f(1.0,1.0,0.7,alpha); }
    objLoader->renderObject(9);
    if(!pickerMode && !pickerModeDebug && !wire_mode) { glColor4f(1.0,1.0,0.7,alpha); }
    objLoader->renderObject(10);
    if(!pickerMode && !pickerModeDebug && !wire_mode) { glColor4f(1.0,1.0,0.7,alpha); }
    objLoader->renderObject(11);
  glPopMatrix();
}

void Visualisation::draw_work(float alpha) {
//  float angle = appModel->getRotationAngle();
  glPushMatrix();
    glScalef(0.6,0.6,0.6);
//    glRotatef(angle, 0.0, -1.0, 0.0);
    if(!pickerMode && !pickerModeDebug && !wire_mode) { glColor4f(0.5,0.5,0.9,alpha); }
    objLoader->renderObject(12);
    if(!pickerMode && !pickerModeDebug && !wire_mode) { glColor4f(1.0,1.0,0.7,alpha); }
    objLoader->renderObject(13);
    if(!pickerMode && !pickerModeDebug && !wire_mode) { glColor4f(1.0,1.0,0.7,alpha); }
    objLoader->renderObject(14);
  glPopMatrix();
}

void Visualisation::draw_holiday(float alpha) {
//  float angle = appModel->getRotationAngle();
  glPushMatrix();
    glScalef(1.0,1.0,1.0);
//    glRotatef(angle, 0.0, -1.0, 0.0);
    if(!pickerMode && !pickerModeDebug && !wire_mode) { glColor4f(1.0,1.0,0.7,alpha); }
    objLoader->renderObject(15);
    if(!pickerMode && !pickerModeDebug && !wire_mode) { glColor4f(0.5,0.9,0.5,alpha); }
    objLoader->renderObject(16);
    if(!pickerMode && !pickerModeDebug && !wire_mode) { glColor4f(0.9,0.5,0.5,alpha); }
    objLoader->renderObject(17);
  glPopMatrix();
}

void Visualisation::draw_meeting(float alpha) {
//  float angle = appModel->getRotationAngle();
  glPushMatrix();
    glScalef(1.0,1.0,1.0);
//    glRotatef(angle, 0.0, -1.0, 0.0);
    if(!pickerMode && !pickerModeDebug && !wire_mode) { glColor4f(1.0,1.0,0.7,alpha); }
    objLoader->renderObject(18);
    if(!pickerMode && !pickerModeDebug && !wire_mode) { glColor4f(0.9,0.5,0.5,alpha); }
    objLoader->renderObject(19);
    if(!pickerMode && !pickerModeDebug && !wire_mode) { glColor4f(1.0,1.0,0.7,alpha); }
    objLoader->renderObject(20);
  glPopMatrix();
}

void Visualisation::draw_radialface() {
  glPushMatrix();
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glColor4f(1.0, 1.0, 1.0, 0.2);
    objLoader->renderObject(0);
    glColor3f(0.8, 0.2, 0.2);
    objLoader->renderObject(1);
  glPopMatrix();
}

void Visualisation::draw_radialtile() {
  glPushMatrix();
    glScalef(1.2, 1.0, 1.0);
    objLoader->renderObject(2);
  glPopMatrix();
}

void Visualisation::draw_flattile() {
  glPushMatrix();
    glScalef(2.0, 0.1, 2.0);
    glutSolidCube(tile_dimension);
  glPopMatrix();
}

void Visualisation::draw_icon(int value, int scale, float alpha, bool highlight) {
  
  float importance = scale*2.0;

  switch(value) {
    case 0:
      break;
    case 1:
      glScalef(importance,importance,importance);
      draw_outline(2, alpha, highlight); // birthday icon
      break;
    case 2:
      glScalef(importance,importance,importance);
      draw_outline(3, alpha, highlight); // general memo icon
      break;
    case 3:
      glScalef(importance,importance,importance);
      draw_outline(4, alpha, highlight); // work icon
      break;
    case 4:
      glScalef(importance,importance,importance);
      draw_outline(5, alpha, highlight); // holiday icon
      break;
    case 5:
      glScalef(importance,importance,importance);
      draw_outline(6, alpha, highlight); // meeting icon
      break;
    default:
      break;
  }

}

void Visualisation::draw_importance(int value) {
  glDepthMask(GL_FALSE);
  glDisable(GL_CULL_FACE);
  glPushMatrix();
    glScalef(1.2, 0.8, 1.0);

    switch(value) {
      case 0:
        break;
      case 1:
        if(!pickerMode && !pickerModeDebug) { glColor4f(0.2,0.8,0.2, 0.4); }
        objLoader->renderObject(3);
        break;
      case 2:
        if(!pickerMode && !pickerModeDebug) { glColor4f(0.6,0.6,0.2, 0.4); }
        objLoader->renderObject(4);
        break;
      case 3:
        if(!pickerMode && !pickerModeDebug) { glColor4f(0.8,0.2,0.2, 0.4); }
        objLoader->renderObject(5);
        break;
      default:
        break;
      
    }

  glPopMatrix();
  glDepthMask(GL_TRUE);
  glEnable(GL_CULL_FACE);
}


// draw objects with outline
void Visualisation::draw_outline(int draw_id, float alpha, bool highlight) {
  // draw objects with outline
  // draw solid object 
  glPushAttrib (GL_POLYGON_BIT);
  glEnable (GL_CULL_FACE);
  // Draw front-facing polygons as filled
  glPolygonMode (GL_FRONT, GL_FILL);
  glCullFace (GL_BACK);
  wire_mode = false;

  // first draw
  switch(draw_id) {
    case 0:
      draw_radialtile();
      break;
    case 1:
      draw_flattile();
      break;
    case 2:
      draw_giftbox(alpha);
      break;
    case 3:
      draw_memo(alpha);
      break;
    case 4:
      draw_work(alpha);
      break;
    case 5:
      draw_holiday(alpha);
      break;
    case 6:
      draw_meeting(alpha);
      break;
    default:
      break;
  };

  // Draw back-facing polygons as lines
  glPushAttrib (GL_LIGHTING_BIT | GL_LINE_BIT | GL_DEPTH_BUFFER_BIT);
  // Disable lighting for outlining
  glDisable (GL_LIGHTING);
  glPolygonMode (GL_BACK, GL_LINE);
  glCullFace (GL_FRONT);
  glDepthFunc (GL_LEQUAL);
	      
  // draw wire object
  glLineWidth (3.0f);
  if(!pickerMode && !pickerModeDebug) { glColor4f(0.0,0.0,0.0,alpha); }
  if(highlight) { glColor4f(0.8,0.2,0.2,alpha); }
  wire_mode = true;

  // second draw
  switch(draw_id) {
    case 0:
      draw_radialtile();
      break;
    case 1:
      draw_flattile();
      break;
    case 2:
      draw_giftbox(alpha);
      break;
    case 3:
      draw_memo(alpha);
      break;
    case 4:
      draw_work(alpha);
      break;
    case 5:
      draw_holiday(alpha);
      break;
    case 6:
      draw_meeting(alpha);
      break;
    default:
      break;
  };

  glPopAttrib (); // GL_LIGHTING_BIT | GL_LINE_BIT | GL_DEPTH_BUFFER_BIT
  glPopAttrib (); // GL_POLYGON_BIT

}

// getters
char* Visualisation::getPrototypeName() {
  switch(mode) {
    case 1: 
      strcpy(prototype_name, "Prototype 1: Radial Visualisation view");
      name_length = strlen(prototype_name);
      break;
    case 2: 
      strcpy(prototype_name, "Prototype 2: Pathway Visualisation view");
      name_length = strlen(prototype_name);
      break;
    case 3:
      strcpy(prototype_name, "Prototype 3: Grid-style Visualisation view");
      name_length = strlen(prototype_name);
      break;
    case 4:
      strcpy(prototype_name, "Prototype 4: EMPTY");
      name_length = strlen(prototype_name);
      break;
    case 5:
      strcpy(prototype_name, "Prototype 5: EMPTY");
      name_length = strlen(prototype_name);
      break;
    default:
      break;
  }  
  return prototype_name;
}

int Visualisation::getPrototypeNameLen() {
  return name_length;
}

char* Visualisation::getEventSubject() {
  int selected_id = appModel->getSelectedDateIndex() *-1;
  printf("SELECTED : %d\n", selected_id);
//  printf("SUBJECT: %s\n", days[selected_id].event_subject);
//  printf("ARRAY SIZE: %lu\n", days.size());
  if(days.size()!=0 && (unsigned int)selected_id < days.size()) {
    return days[selected_id].event_subject;
  } else {
    return (char*)"EMPTY";
  }
}

char* Visualisation::getEventStartDateTime() {
  int selected_id = appModel->getSelectedDateIndex() *-1;
  if(days.size()!=0 && (unsigned int)selected_id < days.size()) {
    std::string buf(days[selected_id].event_startDate);
    buf.append(" ");
    buf.append(days[selected_id].event_startTime);
    // minor editing of date format
  //  if(!buf.empty()) {
  //    size_t f = buf.find(",");
  //    buf.replace(f, 1, "/");
  //    f = buf.find(",");
  //    buf.replace(f, 1, "/");
  //  }
    char* datetime = new char[buf.length() +1];
    strcpy(datetime, buf.c_str());
    return datetime;
  } else {
    return (char*)"EMPTY";
  }
}

char* Visualisation::getEventEndDateTime() {
  int selected_id = appModel->getSelectedDateIndex() *-1;
  if(days.size()!=0 && (unsigned int)selected_id < days.size()) {
    std::string buf(days[selected_id].event_endDate);
    buf.append(" ");
    buf.append(days[selected_id].event_endTime);
    // minor editing of date format
  //  if(!buf.empty()) {
  //    size_t f = buf.find(",");
  //    buf.replace(f, 1, "/");
  //    f = buf.find(",");
  //    buf.replace(f, 1, "/");
  //  }
    char* datetime = new char[buf.length() +1];
    strcpy(datetime, buf.c_str());
    return datetime;
  } else {
    return (char*)"EMPTY";
  }
}

char* Visualisation::getEventLocation() {
  int selected_id = appModel->getSelectedDateIndex() *-1;
  if(days.size()!=0 && (unsigned int)selected_id < days.size()) {
    return days[selected_id].event_location;                                                                              // <-- WORKING HERE !
  } else {
    return (char*)"EMPTY";
  }
}


// setters
void Visualisation::setPrototype(int newMode) {
  mode = newMode;
}


// PROTOTYPE FOR VISUALISATIONS
void Visualisation::prototype_1() {
// Radial Visualisation perspective mode
  // initialise variables
  int segments = 7;
  float size = 0.5f;
  tile_dimension = 0.7f;
  float segment_angle = 51.44;
  float alpha;

  int day;
  int weekday;
  int today = days[0].weekday;
  int event_id;
  int event_icon;
  int event_importance;
  unsigned int current_day = calendar.getWeekDay()-1+7;
  int selected = appModel->getSelectedDateIndex()-1;
  //printf("current:%d, selected:%d\n", current_day, selected);

  pickerMode = appModel->getPickingMode();
  //printf("pickerMode:%s\n", pickerMode?"true":"false");

  // picking mode - disable lighting effects
  if(pickerMode) {	
    // disable effects
    glDisable(GL_DITHER);
    glDisable(GL_LIGHTING);
    glDisable(GL_FOG);
  } else {
    // enable effects
    glEnable(GL_DITHER);
    glEnable(GL_LIGHTING);
  }

  // draw visualisation
  glPushMatrix();
    glTranslatef(0.0, 0.0, -2.0);
    glRotatef(today*segment_angle, 0.0,0.0,1.0);
    glRotatef(selected*segment_angle, 0.0,0.0,1.0);
    draw_radialface();

//    // guide lines
//    for (float i = 0.0; i < segments; i += 1.0) {
//      float angle = M_PI * i * 2.0 / segments ;
//      float nextAngle = M_PI * (i + 1.0) * 2.0 / segments;

//      /* compute sin & cosine */
//      float x1 = size * sin(angle), y1 = size * cos(angle);
//      float x2 = size * sin(nextAngle), y2 = size * cos(nextAngle);

//      glBegin(GL_LINE_LOOP);
//        glColor3f(1.0,1.0,1.0);
//        // near
//        glVertex3f(x1, y1, 0.0);
//        glVertex3f(x2, y2, 0.0);
//        glVertex3f( 0,  0, 0.0);
//      glEnd();
//    }

    glPushMatrix();
    glTranslatef(0.0,0.0,selected*-0.075);  // translate date tiles
    glRotatef(3*segment_angle,0.0,0.0,1.0); // correct date with weekday tile

    for (unsigned int i=0; i<days.size(); i++) {
      //week = days[i].week;
      weekday = days[i].weekday;
      day = days[i].day;
      event_id = days[i].event_id;
      event_icon = days[i].event_icon;
      event_importance = days[i].event_importance;
      alpha = 1.0f;

      // compute sin & cosine
      float angle = -M_PI * (float)i * 2.0 / segments ;
      float nextAngle = -M_PI * ((float)i + 1.0) * 2.0 / segments;
      float x1 = size * sin(angle), y1 = size * cos(angle);
      float x2 = size * sin(nextAngle), y2 = size * cos(nextAngle);

      // days tile past?
      int value = (selected*-1)-1;
      if(i<(unsigned)value) {
        int diff = value-i;
        alpha = 0.15f-diff*0.02f;
      }

      // draw date tile
      glPushMatrix();
        glTranslatef((x1+x2)*0.5, (y1+y2)*0.5, 0.0);
        radial_pos(i);
        glRotatef(15.0, 1.0,0.0,0.0);
        glScalef(0.25, 0.15, 0.2);

        // picking mode draws objects related to a day in its unique colour
        if(pickerMode) { 
          object_id_array.at(i).set_colour();
        } else {  // normal mode draws objects in its usual colour
          glColor4f(1.0, 1.0, 1.0, alpha);
        }
        // allow for transparent rendering
        if(i>=(unsigned)value) {
          // if current highlight tile red
          if(i == current_day) {
            draw_outline(0, alpha, true);
          } else {
            draw_outline(0, alpha, false);
          }
        } else {
          glDepthMask(GL_FALSE);
          // if current highlight tile red
          if(i == current_day) {
            draw_outline(0, alpha, true);
          } else {
            draw_outline(0, alpha, false);
          }
          glDepthMask(GL_TRUE);
        }

        // draw event icon
        if(event_id>=0) { 
          glPushMatrix();
          glTranslatef(0.0,-0.1+0.2*event_importance,0.0);
          glScalef(0.5, 0.5, 0.5);

          // draw only following event draw_model
          if(i>=(unsigned)value) { draw_icon(event_icon, event_importance, alpha, false); }
          glPopMatrix();
        }
        // draw objects without outline
        if(!pickerMode && !pickerModeDebug) { glColor4f(0.8,0.4,0.4, alpha+0.05); }
        drawDay(weekday, day);

      glPopMatrix();
    }

    // draw all alpha blended items
    if(!pickerMode && !pickerModeDebug) {
      for (unsigned int i=0; i<days.size(); i++) {
        // compute sin & cosine
        float angle = -M_PI * (float)i * 2.0 / segments ;
        float nextAngle = -M_PI * ((float)i + 1.0) * 2.0 / segments;
        float x1 = size * sin(angle), y1 = size * cos(angle);
        float x2 = size * sin(nextAngle), y2 = size * cos(nextAngle);
//        int value = (selected*-1)-1;
        glPushMatrix();
          glTranslatef((x1+x2)*0.5, (y1+y2)*0.5, 0.0);
          radial_pos(i);
          glRotatef(15.0, 1.0,0.0,0.0);
          glScalef(0.25, 0.15, 0.2);
          event_id = days[i].event_id;
          event_importance = days[i].event_importance;
//          if(event_id>=0) { // has event
//            // level of importance by depth indicator
//            if(i>=(unsigned)value) { draw_importance(event_importance); }
//          }
        glPopMatrix();
      }
    }
  glPopMatrix();
  glPopMatrix();

  // check picker if enabled and then redraw
  if(pickerMode) {
    pickerCheck();
    appModel->setSwapBuffer(false);
  } else {
    appModel->setSwapBuffer(true);
  }
}

void Visualisation::prototype_2() {
// Pathway Visualisation perspective mode
  // current variables
  pickerMode = appModel->getPickingMode();
  pickerModeDebug = appModel->getPickingModeDebug();
  selected = appModel->getSelected();
  unsigned int current_index;
  unsigned int current_day = calendar.getWeekDay()-1+7;
  tile_dimension = 0.5f;
  float alpha;

  // picking mode - disable lighting effects
  if(pickerMode || pickerModeDebug) {	
    // disable effects
    glDisable(GL_DITHER);
    glDisable(GL_LIGHTING);
    glDisable(GL_FOG);
  } else {
    // enable effects
    glEnable(GL_DITHER);
    glEnable(GL_LIGHTING);
    if(appModel->getFog()) {
      glEnable(GL_FOG);
    }
  }

  // DRAWS ALL DAYS CREATED IN INIT FUNCTION
  glPushMatrix();
    glTranslatef(-1.0, -1.45, -3.0);
    glRotatef(10.0, 1.0, 0.0,0.0);
    glRotatef(-25.0, 0.0, 1.0,0.0);

    //int week;
    int day;
    int weekday;
    int event_id;
    int today = days[0].weekday;
    int event_icon;
    int event_importance;


    for(unsigned int i=0; i<days.size(); i++) {
      //week = days[i].week;
      weekday = days[i].weekday;
      day = days[i].day;
      event_id = days[i].event_id;
      event_icon = days[i].event_icon;
      event_importance = days[i].event_importance;

      // days tile past?
      int value = (selected*-1)-1;
      if(i<(unsigned)value) {
        int diff = value-i;
        alpha = 0.15f-diff*0.02f;
      }

      // check selected date
      current_index = appModel->getSelectedDateIndex();
      if((i+current_index-today)==0.0) { 
        current_index = i;
        //printf("DAY:%d, %d,%d\n", day, i, current_index);
      }

      glPushMatrix();
        // draw items on curve
        curve_pos(i+selected);
        
        // picking mode draws objects related to a day in its unique colour
        if(pickerMode || pickerModeDebug) { 
          object_id_array.at(i).set_colour();
        } else {  // normal mode draws objects in its usual colour

          // highlight current day
          if(i==current_day) {
          glColor3f(1.0,0.7,0.7);
          } else {
          glColor3f(1.0,1.0,1.0);
          }
        }

        // draw objects with outline
        glPushMatrix();
          glScalef(4.0, 1.0, 0.5);

          // highlight current day
          if(i==current_day) {
            draw_outline(1, alpha, true);
          } else {
            draw_outline(1, alpha, false);
          }

        glPopMatrix();
  
        // draw event icon
        if(event_id>=0) { 
          glPushMatrix();
          glTranslatef(-2.8,0.15,0.0);
          if(i>=(unsigned)value) { draw_icon(event_icon, event_importance, 1.0, false); }
          glPopMatrix();
        }

        // draw objects without outline
        drawDate(weekday, day);

      glPopMatrix();
    }
  glPopMatrix();

  // check picker if enabled and then redraw
  if(pickerMode) {
    pickerCheck();
    appModel->setSwapBuffer(false);
  } else {
    appModel->setSwapBuffer(true);
  }
}

void Visualisation::prototype_3() { 
// Grid-style Visualisation perspective mode
  scale = 0.9;
  gap = 1.0-scale;
  tile_dimension = 0.6f;

  float center = -(tile_dimension+gap)*4.0-tile_dimension;
  float alpha = 1.0;

  pickerMode = appModel->getPickingMode();
  pickerModeDebug = appModel->getPickingModeDebug();
  selected = appModel->getSelected();
  int selected_date = appModel->getSelectedDateIndex()-1;

  unsigned int current_index;
  unsigned int current_day = calendar.getWeekDay()-1+7;

  // picking mode - disable lighting effects
  if(pickerMode || pickerModeDebug) {	
    // disable effects
    glDisable(GL_DITHER);
    glDisable(GL_LIGHTING);
    glDisable(GL_FOG);
  } else {
    // enable effects
    glEnable(GL_DITHER);
    glEnable(GL_LIGHTING);
    if(appModel->getFog()) {
      glEnable(GL_FOG);
    }
  }

  // draw grid
  glPushMatrix();
    glTranslatef(center,-1.25, -3.75); 
    glRotatef(10.0, 1.0, 0.0,0.0);
    
    int month, week, weekday, day;
    int today = days[0].weekday;
    int event_id;
    int event_icon;
    int event_importance;

    for(unsigned int i=0; i<days.size(); i++) {
      month = days[i].month;    
      week = days[i].week;
      weekday = days[i].weekday;
      day = days[i].day;
      event_id = days[i].event_id;
      event_icon = days[i].event_icon;
      event_importance = days[i].event_importance;

      // check selected date
      current_index = appModel->getSelectedDateIndex();
      if((i+current_index-today)==0.0) { 
        current_index = i-1;
        //printf("Day:%d, Week:%d\n", days[current_index].day, days[current_index].week);
      }

      // days tile past?
      int value = (selected_date*-1)-1;
      if(i<(unsigned)value) {
        int diff = value-i;
        alpha = 0.15f-diff*0.02f;
      } else {
        alpha = 1;
      }

      glPushMatrix();
      // draw date
      grid_pos(week, weekday, day);
      glScalef(0.6, 0.6, 0.6);
      if(!pickerMode && !pickerModeDebug) { glColor4f(0.8,0.4,0.4, alpha+0.05); }
      drawDay(weekday, day);

      // draw tile and icons
      glScalef(0.8, 0.6, 0.8);
      // picking mode draws objects related to a day in its unique colour
      if(pickerMode || pickerModeDebug) { 
        object_id_array.at(i).set_colour();
      } else {  // normal mode draws objects in its usual colour
        if(month%2==0) {
          glColor4f(0.9,0.9,1.0, alpha+0.05);
        } else {
          glColor4f(1.0,1.0,0.9, alpha+0.05);
        }
      }

      // draw event icon
      if(event_id>=0) { 
        glPushMatrix();
        glTranslatef(0.0,0.15,0.0);
        glScalef(0.5,0.5,0.5);
        if(i>=(unsigned)value) { draw_icon(event_icon, event_importance, 1.0, false); }
        glPopMatrix();
      }

      // picking mode draws objects related to a day in its unique colour
      if(pickerMode || pickerModeDebug) { 
        object_id_array.at(i).set_colour();
      } else {  // normal mode draws objects in its usual colour
        if(month%2==0) {
          glColor4f(0.9,0.9,1.0, alpha+0.05);
        } else {
          glColor4f(1.0,1.0,0.9, alpha+0.05);
        }
      }
      
      // draw day tile
      // highlight current day
      if(i==current_day) {
        draw_outline(1, alpha, true);
      } else {
        draw_outline(1, alpha, false);
      }
      glPopMatrix();
    }
  glPopMatrix();

  // check picker if enabled and then redraw
  if(pickerMode) {
    pickerCheck();
    appModel->setSwapBuffer(false);
  } else {
    appModel->setSwapBuffer(true);
  }

}

void Visualisation::prototype_4() { 
  // EMPTY
}

void Visualisation::prototype_5() {
  // EMPTY
}

void Visualisation::radial_pos(int index) {
  float gap = 1.0;
  float correction = index*0.07;
  float z = (index/7)*-gap;               // spacing between each week
  z += ((float)(index%7)/7) *-gap;        // forms spiral, connected days

  glRotatef(180+25, 0.0,0.0,1.0);         // rotation correction
  glRotatef(index*51.44, 0.0,0.0,1.0);
  glTranslatef(0.0,0.0, z+correction);
}

void Visualisation::curve_pos(float index) {
  // place on curve 
  float z = (index+1.0)*(-1.5); // adjustment
  float far = -5.0;
  float range = far - 0.0;
  float tmp;
  float spacing;

  if(z > far && z < 0) {
    tmp = (far-z)/range;
    //printf("angled %f:%f\n", z,tmp);  
    spacing = 0.1;
    //glTranslatef(0.0, -spacing*z, z); // (horiz,vertical, depth)
    glTranslatef(0.0, -spacing*z, z*0.6);
    glRotatef(tmp*45.0+10.0, 1.0,0.0,0.0);
  } else if (z <= far) {
    //printf("flat top %f:%f\n", z, 0.0);
    spacing = 0.1;
    glTranslatef(0.0, -spacing*z, z*0.5 - 0.5);
    glRotatef(10.0, 1.0,0.0,0.0);
  } else if (z >= 0) {
    //printf("facing screen %f:%f\n", z, 1.0);
    spacing = 0.5;
    glTranslatef(0.0, (-spacing*z)-(z*0.25), 0.0);
    glRotatef(90.0, 1.0, 0.0, 0.0);
  }
}

void Visualisation::grid_pos(int week, int weekday, int day) {
  // variables
  float gap = 0.15;
  float tile_dimension = 0.5;
  int selected_week = appModel->getSelectedWeek();

  float translate_center = weekday*tile_dimension+gap*weekday +0.75;
  float translate_week = -week*tile_dimension+gap*-week;
  float translate_selected_week = selected_week*tile_dimension+gap*selected_week +selected_week*0.25;

  // transformations
  glTranslatef(0.0,0.0,  translate_selected_week-0.2);
  glTranslatef(translate_center,0.0,translate_week);
  glTranslatef(0.0, 0.0, -0.25*week);

}

float Visualisation::computeScale(const char* text) {
	float maxWidth = 0.0;
  float maxHeight = 0.0;
  float maxScale = 0.0;
	float width = t3dDrawWidth(text);
  float height = t3dDrawHeight(text);
	if (width > maxWidth) {
		maxWidth = width;
  }
  if (height > maxHeight) {
    maxHeight = height;   
  }

  if (maxHeight > maxWidth) {
    maxScale = maxHeight;
  } else {
    maxScale = maxWidth;
  }

	return 2.6f / maxScale;
}


void Visualisation::smooth_selection(int frame) {
  // smooth selection animation
  float speed = 0.2;
  float tmp = appModel->getSelected();
  float selected_buff = appModel->getSelectedBuff();

  // removes stutter
  if(selected_buff<=0.01 && selected_buff >= -0.01) {
    appModel->emptySelectedBuff();
  }

  // adds sliding animation
  if(selected_buff != 0) {
    if(selected_buff>0) {
      tmp+=speed;
      appModel->setSelectedBuff(-speed);
      appModel->setSelected(tmp);
    } else if(selected_buff<0) {
      tmp-=speed;
      appModel->setSelectedBuff(speed);
      appModel->setSelected(tmp);
    }
  }
}

void Visualisation::pickerCheck() {
  // read the pixel at click position on the screen.
  int picked_x = appModel->getPicked_x();
  int picked_y = appModel->getPicked_y();
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
 
  unsigned char data[4];
  glReadPixels(picked_x,picked_y,1,1, GL_RGBA, GL_UNSIGNED_BYTE, data);
  glFlush();
  glFinish();
  //printf("[%d,%d] = [%d,%d,%d]\n", picked_x, picked_y, data[0], data[1], data[2]);

  // determine object by colour id
  bool match;
  int id_index = -1;
  for(unsigned int i=0; i<object_id_array.size(); i++) {
    match = true;
    if(object_id_array.at(i).r != data[0] ) { match = false; }
    if(object_id_array.at(i).g != data[1] ) { match = false; }
    if(object_id_array.at(i).b != data[2] ) { match = false; }

    // test for match
    if(match) { 
      id_index = i;
      // determine selected week
      //  printf("value: %d\n", days[id_index].week);
      appModel->setSelectedWeek(days[id_index].week);

    }
  }


  // make translation
  if(id_index>=0) {
//    printf("Object ID: %d [%d,%d,%d]\n", id_index, 
//          object_id_array.at(id_index).r, object_id_array.at(id_index).g, object_id_array.at(id_index).b);

    int current_index = -appModel->getSelectedDateIndex();
    int next_move = id_index - current_index;
    //printf("current:%d next:%d, change:%d\n", current_index, id_index, next_move);
    appModel->setSelectedDateIndex(-next_move);

  } else {
//    printf("Object ID: NOT OBJECT. [%d,%d,%d]\n", data[0], data[1], data[2]);
  }
  
  appModel->setPickingMode(false);
}

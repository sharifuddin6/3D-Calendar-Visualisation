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
  int total_weeks = 10;
  int upper_limit = 7*total_weeks; // 6 weeks in front

  int week = 0;
  int weekday = calendar.getWeekDay();
    
  int offset = 1-weekday; // where monday starts from 1, since 0 is not the initial state
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
  appModel->setCurrentDateIndex(-weekday+1.0);
}

void Visualisation::initLoad() {
  // load object
  objLoader = new ObjectLoader();
  objLoader->loadObject("data/model/gift_box.obj");
  objLoader->loadObject("data/model/gift_wrap.obj");
  objLoader->loadObject("data/model/gift_knot.obj");
  objLoader->loadObject("data/model/radial_face.obj");
  objLoader->loadObject("data/model/radial_text.obj");
  objLoader->loadObject("data/model/radial_tile.obj");
  objLoader->loadObject("data/model/radial_tile_1.obj");
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
  float angle = appModel->getRotationAngle();
  glPushMatrix();
    glScalef(0.4,0.4,0.4);
    glRotatef(angle, 0.0, -1.0, 0.0);
    // draw box
    if(!pickerMode && !pickerModeDebug && !wire_mode) { glColor4f(8.0,8.0,0.5,alpha); }
    objLoader->renderObject(0);
    // draw wrapping
    if(!pickerMode && !pickerModeDebug && !wire_mode) { glColor4f(2.0,0.1,0.1,alpha); }
    objLoader->renderObject(1);
    // draw knot
    if(!pickerMode && !pickerModeDebug && !wire_mode) { glColor4f(2.0,0.1,0.1,alpha); }
    objLoader->renderObject(2);
  glPopMatrix();	
}

void Visualisation::draw_radialface() {
  glPushMatrix();
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glColor4f(1.0, 1.0, 1.0, 0.2);
    objLoader->renderObject(3);
    glColor3f(0.8, 0.2, 0.2);
    objLoader->renderObject(4);
  glPopMatrix();
}

void Visualisation::draw_radialtile() {
  glPushMatrix();
    glScalef(1.2, 1.0, 1.0);
    objLoader->renderObject(5);
  glPopMatrix();
}

void Visualisation::draw_radialtile_1() {
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);
  glPushMatrix();
    glScalef(1.2, 1.0, 1.0);
    objLoader->renderObject(6);
  glPopMatrix();
  glEnable(GL_DEPTH_TEST);
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
    case 1:
      draw_giftbox(alpha);
      break;
    case 2:
      draw_radialtile();
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
    case 1:
      draw_giftbox(alpha);
      break;
    case 2:
      draw_radialtile();
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
      strcpy(prototype_name, "Prototype 2: Curved Perspective view");
      name_length = strlen(prototype_name);
      break;
    case 3:
      strcpy(prototype_name, "Prototype 3: Curved Perspective view (ver 2)");
      name_length = strlen(prototype_name);
      break;
    case 4:
      strcpy(prototype_name, "Prototype 4: Flat Perspective view");
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

// setters
void Visualisation::setPrototype(int newMode) {
  mode = newMode;
}


// PROTOTYPE FOR VISUALISATIONS
void Visualisation::prototype_1() {
// Radial Visualisation mode
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
  unsigned int current_day = today-1;
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
            draw_outline(2, alpha, true);
          } else {
            draw_outline(2, alpha, false);
          }
        } else {
          glDisable(GL_DEPTH_TEST);
          // if current highlight tile red
          if(i == current_day) {
            draw_outline(2, alpha, true);
          } else {
            draw_outline(2, alpha, false);
          }
          glEnable(GL_DEPTH_TEST);
        }

        // TODO: draw event object in correct position
        if(event_id>=0) { 
          glPushMatrix();
          // position the event draw_model
          if(false) { }                                               
          else { glTranslatef(0.0,-1.5,0.0); }
          // draw only following event draw_model
          if(i>=(unsigned)value) { draw_outline(1, alpha, false); }
          glPopMatrix();
          // level of importance by depth indicator
          if(!pickerMode && !pickerModeDebug) { glColor4f(0.8,0.2,0.2, 0.6); }
          if(i>=(unsigned)value) { draw_radialtile_1(); }
        }
        // draw objects without outline
        if(!pickerMode && !pickerModeDebug) { glColor4f(0.8,0.2,0.2, alpha+0.05); }
        drawDay(weekday, day);

      glPopMatrix();
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
  // REMOVED
}

void Visualisation::prototype_3() { 
  // REMOVED
}

void Visualisation::prototype_4() { 
  // REMOVED
}

void Visualisation::prototype_5() {
  // EMPTY
}

void Visualisation::radial_pos(int index) {
  float z = (index/7)*-0.55 +index*0.003;          // spacing between each week
  z += ((float)(index%7)/7) *-0.55;    // forms spiral, connected days

  glRotatef(180+25, 0.0,0.0,1.0);     // rotation correction
  glRotatef(index*51.44, 0.0,0.0,1.0);
  glTranslatef(0.0,0.0, z);
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
  float tmp = appModel->getSelected();
  float selected_buff = appModel->getSelectedBuff();

  // removes stutter
  if(selected_buff<=0.01 && selected_buff >= -0.01) {
    appModel->emptySelectedBuff();
  }

  // adds sliding animation
  if(selected_buff != 0) {
    if(selected_buff>0) {
      tmp+=0.1;
      appModel->setSelectedBuff(-0.1);
      appModel->setSelected(tmp);
    } else if(selected_buff<0) {
      tmp-=0.1;
      appModel->setSelectedBuff(0.1);
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
    if(match) { id_index = i; }
  }

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

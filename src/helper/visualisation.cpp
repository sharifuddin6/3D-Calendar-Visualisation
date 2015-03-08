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
  tile_dimension = 0.5f;
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
  appModel->setSelectedDateIndex(-weekday+1.0);
}

void Visualisation::initLoad() {
  // load object
  objLoader = new ObjectLoader();
  objLoader->loadObject("data/model/gift_box.obj");
  objLoader->loadObject("data/model/gift_wrap.obj");
  objLoader->loadObject("data/model/gift_knot.obj");

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

void Visualisation::drawTile() {
  glPushMatrix();
    glScalef(2.0, 0.1, 2.0);
    glutSolidCube(tile_dimension);
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
    glTranslatef(0.0, 0.5, -2.0);
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
void Visualisation::draw_giftbox() {
  float angle = appModel->getRotationAngle();
  glPushMatrix();
    glTranslatef(-1.25,0.0,0.0);
    glScalef(0.6,0.6,0.6);
    glRotatef(angle, 0.0, -1.0, 0.0);
    // draw box
    if(!pickerMode && !pickerModeDebug && !wire_mode) { glColor3f(8.0,8.0,0.5); }
    objLoader->renderObject(0);
    // draw wrapping
    if(!pickerMode && !pickerModeDebug && !wire_mode) { glColor3f(2.0,0.1,0.1); }
    objLoader->renderObject(1);
    // draw knot
    if(!pickerMode && !pickerModeDebug && !wire_mode) { glColor3f(2.0,0.1,0.1); }
    objLoader->renderObject(2);
  glPopMatrix();	
}

// draw objects with outline
void Visualisation::draw_outline(int draw_id) {

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
      drawTile();
      break;
    case 1:
      draw_giftbox();
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
  if(!pickerMode && !pickerModeDebug) { glColor3f(0.0,0.0,0.0); }
  wire_mode = true;

  // second draw
  switch(draw_id) {
    case 0:
      drawTile();
      break;
    case 1:
      draw_giftbox();
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
      strcpy(prototype_name, "Prototype 1: Curved Perspective view");
      name_length = strlen(prototype_name);
      break;
    case 2: 
      strcpy(prototype_name, "Prototype 2: Curved Perspective view (ver 2)");
      name_length = strlen(prototype_name);
      break;
    case 3:
      strcpy(prototype_name, "Prototype 3: Time Tunnel view");
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


}

void Visualisation::prototype_2() {
  // current variables
  pickerMode = appModel->getPickingMode();
  pickerModeDebug = appModel->getPickingModeDebug();
  selected = appModel->getSelected();
  unsigned int current_index;

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
    glTranslatef(0.0, -1.45, -2.65);
    glRotatef(10.0, 1.0, 0.0,0.0);

    //int week;
    int day;
    int weekday;
    int event_id;
    int today = days[0].weekday;

    for(unsigned int i=0; i<days.size(); i++) {
      //week = days[i].week;
      weekday = days[i].weekday;
      day = days[i].day;
      event_id = days[i].event_id;

      // check selected date
      current_index = appModel->getSelectedDateIndex();
      if((i+current_index-today)==0.0) { 
        current_index = i;
        //printf("DAY:%d, %d,%d\n", day, i, current_index);
      }

      glPushMatrix();
        // draw items on curve
        prototype_2_curve(i+selected);
        
        // picking mode draws objects related to a day in its unique colour
        if(pickerMode || pickerModeDebug) { 
          object_id_array.at(i).set_colour();
        } else {  // normal mode draws objects in its usual colour
          glColor3f(1.0,1.0,1.0);
        }

        // draw objects with outline
	      draw_outline(0);
        if(event_id>=0) { draw_outline(1); }

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
  // prototype_3: Time tunnel view
  int segments = 7;
  float radius = 0.3;
  //float height = 0.3;

  // guide lines
  for (float i = 0.0; i < segments; i += 1.0) {
    float angle = M_PI * i * 2.0 / segments ;
    float nextAngle = M_PI * (i + 1.0) * 2.0 / segments;

    /* compute sin & cosine */
    float x1 = radius * sin(angle), y1 = radius * cos(angle);
    float x2 = radius * sin(nextAngle), y2 = radius * cos(nextAngle);

    glBegin(GL_LINE_LOOP);

      glColor3f(1.0,1.0,1.0);
      
      // near
      glVertex3f(x1, y1, -1.0);
      glVertex3f(x2, y2, -1.0);
      glVertex3f(0, 0, -1.0);

      // far
      glVertex3f(x1, y1, -25.0);
      glVertex3f(x2, y2, -25.0);
      glVertex3f(0, 0, -25.0);

    glEnd();
   }

  // points
  glPointSize(10.0f);
  glBegin(GL_POINTS);
  for (float i = 0.0; i < segments+1; i += 1.0) {
    float angle = M_PI * i * 2.0 / segments ;
    float nextAngle = M_PI * (i + 1.0) * 2.0 / segments;

    /* compute sin & cosine */
    float x1 = radius * sin(angle), y1 = radius * cos(angle);
    float x2 = radius * sin(nextAngle), y2 = radius * cos(nextAngle);

    glColor3f(1.0,0.0,0.0);
      
    // near
    //glVertex3f(x1, y1, -1.0);
    //glVertex3f(x2, y2, -1.0);

    // mid point
    glVertex3f((x1+x2)*0.5, (y1+y2)*0.5, -1.0);
   
  }
  glEnd();

}

void Visualisation::prototype_4() { 
  // prototype_4: Flat perspective view
  scale = 0.9;
  gap = 1.0-scale;
  float center = -(tile_dimension+gap)*4.0;
  
  // DRAW GRID
  glPushMatrix();
    glTranslatef(center,-1.25, -3.75);
    glRotatef(10.0, 1.0, 0.0,0.0);

    // DRAWS ALL DAYS CREATED IN INIT FUNCTION
    int week, weekday, day;

    for(unsigned int i=0; i<days.size(); i++) {
      week = days[i].week;
      weekday = days[i].weekday;
      day = days[i].day;
      prototype_4_drawTile(week, weekday, day);
    }

  glPopMatrix();
}

void Visualisation::prototype_5() {

}

void Visualisation::prototype_2_curve(float index) {
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
    glTranslatef(0.0, -spacing*z, z);
    glRotatef(tmp*90.0+10.0, 1.0,0.0,0.0);
  } else if (z <= far) {
    //printf("flat top %f:%f\n", z, 0.0);
    spacing = 0.1;
    glTranslatef(0.0, -spacing*z, z);
    glRotatef(10.0, 1.0,0.0,0.0);
  } else if (z >= 0) {
    //printf("facing screen %f:%f\n", z, 1.0);
    spacing = 0.5;
    glTranslatef(0.0, (-spacing*z)-(z*0.25), 0.0);
    glRotatef(90.0, 1.0, 0.0, 0.0);
  }
}

void Visualisation::prototype_4_drawTile(int week, int weekday, int day) {
  glPushMatrix();
    glColor3f(1.0,1.0,1.0);    
    glTranslatef(weekday*tile_dimension+gap*weekday,0.0,-week*tile_dimension+gap*-week);
    glTranslatef(0.0, 0.0, -0.5*week);
    glScalef(0.6, 0.6, 0.6);
    drawDate(weekday, day);
    glColor3f(1.0,1.0,1.0);
    glScalef(0.8, 0.6, 0.8);
    drawTile();
  glPopMatrix();
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
      tmp+=0.05;
      appModel->setSelectedBuff(-0.05);
      appModel->setSelected(tmp);
    } else if(selected_buff<0) {
      tmp-=0.05;
      appModel->setSelectedBuff(0.05);
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

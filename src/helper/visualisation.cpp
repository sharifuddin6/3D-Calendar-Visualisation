#include "visualisation.h"
#include "../../lib/drawtext/text3d.h"

#include <GL/glut.h>
#include <stdio.h>
#include <string.h>
#include <cmath>


Visualisation::Visualisation() {
  mode = 1;
  prototype_name = new char[64];
  getPrototypeName();

  tile_dimension = 0.5f;
  
//  const char* date = calendar.getDate(25); 
//  int day = calendar.parseDay(date);
//  printf("25 days from today: %d\n", day);
  init();
}

void Visualisation::init() {
  // this week from monday
  int total_weeks = 10;
  int upper_limit = 7*total_weeks; // 6 weeks in front

  int week = 0;
  int weekday = calendar.getWeekDay();
//  int today = calendar.getDay();
    
  int offset = 1-weekday; // where monday starts from 1, since 0 is not the initial state
  weekday = 1;
  char date_buff[32];
  
  for(int i=0; i<upper_limit; i++) {
    sprintf(date_buff, "%s", calendar.getDate(offset));
    int day = calendar.parseDay(date_buff);
    aDay aday;
    aday.week = week;
    aday.weekday = weekday;
    aday.day = day;

    days.push_back(aday); // push back
    
    offset++;
    weekday+=1;
    
    if((i+1)%7 == 0) { week++; weekday = 1; }
  }

}

void Visualisation::draw(int frame) {
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
    default:
      break;  
  } 

}

void Visualisation::drawTile(int weekday, int day) {
  // init 3dtext
  t3dInit();

  char *buff = new char[4];
  snprintf(buff, 4, "%d", day);

  glPushMatrix();
    glColor3f(0.8,0.2,0.2);
    glScalef(0.1, 0.6, 0.1);
    glTranslatef(0.0, 0.5, 0.0);    
    drawText(buff);
  glPopMatrix();

  glColor3f(1.0,1.0,1.0);
  glPushMatrix();
    glScalef(0.8,1,1);
    glutSolidCube(tile_dimension);
  glPopMatrix();
}

void Visualisation::drawText(const char* text) {
  float text_scale;
  text_scale = computeScale(text);

  glPushMatrix();
  glScalef(text_scale, text_scale, text_scale);
	glRotatef(90, -1, 0, 0);
	t3dDraw3D(text, 0, 0, 0.2f);
	glPopMatrix();

}

float Visualisation::computeScale(const char* text) {
	float maxWidth = 0;
	float width = t3dDrawWidth(text);
	if (width > maxWidth) {
		maxWidth = width;
  }
	return 2.6f / maxWidth;
}

// getters
char* Visualisation::getPrototypeName() {
  switch(mode) {
    case 1: 
      strcpy(prototype_name, "Prototype 1: Flat Perspective view");
      name_length = strlen(prototype_name);
      break;
    case 2:
      strcpy(prototype_name, "Prototype 2: Time Tunnel view");
      name_length = strlen(prototype_name);
      break;
    case 3:
      strcpy(prototype_name, "Prototype 3: 3D Lexis Pencil");
      name_length = strlen(prototype_name);
      break;
    case 4:
      strcpy(prototype_name, "Prototype 4: 3D Fibonacci Spiral");
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
  // prototype_1: Flat perspective view
  scale = 0.75;
  gap = 1.0-scale;
  float center = (0.5*tile_dimension) -(tile_dimension)*(7.0*0.5f) -gap - (tile_dimension);

  // DRAW GRID
  glPushMatrix();
    glTranslatef(center,-1.25, -3.75);

    // DRAWS ALL DAYS CREATED IN INIT FUNCTION
    int week, weekday, day;

    for(unsigned int i=0; i<days.size(); i++) {
      week = days[i].week;
      weekday = days[i].weekday;
      day = days[i].day;
      prototype_1_drawTile(week, weekday, day);
    }

  glPopMatrix();
}

void Visualisation::prototype_2() { 
  // prototype_2: Time tunnel view
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

void Visualisation::prototype_3() { 
  // prototype_3: Lexis Pencil
  // draw 3d text
  t3dInit();

  glPushMatrix();
    glTranslatef(0.0f, 0.0f, -8.0f);
    const char* word_1 = "SHARIF HERE!";
    drawText(word_1);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0.0f, -0.2f, -8.0f);
    const char* word_2 = "FRIDAY";
    drawText(word_2);
  glPopMatrix();

}

void Visualisation::prototype_4() {
  // prototype_4: Fibonacci spiral view
  float rotations = 5; //How many times the spiral rotates around until it stops.
  float theta, nextTheta;
  float epsilon = 0.1f * 2.0f * M_PI;
  float x1, y1, z1;
  float x2, y2, z2;


  glBegin(GL_LINES);
  for(theta = 0.0f; theta < rotations * 2.0f * M_PI; theta += epsilon) {
    x1 = sin(theta) * theta;
    y1 = cos(theta) * theta;
    z1 = theta;

    nextTheta = theta+epsilon;    
    x2 = sin(nextTheta) * nextTheta;
    y2 = cos(nextTheta) * nextTheta;
    z2 = nextTheta;

    glVertex3f(x1,y1,z1-10);
    glVertex3f(x2,y2,z2-10);

  }
  glEnd();
}

void Visualisation::prototype_1_drawTile(int week, int weekday, int day) {
  glPushMatrix();
    glColor3f(1.0,1.0,1.0);    
    glTranslatef(weekday*tile_dimension+gap,0,-week*tile_dimension+gap*-week);
    glScalef(1.0, 0.05, 1.0);
    drawTile(weekday, day);
  glPopMatrix();
}


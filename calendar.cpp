#include "calendar.h"
#include <stdio.h>
#include <time.h>
#include <cmath>

Calendar::Calendar() { 
  mode = 1;

  tile_dimension = 0.5f;
  days = 7;
  weeks = 25;

  // get datetime
  time_t     now = time(0);
  struct tm  tstruct;
  char       buf[80];
  tstruct = *localtime(&now);
  strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
  printf("current datetime: %s\n", buf);

}

void Calendar::prototype_1() {
  // prototype_1: Flat perspective view
  float scale = 0.75;
  float gap = 1.0-scale;
  float center = (0.5*tile_dimension) -(tile_dimension)*((float)days*0.5f) -gap;

  // DRAW GRID
  glPushMatrix();
    glTranslatef(center,-1.0f, -10.0f);
  
    for(int i=0; i<days; i++) {
      for(int j=0; j<weeks; j++) {
        
        // tiles for days
        glPushMatrix();
          glTranslatef(i*tile_dimension+gap,0,j*tile_dimension*1.1);
          //glRotatef(5.0, 1.0, 0.0, 0.0);
          glScalef(1.0, 0.05, 1.0);
          glColor3f(1.0,1.0,1.0);
          glutSolidCube(tile_dimension*scale);
        glPopMatrix();        
      
      }   
    }
  glPopMatrix();
}

void Calendar::prototype_2() { 
  // prototype_2: Time tunnel view
  int segments = 7;
  float radius = 0.5;
  float height = 0.5;

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

void Calendar::prototype_3() { 
  // prototype_3: Fibonacci spiral view
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

void Calendar::prototype_4() { }


void Calendar::draw(int frame) {
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

void Calendar::drawText(float x, float y, const char *string) {
  const char *c;

  glMatrixMode( GL_PROJECTION ) ;
  glPushMatrix() ; // save
  glLoadIdentity();// and clear
  glMatrixMode( GL_MODELVIEW ) ;
  glPushMatrix() ;
  glLoadIdentity() ;
  
  gluOrtho2D (0.0f, 800.0f, 0.0f, 600.0f);
  glDisable( GL_DEPTH_TEST ) ; // also disable the depth test so renders on top

  glColor3f(1.0f,1.0f,1.0f);
  glRasterPos2f(x, y);
  for (c=string; *c != '\0'; c++) {
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *c);
  }
  
  glEnable( GL_DEPTH_TEST ) ; // Turn depth testing back on

  glMatrixMode( GL_PROJECTION ) ;
  glPopMatrix() ; // revert back to the matrix I had before.
  glMatrixMode( GL_MODELVIEW ) ;
  glPopMatrix() ;
  
}

void Calendar::setPrototype(int newMode) {
  mode = newMode;
}

#include "cube.h"
#include <stdio.h>

Cube::Cube() { }

void Cube::draw(int frame) {
  // update angle
  int angle = frame%360;

  glPushMatrix();
    glTranslatef(-30,0,-40);
    glRotatef(angle, 0.1, 0.2, 0.5);
    glColor3ub(255,0,255);
    glutSolidCube(1);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(-20,0,-30);
    glRotatef((float)angle, 0.1, 0.2, 0.5);
    glColor3ub(255,0,0);
    glutSolidCube(1);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(-10,0,-20);
    glRotatef(angle, 0.1, 0.2, 0.5);
    glColor3ub(0,255,0);
    glutSolidCube(1);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0,0,-10);
    glRotatef(angle, 0.1, 0.2, 0.5);
    glColor3ub(0,0,255);
    glutSolidCube(1);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(5,0,0);
    glRotatef(angle, 0.1, 0.2, 0.5);
    glColor3ub(255,255,0);
    glutSolidCube(1);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(10,0,10);
    glRotatef((float)angle, 0.1, 0.2, 0.5);
    glColor3ub(255,0,0);
    glutSolidCube(1);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(15,0,15);
    glRotatef(angle, 0.1, 0.2, 0.5);
    glColor3ub(0,255,0);
    glutSolidCube(1);
  glPopMatrix();

}

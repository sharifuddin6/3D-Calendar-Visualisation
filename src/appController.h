/*
 * The controller class interface for the visualisation software. 
 * Skeleton code for various mouse and keyboard listeners.
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


#ifndef APPCONTROLLER_H
#define APPCONTROLLER_H

#include "appModel.h"

#include <stdio.h>
#include <GL/glut.h>


class AppController {

  public:
    // constructor
    AppController(AppModel *newAppModel);

    // enum menu options
    enum MENU_TYPE { MENU_1, MENU_2, MENU_3, MENU_4, MENU_5 };

    virtual void menu(int item);
    virtual void mouse(int button, int state, int x, int y);
    virtual void keyboard(unsigned char key, int x, int y);
    virtual void specialInput(int key, int x, int y);

  private:
    AppModel *appModel;
    int change, current;
    float pos_x, pos_y, pos_z;
    float selected;

};

#endif

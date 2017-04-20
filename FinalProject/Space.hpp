//
//  Space.hpp
//  FinalProject
//
//  Created by Adam Barson on 4/19/17.
//  Copyright © 2017 Adam Barson. All rights reserved.
//

#ifndef Space_hpp
#define Space_hpp

#include <stdio.h>

#include <stdlib.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

/* Game Functionality */

void drawAllAsteroids();

void moveAllBullets();

void moveAllAsteroids();

void nextLevel();

void pause();

void openMenu();

void highScore();

/* Game Functionality */

/* GLUT Functionality */
// Program initialization NOT OpenGL/GLUT dependent,
// as we haven't created a GLUT window yet
void init(void);

// Callback functions for GLUT */

// Draw the window - this is where all the GL actions are
void display(void);

// Called when window is resized,
// also when window is first created,
// before the first call to display().
void reshape(int w, int h);

// Refresh the display, called when system is idle
void refresh(void);

// Trap and process keyboard events
void kbd(unsigned char key, int x, int y);

// Handle "mouse cursor moved" events
void cursor(int x, int y);

// Handle "mouse moved with button pressed" events
void drag(int x, int y);

// Handle mouse button pressed and released events
void mouse(int button, int state, int x, int y);

int graphicsPlay(int argc, char *argv[]);

#endif /* Space_hpp */

//
//  Space.cpp
//  FinalProject
//
//  Created by Adam Barson on 4/19/17.
//  Copyright © 2017 Adam Barson. All rights reserved.
//

#include "Space.hpp"
#include "GamePiece.hpp"
#include <iostream>
#include <fstream>
//#include <irrklang/irrKlang.h>

GLdouble screen_width, screen_height;

int wd;

vector<Asteroid> asteroids;

vector<Circle_Coord> thrustFire;

Ship ship;
vector<Bullet> clip;

int mouse_x, mouse_y = 0;

int counter = 0;

int start_ast;

bool keys[256];

ofstream write_discovered;

//winmm.lib
//conio.h

/*ALCdevice *device;

ALsizei size, freq;
ALenum format;
ALvoid *data;
ALboolean loop = AL_FALSE;




void test(){
    device = alcOpenDevice(NULL);
    if (!device){
        cout << "Oh no..." << endl;
    } else {
        cout << "Heck yeah." << endl;
    }
    
    
}
*/

void collisions(){
    for (int i = 0; i < asteroids.size(); ++i){
        for (int j = 0; j < clip.size(); ++j){
            if (asteroids[i].detectCollision(clip[j])){
                asteroids.erase(asteroids.begin() + i);
                clip.erase(clip.begin() + j);
                i--;
                j--;
            }
        }
        if (asteroids[i].detectCollision(ship)){
            //
        }
    }
}
void start(){
    ifstream in_file("save_state.txt");
    if (in_file){
        cout << "Would you like to load your previous game state? (y/n)" << endl;
        string user_input;
        while ((!(cin >> user_input) || (user_input != "y" && user_input != "n"))){
            cin.clear();
            string junk;
            getline(cin, junk);
            cout << "Enter a y/n. " << endl;
        }
        if (user_input == "y"){
            in_file >> start_ast;
            write_discovered.open("save_state.txt");
        } else{
            start_ast = 1;
            write_discovered.open("save_state.txt");
        }
    } else {
        write_discovered.open("save_state.txt");
        //write_discovered("save_state.txt");
        cout << "No save file found. Making one for you now... " << endl;
        start_ast = 1;
    }
    
    //ifstream read_discovered("save_state.txt");
}

void spawnThrustFire(){
    Circle_Coord c1(2);
    c1.set_center(Point2D(ship.getLocation().get_x() - ship.getDirection().get_x() * 40 - rand() % 8 + 1, ship.getLocation().get_y() -ship.getDirection().get_y() * 40));
    c1.set_color(1, 0, 0);
    c1.set_outside_color(1, 0, 0);
    
    Circle_Coord c2(2);
    c2.set_center(Point2D(ship.getLocation().get_x() - ship.getDirection().get_x() * 40 + rand() % 8 + 1, ship.getLocation().get_y() -ship.getDirection().get_y() * 40));
    c2.set_color(1, 0, 0);
    c2.set_outside_color(1, 0, 0);
    
    Circle_Coord c3(2);
    c3.set_center(Point2D(ship.getLocation().get_x() - ship.getDirection().get_x() * 40, ship.getLocation().get_y() -ship.getDirection().get_y() * 40 + rand() % 8 + 1));
    c3.set_color(1, 0, 0);
    c3.set_outside_color(1, 0, 0);
    
    Circle_Coord c4(2);
    c4.set_center(Point2D(ship.getLocation().get_x() - ship.getDirection().get_x() * 40, ship.getLocation().get_y() -ship.getDirection().get_y() * 40  - rand() % 8 + 1));
    c4.set_color(1, 0, 0);
    c1.set_outside_color(1, 0, 0);
    
    Circle_Coord c5(2);
    c5.set_center(Point2D(ship.getLocation().get_x() - ship.getDirection().get_x() * 40, ship.getLocation().get_y() -ship.getDirection().get_y() * 40));
    c5.set_color(1, 0, 0);
    //c5.set_outside_color(1, 0, 0);
    thrustFire.push_back(c1);
    thrustFire.push_back(c2);
    thrustFire.push_back(c3);
    thrustFire.push_back(c4);
    thrustFire.push_back(c5);
    
}

void reduceThrustFire(){
    for (int i = 0; i < thrustFire.size(); ++i){
        thrustFire[i].set_center(Point2D(thrustFire[i].get_center_x() + rand() % (5 - (-5) + 1) + (-5), thrustFire[i].get_center_y() + rand() % (5 - (-5) + 1) + (-5)));
        thrustFire[i].set_radius(thrustFire[i].get_radius()-0.20);
        if (thrustFire[i].get_radius() < 0.01){
            thrustFire[i].set_radius(0);
            thrustFire.erase(thrustFire.begin() + i);
            i--;
        }
    }
}

void drawAllAsteroids(){
    for (int i = 0; i < asteroids.size(); ++i){
        asteroids[i].drawShape();
    }
}

void moveAllAsteroids(){
    for (int i = 0; i < asteroids.size(); ++i){
        asteroids[i].move();
    }
}
void drawBullets(){
    for(int i=0; i<clip.size();++i){
        clip[i].drawShape();
    }
}
void moveBullets(){
    for(int i=0; i<clip.size();++i){
        clip[i].move();
    }
}
void init() {
   // test();
    start();
    cout << "Number of asteroids to start:" << start_ast << endl;
    screen_width = 600;
    screen_height = 600;
    ship = Ship();
    for (int i = 0; i < start_ast; ++i){
        asteroids.push_back(Asteroid());
    }
}


/* Initialize OpenGL Graphics */
void initGL() {
    // Set "clearing" or background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black and opaque
    glColor3f(0.0f, 0.0f, 1.0f);
}

/* Handler for window-repaint event. Call back when the window first appears and
 whenever the window needs to be re-painted. */
void display() {
    // tell OpenGL to use the whole window for drawing
    glViewport(0, 0, screen_width, screen_height);
    
    // do an orthographic parallel projection with the coordinate
    // system set to first quadrant, limited by screen/window size
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, screen_width, screen_height, 0.0, -1.f, 1.f);
    
    
    
    glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer with current clearing color
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    ship.drawShape();
    drawAllAsteroids();
    
    for (int i = 0; i < thrustFire.size(); i++){
        thrustFire[i].draw();
    }
    drawBullets();
    
    glFlush();
}

// http://www.theasciicode.com.ar/ascii-control-characters/escape-ascii-code-27.html
void kbd(unsigned char key, int x, int y)
{
    // escape
    if (key == 27) {
        write_discovered << asteroids.size();
        glutDestroyWindow(wd);
        exit(0);
    }
    if (key == 32){
        if (ship.getShotDelay() == 0){
        clip.push_back(Bullet(Point2D(ship.getDirection().get_x(),ship.getDirection().get_y()), Point2D(ship.getLocation().get_x(), ship.getLocation().get_y())));
            ship.shoot();
        }
        
        
    }
    
    if (key == 'G') {
        glColor3f(0.0f, 1.0f, 0.0f);
    }
    
    if (key == 'R') {
        glColor3f(1.0f, 0.0f, 0.0f);
    }
    
    glutPostRedisplay();
    
    return;
}

void kbdS(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_DOWN:
            //maybe break in the future?
            break;
        case GLUT_KEY_LEFT:
            keys[GLUT_KEY_LEFT] = true;
            break;
        case GLUT_KEY_RIGHT:
            keys[GLUT_KEY_RIGHT] = true;
            break;
        case GLUT_KEY_UP:
            keys[GLUT_KEY_UP] = true;
            break;
            
    }
    glutPostRedisplay();
    return;
}

void kbdU(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_DOWN:
            
            break;
        case GLUT_KEY_LEFT:
            keys[GLUT_KEY_LEFT] = false;
            break;
        case GLUT_KEY_RIGHT:
            keys[GLUT_KEY_RIGHT] = false;
            break;
        case GLUT_KEY_UP:
            keys[GLUT_KEY_UP] = false;
            break;
            
    }
    
    glutPostRedisplay();
    
    return;
}

void cursor(int x, int y) {
    mouse_x = x;
    mouse_y = y;
    glutPostRedisplay();
}

// button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
// state will be GLUT_UP or GLUT_DOWN
void mouse(int button, int state, int x, int y) {
    glutPostRedisplay();
}

void timer(int extra) {
    if (keys[GLUT_KEY_LEFT]){
        ship.rotateL();
    }
    if (keys[GLUT_KEY_RIGHT]){
        ship.rotateR();
    }
    if (keys[GLUT_KEY_UP]){
        ship.move();
        spawnThrustFire();
    }
    moveAllAsteroids();
    reduceThrustFire();
    moveBullets();
    counter++;
    if (counter % 100 == 0 && asteroids.size() < 5){
       asteroids.push_back(Asteroid());
    }
    ship.update();
    glutTimerFunc(30, timer, 0);
    glutPostRedisplay();
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
    
    init();
    
    glutInit(&argc, argv);          // Initialize GLUT
    
    glutInitDisplayMode(GLUT_RGBA);
    
    glutInitWindowSize((int)screen_width, (int)screen_height);
    glutInitWindowPosition(100, 100); // Position the window's initial top-left corner
    /* create the window and store the handle to it */
    wd = glutCreateWindow("Asteroids!" /* title */ );
    
    // Register callback handler for window re-paint event
    glutDisplayFunc(display);
    
    // Our own OpenGL initialization
    initGL();
    
    // register keyboard press event processing function
    // works for numbers, letters, spacebar, etc.
    glutKeyboardFunc(kbd);
    
    // register special event: function keys, arrows, etc.
    glutSpecialFunc(kbdS);
    
    glutSpecialUpFunc(kbdU);
    
   // glutIgnoreKeyRepeat(true);
    
    // handles mouse movement
    glutPassiveMotionFunc(cursor);
    
    // handles mouse click
    glutMouseFunc(mouse);
    
    // handles timer
    glutTimerFunc(0, timer, 0);
    
    // Enter the event-processing loop
    glutMainLoop();
    return 0;
}

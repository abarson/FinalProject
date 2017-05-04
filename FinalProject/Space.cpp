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

enum screen_state {menu, game_play, paused, game_over};

GLdouble screen_width, screen_height;

int wd;

vector<Asteroid> asteroids;

vector<Circle_Coord> thrustFire;

vector<Circle_Coord> explosionFire;

Ship ship;
vector<Bullet> clip;
Powerup PU;

screen_state screen;


int mouse_x, mouse_y = 0;

int counter = 0;

int start_ast;

bool keys[256];

bool respawning = false;

ofstream write_discovered;

enum type {SHIP, ASTEROID};

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

void display_menu() {
    // draw a string message
    
    string message = "Click anywhere to begin";
    glColor3f(1, 1, 1);
    glRasterPos2i(170, 250);
    for (int i = 0; i < message.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, message[i]);
    }
    string asteroid_message = "Welcome to Asteroid!";
    glColor3f(1,1,1);
    glRasterPos2i(180, 150);
    for (int i = 0; i < asteroid_message.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, asteroid_message[i]);
    }
    
}

void display_paused(){
    string pause_message = "Paused";
    glColor3f(1, 1, 1);
    glRasterPos2i(250, 250);
    for (int i = 0; i < pause_message.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, pause_message[i]);
    }
    
    string resume_message = "'r' to resume";
    glColor3f(1, 1, 1);
    glRasterPos2i(220, 300);
    for (int i = 0; i < resume_message.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, resume_message[i]);
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
            start_ast = 1;
        }
    }

void explosion(Point2D loc, double size, type t){
    for (int i = 0; i < 20 + (int)size; ++i){
        Circle_Coord c(rand() % ((int)size / 6));
        if (t == SHIP){
            c.set_outside_color(1, 1, 0);
            c.set_color(1, 1, 0);
        } else {
            c.set_outside_color(100.0/255, 100.0/255, 100.0/255);
            c.set_color(150.0/255, 150.0/255, 150.0/255);
        }
        c.set_center(loc.get_x() + rand() % ((int)size - (-(int)size) + 1) + (-(int)size), loc.get_y() + rand() % ((int)size - (-(int)size) + 1) + (-(int)size));
        explosionFire.push_back(c);
        
    }
}

void collisions(){
    for (int i = 0; i < asteroids.size(); ++i){
        for (int j = 0; j < clip.size(); ++j){
            if (asteroids[i].detectCollision(clip[j])){
                explosion(asteroids[i].getLocation(), asteroids[i].getCircle().get_radius(), ASTEROID);
                asteroids.erase(asteroids.begin() + i);
                clip.erase(clip.begin() + j);
                i--;
                j--;
            }
        }
        
    }
    if (!respawning){
        for (int i = 0; i < asteroids.size(); ++i){
            if (asteroids[i].detectCollision(ship)){
                explosion(asteroids[i].getLocation(), asteroids[i].getCircle().get_radius(), ASTEROID);
                explosion(ship.getLocation(), 30, SHIP);
                ship.regenerate();
                respawning = true;
                asteroids.erase(asteroids.begin() + i);
                i--;
            }
        }
    }
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

void reduceFire(){
    for (int i = 0; i < thrustFire.size(); ++i){
        thrustFire[i].set_center(Point2D(thrustFire[i].get_center_x() + rand() % (5 - (-5) + 1) + (-5), thrustFire[i].get_center_y() + rand() % (5 - (-5) + 1) + (-5)));
        thrustFire[i].set_radius(thrustFire[i].get_radius()-0.20);
        if (thrustFire[i].get_radius() < 0.01){
            thrustFire[i].set_radius(0);
            thrustFire.erase(thrustFire.begin() + i);
            i--;
        }
    }
    for (int i = 0; i < explosionFire.size(); ++i){
        explosionFire[i].set_center(Point2D(explosionFire[i].get_center_x() + rand() % (5 - (-5) + 1) + (-5), explosionFire[i].get_center_y() + rand() % (5 - (-5) + 1) + (-5)));
        explosionFire[i].set_radius(explosionFire[i].get_radius()-0.20);
        if (explosionFire[i].get_radius() < 0.01){
            explosionFire[i].set_radius(0);
            explosionFire.erase(explosionFire.begin() + i);
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
        if (clip[i].getLifeTime() > 50){
            clip.erase(clip.begin() + i);
            i--;
        }
    }
}

void generateBullet(){
    if (!respawning){
        if (ship.getShotDelay() == 0){
            clip.push_back(Bullet(Point2D(ship.getDirection().get_x(),ship.getDirection().get_y()), Point2D(ship.getLocation().get_x(), ship.getLocation().get_y())));
            ship.shoot();
        }
    }
}

void animation(){
    ship.drawShape();
    drawAllAsteroids();
    
    for (int i = 0; i < thrustFire.size(); ++i){
        thrustFire[i].draw();
    }
    
    for (int i = 0; i < explosionFire.size(); ++i){
        explosionFire[i].draw();
    }
    drawBullets();
    PU.drawShape();
}

void init() {
   // test();
    start();
    screen = menu;
    cout << "Number of asteroids to start:" << start_ast << endl;
    screen_width = 600;
    screen_height = 600;
    ship = Ship();
    for (int i = 0; i < start_ast; ++i){
        asteroids.push_back(Asteroid());
        
    }
    respawning = true;
}


/* Initialize OpenGL Graphics */
void initGL() {
    // Set "clearing" or background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black and opaque
    glColor3f(0.0f, 0.0f, 1.0f);
}


void play(){
    
    if (screen == game_play){
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
        if (keys[32]){
            generateBullet();
        }
        moveAllAsteroids();
        reduceFire();
        collisions();
        moveBullets();
        PU.move();
        counter++;
        if (counter % 100 == 0 && asteroids.size() < 5){
            asteroids.push_back(Asteroid());
        }
        ship.update();
        
        if (respawning){
            ship.setRespawning(ship.getRespawning() + 1);
            ship.blink();
            if (ship.getRespawning() == 50){
                ship.setRespawning(0);
                respawning = false;
            }
        }
    }
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
    
    animation();
    
    switch(screen) {
        case menu:
            display_menu();
            break;
        case game_play:
            //play();
            break;
        case game_over:
            //display_game_over();
            break;
        case paused:
            display_paused();
    }
    
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
        keys[32] = true;
    }
    
    if (key == 'G') {
        glColor3f(0.0f, 1.0f, 0.0f);
    }
    
    if (key == 'R') {
        glColor3f(1.0f, 0.0f, 0.0f);
    }
    
    if (key == 'p' && screen == game_play) {
        screen = paused;
    }
    
    if (key == 'r' && screen == paused){
        screen = game_play;
    }
    
    glutPostRedisplay();
    
    return;
}

// http://www.theasciicode.com.ar/ascii-control-characters/escape-ascii-code-27.html
void kbU(unsigned char key, int x, int y)
{
    
    if (key == 32){
        keys[32] = false;
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
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP &&screen == menu) {
        screen = game_play;
    }
    glutPostRedisplay();
}


void timer(int extra) {
    play();
    
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
    
    glutKeyboardUpFunc(kbU);
    
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

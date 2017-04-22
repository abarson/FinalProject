//
//  GamePiece.cpp
//  FinalProject
//
//  Created by Adam Barson on 4/19/17.
//  Copyright © 2017 Adam Barson. All rights reserved.
//

#include "GamePiece.hpp"
#include "Space.hpp"
#include <stdlib.h>
using namespace std;
GamePiece::GamePiece(){
    velocity = 0;
    target = Point2D();
    origin = Point2D();
}

void GamePiece::setVelocity(double vIn){
    if (vIn > 0){
        velocity = vIn;
    }
    else {
        velocity = 1;
    }
}

double GamePiece::getVelocity() const{
    return velocity;
}


Ship::Ship(){
    shape = Triangle_Coord(300, 300);
    shape.set_color(1, 1, 0);
    numLives = 3;
    thrustV = 0;
    rotationalV = 0;
}

void Ship::regenerate(){
    //not implemented
}
void Ship::rotateR(){
    shape.set_angle(shape.get_angle() + 1);
}
void Ship::rotateL(){
    //not implemented
}
void Ship::shoot(){
    //not implemented
}
Shape Ship::getShape() const {
    return shape;
}
void Ship::drawShape() {
    shape.draw();
}
void Ship::explode() {
    //not implemented
}
Point2D Ship::getLocation() const{
    return shape.get_tip();
}
void Ship::move() {
    //not implemented
}
bool Ship::detectCollision(GamePiece *piece) const {
    //not implemented
    return false;
}

Asteroid::Asteroid(): GamePiece(){
    shape = Circle_Coord();
    initFields();
}

void Asteroid::initFields(){
    double r_velocity = rand() % 8 + 3;
    double r_size = rand() % 30 + 20;
    setVelocity(r_velocity);
    shape.set_radius(r_size);
    
    shape.set_outside_color(100.0/255, 100.0/255, 100.0/255);
    shape.set_color(150.0/255, 150.0/255, 150.0/255);
    
    int c = rand() % 4;
    int x;
    int y;
    
    //there are four different cases for spawning the Asteroid, one for each side of the screen
    switch(c){
        case(0):
            x = 600;
            y = rand() % 300 + 200;
            break;
        case(1):
            x = rand() % 300 + 200;
            y = 600;
            break;
        case(2):
            x = 0;
            y = rand() % 300 + 200;
            break;
        case(3):
            x = rand() % 300 + 200;
            y = 0;
            break;
        default:
            x = 0;
            y = 0;
    }
    shape.set_center(x, y);
    
    //set the target to be the opposite side of the screen of the Asteroid
    target.set_x(600 - x);
    target.set_y(600 - y);
    
    double x_dir = target.get_x() - getLocation().get_x();
    double y_dir = target.get_y() - getLocation().get_y();
    double length = sqrt(pow((x_dir), 2) + pow((y_dir), 2));
    direction.set_x(x_dir/length);
    direction.set_y(y_dir/length);
    
}
Shape Asteroid::getShape() const{
    return shape;
}

void Asteroid::drawShape(){
    shape.draw();
}

void Asteroid::explode(){
    //not implemented
}

Point2D Asteroid::getLocation() const{
    return shape.get_center();
}

void Asteroid::move(){
    if ((getLocation().get_x() > -20 && getLocation().get_x() < 620 && getLocation().get_y() > -20 && getLocation().get_y() < 620)){
        shape.set_center(getLocation().get_x() + (direction.get_x()) * getVelocity(), getLocation().get_y() + (direction.get_y()) * getVelocity());
    }
    else{
        if (getLocation().get_x() < 0){
            shape.set_center(600, getLocation().get_y());
        }
        else if (getLocation().get_x() > 600){
            shape.set_center(0, getLocation().get_y());
        }
        else if (getLocation().get_y() < 0){
            shape.set_center(getLocation().get_x(), 600);
        }
        else{
            shape.set_center(getLocation().get_x(), 0);
        }
    }
    
}

bool Asteroid::detectCollision(GamePiece *piece) const{
    return false;
}




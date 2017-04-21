//
//  GamePiece.cpp
//  FinalProject
//
//  Created by Adam Barson on 4/19/17.
//  Copyright © 2017 Adam Barson. All rights reserved.
//

#include "GamePiece.hpp"
#include <stdlib.h>
using namespace std;
GamePiece::GamePiece(){
    velocity = 0;
    target = Point2D();
    origin = Point2D();
}


double GamePiece::getDirection(){
    return 0;
}

bool GamePiece::detectCollision(){
    return false;
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

Ship::Ship(): GamePiece(){
    triangle = Circle_Coord();
    triangle.set_center(300, 300);
    triangle.set_color(0, 1, 1);
    //terminalV = 0;
    //friction = 0;
    numLives = 3;
    thrustV = 0;
    rotationalV = 0;
}

void Ship::regenerate(){
    
}

void Ship::rotateR(){
    
}

void Ship::rotateL(){
    
}

void Ship::shoot(){
    
}

Shape Ship::getShape(){
    return triangle;
}

void Ship::drawShape(){
    triangle.draw();
}

void Ship::move(){
    
}

void Ship::explode(){
    
}

Point2D Ship::getLocation(){
    return triangle.get_center();
}

void Ship::moveTowards() {
    
}


Asteroid::Asteroid(): GamePiece(){
    shape = Circle_Coord();
    initFields();

    double x_dir = target.get_x() - getLocation().get_x();
    double y_dir = target.get_y() - getLocation().get_y();
    double length = sqrt(pow((x_dir), 2) + pow((y_dir), 2));
    direction.set_x(x_dir/length);
    direction.set_y(y_dir/length);
}

void Asteroid::initFields(){
    double r_velocity = rand() % 8 + 3;
    double r_size = rand() % 30 + 20;
    setVelocity(r_velocity);
    shape.set_radius(r_size);
    
    shape.set_outside_color(1, 0, 0);
    shape.set_color(1, 1, 0);
    
    int c = rand() % 4;
    int x;
    int y;
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
            x = rand() % 300 + 2000;
            y = 0;
            break;
        default:
            x = 0;
            y = 0;
    }
    cout << c << endl;
    shape.set_center(x, y);
    target.set_x(600 - x);
    target.set_y(600 - y);
    
}
Shape Asteroid::getShape() {
    return shape;
}

void Asteroid::drawShape(){
    shape.draw();
}
void Asteroid::move(){
    
}
void Asteroid::explode(){
    
}

Point2D Asteroid::getLocation(){
    return shape.get_center();
}

void Asteroid::moveTowards(){
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



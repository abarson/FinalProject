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
    direction = Point2D();
    velocity = Point2D();
}

void Ship::regenerate(){
    //not implemented
}
void Ship::rotateR(){
    shape.rotate(ROTATION_FORCE);
}
void Ship::rotateL(){
    shape.rotate(-ROTATION_FORCE);
}
void Ship::shoot(){
    cout << "shoot"<<endl;
    
    //not implemented
    // call a bullet polygon each time the space bar is pressed
    // center that bullet polygon at the tip vertex of the ship
    // have it faced in (get direction)
    // move at a constant velocity in direction
}

Point2D Ship::getDirection() const{
    double x_dir = shape.get_tip().get_x() - shape.get_center().get_x();
    double y_dir = shape.get_tip().get_y() - shape.get_center().get_y();
    double length = sqrt(pow((x_dir), 2) + pow((y_dir), 2));
    return Point2D(x_dir/length, y_dir/length);
}

void Ship::update(){
    keepMoving();
    applyFriction();
    checkBounds();
}

void Ship::applyFriction(){
    if (velocity.get_x() != 0){
        velocity.set_x(velocity.get_x()*FRICTION);
        if (abs(velocity.get_x()) < 0.001){
            velocity.set_x(0);
        }
    }
    
    if (velocity.get_y() != 0){
        velocity.set_y(velocity.get_y()*FRICTION);
        if (abs(velocity.get_y()) < 0.001){
            velocity.set_y(0);
        }
    }
}

void Ship::updateDirection(){
    direction.set_x(getDirection().get_x());
    direction.set_y(getDirection().get_y());
}

void Ship::keepMoving(){
    double result_x = velocity.get_x();
    double result_y = velocity.get_y();
    
    Point2D new_tip(shape.get_tip().get_x() + result_x, shape.get_tip().get_y() + result_y);
    Point2D new_bl(shape.get_bl().get_x() + result_x, shape.get_bl().get_y() + result_y);
    Point2D new_br(shape.get_br().get_x() + result_x, shape.get_br().get_y() + result_y);
    Point2D center(shape.get_center().get_x() + result_x, shape.get_center().get_y() + result_y);
    
    shape.set_tip(new_tip);
    shape.set_bl(new_bl);
    shape.set_br(new_br);
    shape.set_center(center);
}

void Ship::speedCap(){
    double result_x = velocity.get_x();
    double result_y = velocity.get_y();
    
    double speed = sqrt(pow((result_x), 2) + pow((result_y), 2));
    if (speed > MAX_SPEED){
        result_x/=speed;
        result_y/=speed;
        result_x*=MAX_SPEED;
        result_y*=MAX_SPEED;
    }
    velocity.set_x(result_x);
    velocity.set_y(result_y);
    speed = sqrt(pow((result_x), 2) + pow((result_y), 2));
    cout << speed << ": " << result_x << ", " << result_y << endl;
}

void Ship::checkBounds(){
    if (shape.get_center().get_x() < -BUFFER || shape.get_center().get_x() > 600 + BUFFER || shape.get_center().get_y() < -BUFFER || shape.get_center().get_y() > 600 + BUFFER){
        Point2D rel_tip = shape.get_rel_tip();
        Point2D rel_bl = shape.get_rel_bl();
        Point2D rel_br = shape.get_rel_br();
        if (shape.get_center().get_x() < 0){
            shape.set_center(Point2D(600, shape.get_center().get_y()));
        }
        else if (shape.get_center().get_x() > 600){
            shape.set_center(Point2D(0, shape.get_center().get_y()));
        }
        else if (shape.get_center().get_y() < 0){
            shape.set_center(Point2D(shape.get_center().get_x(), 600));
        }
        else if (shape.get_center().get_y() > 600){
            shape.set_center(Point2D(shape.get_center().get_x(), 0));
        }
        shape.set_tip(Point2D(shape.get_center().get_x() + rel_tip.get_x(), shape.get_center().get_y() + rel_tip.get_y()));
        shape.set_bl(Point2D(shape.get_center().get_x() + rel_bl.get_x(), shape.get_center().get_y() + rel_bl.get_y()));
        shape.set_br(Point2D(shape.get_center().get_x() + rel_br.get_x(), shape.get_center().get_y() + rel_br.get_y()));
    }
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
    updateDirection();
    
    velocity.set_x(velocity.get_x() + direction.get_x());
    velocity.set_y(velocity.get_y() + direction.get_y());
    
    speedCap();
    
    spawnThrustFire();
}
bool Ship::detectCollision(GamePiece &piece) const {
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
    if ((getLocation().get_x() > -BUFFER && getLocation().get_x() < 600 + BUFFER && getLocation().get_y() > -BUFFER && getLocation().get_y() < 600 + BUFFER)){
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

bool Asteroid::detectCollision(GamePiece &piece) const{
    return false;
}
  
Bullet::Bullet(Point2D dIn, Point2D loc): GamePiece(){
    shape = Circle_Coord();
    bdirection = dIn;
    initFields(dIn, loc);
}

void Bullet::initFields(Point2D dIn, Point2D loc){
    double r_velocity = 5;
    double r_size = 2;
    setVelocity(r_velocity);
    shape.set_radius(r_size);
    
    shape.set_color(1, 0, 0);
    //shape.set_outside_color(255/255, 0/255, 0/255);
    //shape.set_color(255/255, 0/255, 0/255);
    
    shape.set_center(Point2D(loc.get_x() + dIn.get_x(), loc.get_y() + dIn.get_y()));
    
    //set the target to be the opposite side of the screen of the Asteroid
    target.set_x(shape.get_center().get_x()+200);
    target.set_y(shape.get_center().get_y()+200);
    
    double x_dir = target.get_x() - getLocation().get_x();
    double y_dir = target.get_y() - getLocation().get_y();
    double length = sqrt(pow((x_dir), 2) + pow((y_dir), 2));
    //bdirection.set_x(x_dir/length);
    //bdirection.set_y(y_dir/length);
    
}

Shape Bullet::getShape() const {
    return shape;
}
void Bullet::drawShape() {
    shape.draw();
}
void Bullet::explode() {
    //not implemented
}
Point2D Bullet::getLocation() const{
    return Point2D();
}
void Bullet::move() {
    shape.set_center(shape.get_center().get_x() + (bdirection.get_x())*15, shape.get_center().get_y() + (bdirection.get_y())*15);
    
    
}
bool Bullet::detectCollision(GamePiece &piece) const {
    //not implemented
    return false;
}

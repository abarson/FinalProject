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
    if (velocity > 0){
        velocity = vIn;
    }
    else {
        velocity = 1;
    }
}

double GamePiece::getVelocity() const{
    return velocity;
}

Asteroid::Asteroid(int x, int y): GamePiece(){
    double r = rand() % 100;
    int buffer_x = 0;
    int buffer_y = 0;
    setVelocity(r);
    cout << r << endl;
    shape = Circle_Coord();
    shape.set_radius(20);
    shape.set_center(x, y);
    origin.set_x(x);
    origin.set_y(y);
    if (x > 0){
        buffer_x = -20;
    }
    else{
        buffer_x = 20;
    }
    
    if (y > 0){
        buffer_y = -20;
    }
    else{
        buffer_y = 20;
    }
    target.set_x(600 + buffer_x - x);
    target.set_y(600 + buffer_y - y);
    shape.set_outside_color(1, 0, 0);
    shape.set_color(0, 1, 1);
    
    double x_dir = target.get_x() - getLocation().get_x();
    double y_dir = target.get_y() - getLocation().get_y();
    double length = sqrt(pow((x), 2) + pow((y), 2));
    direction.set_x(x_dir/length);
    direction.set_y(y_dir/length);
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
    
    double x = target.get_x() - getLocation().get_x();
    double y = target.get_y() - getLocation().get_y();
    cout << x << endl;
    cout << y << endl;
    if ((x > 2.5 || x < -2.5) && (y > 2.5 || y < -2.5)){
        double length = sqrt(pow((x), 2) + pow((y), 2));
        shape.set_center(getLocation().get_x() + (x/length) * 5, getLocation().get_y() + (y/length) * 5);
    }
    else{
        shape.set_center(600 - getLocation().get_x(), 600 - getLocation().get_y());
    }
    
}

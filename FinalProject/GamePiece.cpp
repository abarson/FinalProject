//
//  GamePiece.cpp
//  FinalProject
//
//  Created by Adam Barson on 4/19/17.
//  Copyright © 2017 Adam Barson. All rights reserved.
//

using namespace std;
#include "GamePiece.hpp"
GamePiece::GamePiece(){
    velocity = 0;
    target = Point2D();
}

void Asteroid::moveTowards(){
    
    double x = target.get_x() - getLocation().get_x();
    double y = target.get_y() - getLocation().get_y();
    if (x != 0 && y != 0){
        double length = sqrt(pow((x), 2) + pow((y), 2));
        shape.set_center(getLocation().get_x() + (x/length) * 5, getLocation().get_y() + (y/length) * 5);
    }
    
}

double GamePiece::getDirection(){
    return 0;
}

bool GamePiece::detectCollision(){
    return false;
}

Asteroid::Asteroid(int x, int y): GamePiece(){
    shape = Circle_Coord();
    shape.set_radius(20);
    shape.set_center(x, y);
    target.set_x(400 - x);
    target.set_y(600 - y);
    shape.set_outside_color(1, 0, 0);
    shape.set_color(0, 1, 1);
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

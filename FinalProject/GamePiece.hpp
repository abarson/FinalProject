//
//  GamePiece.hpp
//  FinalProject
//
//  Created by Adam Barson on 4/19/17.
//  Copyright © 2017 Adam Barson. All rights reserved.
//

#ifndef GamePiece_hpp
#define GamePiece_hpp

#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Shape{
    Shape();
    ~Shape();
};
class Point2D{
    Point2D();
    ~Point2D();
};


class GamePiece{
public:
    GamePiece();
    //~GamePiece();
    virtual void setShape()=0;
    virtual void move()=0;
    virtual void explode()=0;
    virtual double getLocation();
    virtual double getDirection();
    virtual bool detectCollision();
private:
    //fields
    double velocity;
    Shape Shape();
    Point2D point();
};

class Bullet: public GamePiece{
public:
    Bullet();
    //~Bullet();
    virtual void setShape() override;
    virtual void move() override;
    virtual void explode() override;
    
private:
    //fields
    double baseVelocity;
    int lifeTime;
    
    
};
class Ship: public GamePiece{
public:
    Ship();
    //~Ship();
    void regenerate();
    void rotateR();
    void rotateL();
    void shoot();
    virtual void setShape() override;
    virtual void move() override;
    virtual void explode() override;
    
private:
    //fields
    static double terminalV;
    static double friction;
    int numLives;
    double thrustV;
    double rotationalV;
    
};
class Asteroid: public GamePiece{
public:
    Asteroid();
    //~Asteroid();
    virtual void setShape() override;
    virtual void move() override;
    virtual void explode() override;
    
private:
    //fields
    
};


#endif /* GamePiece_hpp */

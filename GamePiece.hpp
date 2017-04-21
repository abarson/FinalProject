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
#include "Shape.hpp"
using namespace std;

class GamePiece{
public:
    GamePiece();
    //~GamePiece();
    virtual Shape getShape()=0;
    virtual void drawShape()=0;
    virtual void move()=0;
    virtual void explode()=0;
    virtual Point2D getLocation() = 0;
    virtual void moveTowards() = 0;
    virtual double getDirection();
    virtual bool detectCollision();
    virtual void setVelocity(double vIn);
    virtual double getVelocity() const;
protected:
    Point2D target;
    Point2D origin;
private:
    //fields
    double velocity;
};

class Bullet: public GamePiece{
public:
    Bullet();
    //~Bullet();
    virtual Shape getShape() override;
    virtual void drawShape() override;
    virtual void move() override;
    virtual void explode() override;
    virtual Point2D getLocation() override;
    virtual void moveTowards() override;
    
private:
    //fields
    double baseVelocity;
    int lifeTime;
    //We will need a line object
    
};
class Ship: public GamePiece{
public:
    Ship();
    //~Ship();
    void regenerate();
    void rotateR();
    void rotateL();
    void shoot();
    virtual Shape getShape() override;
    virtual void drawShape() override;
    virtual void move() override;
    virtual void explode() override;
    virtual Point2D getLocation() override;
    virtual void moveTowards() override;
    
    
private:
    //fields
    static double terminalV;
    static double friction;
    int numLives;
    double thrustV;
    double rotationalV;
    //don't know what shape yet... triangle?
    Circle_Coord triangle;
    
};
class Asteroid: public GamePiece{
public:
    Asteroid();
    //~Asteroid();
    void initFields();
    virtual Shape getShape() override;
    virtual void drawShape() override;
    virtual void move() override;
    virtual void explode() override;
    virtual Point2D getLocation() override;
    virtual void moveTowards() override;
    
    
private:
    //fields
    Circle_Coord shape;
    Point2D direction;
    
};


#endif /* GamePiece_hpp */

//
//  asteroid.hpp
//  FinalProject
//
//  Created by Eli Gitelman on 4/19/17.
//  Copyright © 2017 Adam Barson. All rights reserved.
//

#ifndef asteroid_hpp
#define asteroid_hpp
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
    GamePiece();
    ~GamePiece();
    
    virtual void setShape()=0;
    virtual void move()=0;
    virtual void explode()=0;
    virtual double getLocation();
    virtual double getDirection();
    virtual bool detectCollision();
    
    
    //fields
    double velocity;
    Shape Shape();
    Point2D point();
    
    
};

class Bullet: public GamePiece{
    Bullet();
    ~Bullet();
    virtual void setShape() override;
    virtual void move() override;
    virtual void explode() override;
    
    //fields
    double baseVelocity;
    int lifeTime;

    
};
class Ship: public GamePiece{
    Ship();
    ~Ship();
    void regenerate();
    void rotateR();
    void rotateL();
    void shoot();
    virtual void setShape() override;
    virtual void move() override;
    virtual void explode() override;
    
    //fields
    static double terminalV;
    static double friction;
    int numLives;
    double thrustV;
    double rotationalV;
    
};
class Asteroid: public GamePiece{
    Asteroid();
    ~Asteroid();
    virtual void setShape() override;
    virtual void move() override;
    virtual void explode() override;
    
    //fields

    
};
class Space{
    Space();
    ~Space();
    void getAsteroid();
    void getShip();
    void getBullet();
    void nextLevel();
    void pause();
    void openMenu();
    void highScore();
    
    
    vector<Asteroid> asteroids;
    vector<Bullet> bullets;


};



#include <stdio.h>

#endif /* asteroid_hpp */

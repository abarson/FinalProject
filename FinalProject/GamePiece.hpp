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

#define MAX_SPEED 12 //max speed that the Ship can move in
#define BUFFER 20 //the distance from the edge of the screen the Ship or Asteroid can go before being moved to the opposite side of the screen
#define ROTATION_FORCE 5 //the amount of degrees the Ship rotates
#define FRICTION 0.95 //the force used to slow down the Ship
#define SHOT_DELAY 10
using namespace std;

class GamePiece{
public:
    /**
     * Requires: nothing
     * Modifies: instance fields
     * Effects: set instance fields to default values
     */
    GamePiece();
    
    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects: return the shape of the GamePiece
     */
    virtual Shape getShape() const=0;
    
    /**
     * Requires: nothing
     * Modifies: the GUI display
     * Effects: add the shape to the screen
     */
    virtual void drawShape()=0;
    
    /**
     * Requires: the GamePiece has intersected with another compatible GamePiece
     * Modifies: the GUI display
     * Effects: remove the GamePiece from the screen and generate a small explosion animation
     */
    virtual void explode()=0;
    
    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects: get the location of the GamePiece
     */
    virtual Point2D getLocation() const=0;
    
    /**
     * Requires: nothing
     * Modifies: the location of the GamePiece
     * Effects: move the GamePiece towards a target location. If it goes out of the bounds of the screen, move it to the opposite side of the screen, for a continuous flow effect.
     */
    virtual void move() = 0;
    
    /**
     * Requires: vIn >= 1
     * Modifies: velocity
     * Effects: sets a new velocity
     */
    virtual void setVelocity(double vIn);
    
    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects: get the velocity of the GamePiece
     */
    virtual double getVelocity() const;
protected:
    Point2D target;
    Point2D origin;
private:
    double velocity;
};

class Ship: public GamePiece{
public:
    /**
     * Requires: nothing
     * Modifies: instance fields
     * Effects: set instance fields to default values
     */
    Ship();
    
    /**
     * Requires: the Ship has been destroyed
     * Modifies: the GUI display
     * Effects: respawn the ship in the middle of the screen
     */
    void regenerate();
    
    /**
     * Requires: nothing
     * Modifies: the direction of the Ship
     * Effects: rotate the Ship to the right
     */
    void rotateR();
    
    /**
     * Requires: nothing
     * Modifies: the direction of the Ship
     * Effects: rotate the Ship to the left
     */
    void rotateL();
    
    /**
     * Requires: nothing
     * Modifies: the GUI display
     * Effects: shoot a Bullet from the tip of the Ship
     */
    void shoot();
    
    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects: get the current direction of the Ship
     */
    Point2D getDirection() const;
    
    /**
     * Requires: nothing
     * Modifies: velocity and position of the Ship
     * Effects: continues to move the Ship and applies friction. Put the ship back in bounds if it goes out of bounds
     */
    void update();
    
    /**
     * Requires: nothing
     * Modifies: velocity
     * Effects: reduce the velocity by the FRICTION rate
     */
    void applyFriction();
    
    /**
     * Requires: nothing
     * Modifies: direction
     * Effects: calculate the direction of the ship as a normalized 2D vector
     */
    void updateDirection();
    
    /**
     * Requires: nothing
     * Modifies: the location of the Ship
     * Effects: move the Ship using its velocity
     */
    void keepMoving();
    
    /**
     * Requires: nothing
     * Modifies: velocity
     * Effects: if the speed of the ship is too high, reduce it to fit the restraints of MAX_SPEED
     */
    void speedCap();
    
    /**
     * Requires: nothing
     * Modifies: the location of the Ship
     * Effects: if the Ship goes of screen, place it on the other side of the screen.
     */
    void checkBounds();
    
    /**
     * Requires: nothing
     * Modifies: shotDelay
     * Effects: 
     */
    void gunUpdate();
    
    void setShotDelay(int sIn);
    
    int getShotDelay() const;
    
    
    Triangle_Coord getTriangle() const;
    
    
    //Triangle shape
    virtual Shape getShape() const override;
    
    virtual void drawShape() override;
    
    virtual void explode() override;
    
    virtual Point2D getLocation() const override;
    
    //movement based on user input
    virtual void move() override;
    
private:
    Triangle_Coord shape;
    int numLives;
    Point2D direction;
    Point2D velocity;
    double shotDelay;
};

class Bullet: public GamePiece{
public:
    /**
     * Requires: nothing
     * Modifies: instance fields
     * Effects: set direction of Bullet and set instance fields to default values
     */
    Bullet(Point2D dIn, Point2D loc);
    void initFields(Point2D dIn, Point2D loc);
    
    Circle_Coord getCircle() const;
    
    //the shape of the Bullet is a simple line
    virtual Shape getShape() const override;
    
    virtual void drawShape() override;
    
    //There will be no explosion for the bullet, just removal from the screen
    virtual void explode() override;
    
    virtual Point2D getLocation() const override;
    
    //the Bullet moves in a straight line with the direction dictated by the direction of the Ship
    virtual void move() override;
    
private:
    Point2D baseVelocity;
    Point2D bdirection;
    int lifeTime;
    Circle_Coord shape;
    //We will need a line object
};

class Asteroid: public GamePiece{
public:
    /**
     * Requires: nothing
     * Modifies: instance fields
     * Effects: randomize size, start location, and target location of the Asteroid
     */
    Asteroid();
    
    /**
     * Requires: nothing
     * Modifies: instance fields
     * Effects: used in constructor to help make code neater, initializes all instance fields
     */
    void initFields();
    
    //Circle shape
    virtual Shape getShape() const override;
    
    virtual void drawShape() override;
    
    virtual void explode() override;
    
    virtual Point2D getLocation() const override;
    
    virtual void move() override;
    
    bool detectCollision(Bullet &bIn) const;
    
    bool detectCollision(Ship &sIn) const;
private:
    //fields
    Circle_Coord shape;
    Point2D direction;
    
};
class PowerUp: public GamePiece{
public:
    PowerUp();
    void initFields();
    virtual Shape getShape() const override;
    
    virtual void drawShape() override;
    
    virtual void explode() override;
    
    virtual Point2D getLocation() const override;
    
    virtual void move() override;
    
    bool detectCollision(Ship &sIn) const;
    
private:
    Circle_Coord shape;
    Point2D direction;

    
};



#endif /* GamePiece_hpp */

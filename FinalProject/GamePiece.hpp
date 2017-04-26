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


struct Movement_Info{
    Point2D direction;
    int stagnation;
    double speed;
};



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
     * Requires: nothing
     * Modifies: nothing
     * Effects: checks to see if this GamePiece has intersected with another compatible GamePiece
     */
    virtual bool detectCollision(GamePiece *piece) const = 0;
    
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

class Bullet: public GamePiece{
public:
    /**
     * Requires: nothing
     * Modifies: instance fields
     * Effects: set direction of Bullet and set instance fields to default values
     */
    Bullet();
    
    //the shape of the Bullet is a simple line
    virtual Shape getShape() const override;
    
    virtual void drawShape() override;
    
    //There will be no explosion for the bullet, just removal from the screen
    virtual void explode() override;
    
    virtual Point2D getLocation() const override;
    
    //the Bullet moves in a straight line with the direction dictated by the direction of the Ship
    virtual void move() override;
    
    virtual bool detectCollision(GamePiece *piece) const override;
    
private:
    double baseVelocity;
    int lifeTime;
    //We will need a line object
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
    
    void update();
    
    int getTurnStag() const;
    
    void incrementTurnStag();
    
    int getThrustStag() const;
    
    void incrementThrustStag();
    
    void updateDirection();
    
    void keepMoving();
    
    void updateMoves();
    
    //Triangle shape
    virtual Shape getShape() const override;
    
    virtual void drawShape() override;
    
    virtual void explode() override;
    
    virtual Point2D getLocation() const override;
    
    void makeAllMoves();
    
    //movement will be based on user input
    virtual void move() override;
    
    //collision detection will be detected with Asteroids
    virtual bool detectCollision(GamePiece *piece) const override;
    
private:
    Triangle_Coord shape;
    int numLives;
    double thrustV;
    double rotationalV;
    int turn_stag;
    int thrust_stag;
    Point2D direction;
    
    int current_move;
    vector<Movement_Info> moves;
    
    
    
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
    
    virtual bool detectCollision(GamePiece *piece) const override;
    
private:
    //fields
    Circle_Coord shape;
    Point2D direction;
    
};


#endif /* GamePiece_hpp */

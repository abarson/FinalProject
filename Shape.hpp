//
//  Shape.hpp
//  FinalProject
//
//  Created by Adam Barson on 4/19/17.
//  Copyright © 2017 Adam Barson. All rights reserved.
//

#ifndef Shape_hpp
#define Shape_hpp

#include <cmath>
#include <iostream>
using namespace std;


struct color {
    double red;
    double green;
    double blue;
};

class Shape {
public:
    Shape();
    Shape(double a, double p, color f);
    Shape(color f);
    
    virtual double get_area() const;
    virtual double get_perimeter() const;
    virtual color get_fill() const;
    
    virtual void set_color(color c);
    virtual void set_color(double r, double g, double b);
    
    /**
     * Requires: nothing
     * Modifies: nothing (canvas to be drawn on)
     * Effects: draws the shape on the canvas
     */
    virtual void draw() const = 0;
    
protected:
    double area;
    double perimeter;
    
    virtual void calc_area_peri() = 0;
    color fill;
};

class Circle : public Shape {
public:
    Circle();
    Circle(double r);
    Circle(color c);
    Circle(double r, color c);
    
    double get_radius() const;
    
    void set_radius(double r);
    
    // override draw method from Shape
    virtual void draw() const override;
protected:
    double radius;
private:
    virtual void calc_area_peri() override;
};

class Point2D {
public:
    Point2D();
    Point2D(double x_in, double y_in);
    
    double get_x() const;
    double get_y() const;
    
    void set_x(double x_in);
    void set_y(double y_in);
    void set_point(double x_in, double y_in);
    
    void move_point(double x_offset, double y_offset);
    
    static double distance_between(double x1, double y1, double x2, double y2);
    
private:
    double x;
    double y;
};

class Circle_Coord : public Circle {
public:
    Circle_Coord();
    
    Point2D get_center() const;
    int get_center_x() const;
    int get_center_y() const;
    
    void set_center(Point2D center_in);
    void set_center(double x_in, double y_in);
    
    virtual void set_outside_color(double r, double g, double b);
    
    virtual void draw() const override;
    
    void drawTriangle() const;
    
    bool is_overlapping(double x_in, double y_in) const;
    
    bool is_overlapping(const Circle_Coord &c) const;
    
    bool is_overlapping(double x_in1, double y_in1, double x_in2, double y_in2) const;
    
    
private:
    Point2D center;
    color outside;
};



#endif /* Shape_hpp */

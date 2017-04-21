//
//  Shape.cpp
//  FinalProject
//
//  Created by Adam Barson on 4/19/17.
//  Copyright © 2017 Adam Barson. All rights reserved.
//

#include "Shape.hpp"
#include "Space.hpp"
Shape::Shape(): area(0), perimeter(0) {
    fill.red = fill.green = fill.blue = 0;
}

Shape::Shape(double a, double p, color f): area(a), perimeter(p), fill(f) {
}

Shape::Shape(color f) : area(0), perimeter(0), fill(f) {
}

double Shape::get_area() const {
    return area;
}

double Shape::get_perimeter() const {
    return perimeter;
}

color Shape::get_fill() const {
    return fill;
}

void Shape::set_color(color c) {
    fill = c;
}

void Shape::set_color(double r, double g, double b) {
    fill = {r, g, b};
    /*
     fill.red = r;
     fill.green = g;
     fill.blue = b;
     */
}

Circle::Circle() : Shape(), radius(0) {
}

Circle::Circle(double r) : Shape() {
    set_radius(r);
}

Circle::Circle(color c) : Shape(c), radius(0) {
}

Circle::Circle(double r, color c) : Shape(c) {
    set_radius(r);
}

double Circle::get_radius() const {
    return radius;
}

void Circle::set_radius(double r) {
    radius = r;
    if (r < 0) {
        radius = 0;
    }
    calc_area_peri();
}

// This method is to be completed.
void Circle::draw() const {
    cout << "Drawing a circle" << endl;
}

void Circle::calc_area_peri() {
    area = M_PI * radius * radius;
    perimeter = 2.0 * M_PI * radius;
}

Point2D::Point2D() : x(0), y(0) {
}

Point2D::Point2D(double x_in, double y_in) : x(x_in), y(y_in) {
}

double Point2D::get_x() const {
    return x;
}

double Point2D::get_y() const {
    return y;
}

void Point2D::set_x(double x_in) {
    x = x_in;
}

void Point2D::set_y(double y_in) {
    y = y_in;
}

void Point2D::set_point(double x_in, double y_in) {
    x = x_in;
    y = y_in;
}

void Point2D::move_point(double x_offset, double y_offset) {
    x += x_offset;
    y += y_offset;
}

Circle_Coord::Circle_Coord() {
    center = Point2D();
}

Point2D Circle_Coord::get_center() const {
    return center;
}

int Circle_Coord::get_center_x() const {
    return center.get_x();
}

int Circle_Coord::get_center_y() const {
    return center.get_y();
}

void Circle_Coord::set_center(Point2D center_in) {
    center = center_in;
}

void Circle_Coord::set_center(double x_in, double y_in) {
    center = Point2D(x_in, y_in);
}

void Circle_Coord::set_outside_color(double r, double g, double b) {
    outside = {r, g, b};
}

double Point2D::distance_between(double x1, double y1, double x2, double y2){
    return sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
}

bool Circle_Coord::is_overlapping(const Circle_Coord &c) const{
    return (Point2D::distance_between(get_center_x(), get_center_y(), c.get_center_x(), c.get_center_y()) <= radius + c.get_radius());
}

bool Circle_Coord::is_overlapping(double x_in, double y_in) const{
    Circle_Coord temp;
    temp.set_center(x_in, y_in);
    return is_overlapping(temp);
}

bool Circle_Coord::is_overlapping(double x_in1, double y_in1, double x_in2, double y_in2) const{
    // the center y is in between y_in1 and y_in2
    if (x_in1 == x_in2 && ((get_center_y() > y_in2) == (get_center_y() < y_in1) &&
                           (x_in1 >= get_center_x() - radius) && x_in1 <= get_center_x() + radius)){
        return true;
        //horizontal line segment
    } else if (y_in1 == y_in2 && ((get_center_x() > x_in2) == (get_center_x() < x_in1) &&
                                  (y_in1 >= get_center_y() - radius) && y_in1 <= get_center_y() + radius)){
        return true;
    }
    return false;
}

void Circle_Coord::draw() const {
    glBegin(GL_TRIANGLE_FAN);
    // set fill color
    glColor3f(fill.red, fill.green, fill.blue);
    // draw center point
    glVertex2i(get_center_x(), get_center_y());
    // set outside color
    glColor3f(outside.red, outside.green, outside.blue);
    // draw outside points
    for (int i = 0; i <= 360; ++i) {
        glVertex2i(get_center_x() + radius * cos(i * M_PI / 180.0), get_center_y() + radius * sin(i * M_PI / 180.0));
    }
    glEnd();
}

void Circle_Coord::drawTriangle() const {
    glBegin(GL_TRIANGLES);
    //set fill color
    glColor3f(fill.red, fill.green, fill.blue);
    //draw center point
    glVertex2i(get_center_x(), get_center_y());
    //draw triangle
    glVertex2i(300, 300);
    glVertex2i(302,302);
    glVertex2i(295,295);
}

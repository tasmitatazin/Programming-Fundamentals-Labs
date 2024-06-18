//
//  Triangle.cpp
//  Lab5
//
//  Created by Tarek Abdelrahman on 2020-11-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

//  ECE244 Student: Write the implementation of the class Triangle here

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

#include "Shape.h"
#include "Triangle.h"

// Build a Triangle object
Triangle::Triangle(string n, float x1, float y1, float x2, float y2, float x3, float y3) : Shape(n, (x1 + x2 + x3) / 3, (y1 + y2 + y3) / 3)
{
    this->x1 = x1;
    this->y1 = y1;
    this->x2 = x2;
    this->y2 = y2;
    this->x3 = x3;
    this->y3 = y3;
}

Triangle::~Triangle()
{
    // Nothing to do
}

// Accessor
float Triangle::getx1() const
{
    return x1;
}

float Triangle::gety1() const
{
    return y1;
}

float Triangle::getx2() const
{
    return x2;
}

float Triangle::gety2() const
{
    return y2;
}

float Triangle::getx3() const
{
    return x3;
}

float Triangle::gety3() const
{
    return y3;
}

// Mutator
void Triangle::setx1(float x1)
{
    this->x1 = x1;
}

void Triangle::sety1(float y1)
{
    this->y1 = y1;
}

void Triangle::setx2(float x2)
{
    this->x2 = x2;
}

void Triangle::sety2(float y2)
{
    this->y2 = y2;
}

void Triangle::setx3(float x3)
{
    this->x3 = x3;
}

void Triangle::sety3(float y3)
{
    this->y3 = y3;
}

void Triangle::draw() const
{
    // Set floating point printing to fixed point with 2 decimals
    cout << std::fixed;
    cout << std::setprecision(2);

    // Print the information
    cout << "triangle: " << name << " "
         << x_centre << " " << y_centre
         << " " << x1 << " " << y1 << " " << x2 << " " << y2 << " " << x3 << " " << y3 << " " << computeArea()
         << endl;
}

float Triangle::computeArea() const
{
    return (abs((x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2));
}

Shape *Triangle::clone() const
{
    return (new Triangle(*this));
}
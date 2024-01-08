#include "pch.h"
#include "Triangle.h"

// Constructor for Triangle class
Triangle::Triangle(Point3D inP1, Point3D inP2, Point3D inP3) :
    mP1(inP1), mP2(inP2), mP3(inP3)
{

}

// Destructor for Triangle class
Triangle::~Triangle()
{

}

// Getter for point mP1
Point3D Triangle::p1() const
{
    return mP1;
}

// Getter for point mP2
Point3D Triangle::p2() const
{
    return mP2;
}

// Getter for point mP3
Point3D Triangle::p3() const
{
    return mP3;
}

// Setter for point mP1
void Triangle::setP1(Point3D inP1)
{
    mP1 = inP1;
}

// Setter for point mP2
void Triangle::setP2(Point3D inP2)
{
    mP2 = inP2;
}

// Setter for point mP3
void Triangle::setP3(Point3D inP3)
{
    mP3 = inP3;
}

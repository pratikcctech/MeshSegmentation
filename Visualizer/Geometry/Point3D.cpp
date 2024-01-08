#include "pch.h"
#include "Point3D.h"

// Constructor with parameters to set initial values for X, Y, and Z coordinates
Point3D::Point3D(float inX, float inY, float inZ)
    : mX(inX),
    mY(inY),
    mZ(inZ)
{
}

// Default constructor that initializes X, Y, and Z coordinates to zero
Point3D::Point3D()
    : mX(0),
    mY(0),
    mZ(0)
{
}

// Destructor, defaulted to the default implementation
Point3D::~Point3D() = default;

// Getter method for the X coordinate
float Point3D::x() const
{
    return mX;
}

// Getter method for the Y coordinate
float Point3D::y() const
{
    return mY;
}

// Getter method for the Z coordinate
float Point3D::z() const
{
    return mZ;
}

// Setter method for the X coordinate
void Point3D::setX(float x)
{
    mX = x;
}

// Setter method for the Y coordinate
void Point3D::setY(float y)
{
    mY = y;
}

// Setter method for the Z coordinate
void Point3D::setZ(float z)
{
    mZ = z;
}
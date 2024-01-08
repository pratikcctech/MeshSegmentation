#pragma once

// Include the header file for the Geometry API
#include "Geometry.h"

// Class definition for Point3D
class GEOMETRY_API Point3D
{
public:
    // Constructors and Destructor
    Point3D(float inX, float inY, float inZ);
    Point3D();
    ~Point3D();

    // Getter methods for X, Y, and Z coordinates
    float x() const;
    float y() const;
    float z() const;

    // Setter methods for X, Y, and Z coordinates
    void setX(float x);
    void setY(float y);
    void setZ(float z);

private:
    // Private member variables for storing X, Y, and Z coordinates
    float mX;
    float mY;
    float mZ;
};

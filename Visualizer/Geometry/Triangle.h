#pragma once

// Include necessary header files
#include "Point3D.h"

// Declaration of the Triangle class
class GEOMETRY_API Triangle
{
public:
    // Constructor: Initializes the Triangle with three points
    Triangle(Point3D inP1, Point3D inP2, Point3D inP3);

    // Destructor: Cleans up resources associated with the Triangle
    ~Triangle();

    // Getter for point mP1
    Point3D p1() const;

    // Getter for point mP2
    Point3D p2() const;

    // Getter for point mP3
    Point3D p3() const;

    // Setter for point mP1
    void setP1(Point3D inP1);

    // Setter for point mP2
    void setP2(Point3D inP2);

    // Setter for point mP3
    void setP3(Point3D inP3);

private:
    // Private member variables representing the three points of the triangle
    Point3D mP1;
    Point3D mP2;
    Point3D mP3;
};

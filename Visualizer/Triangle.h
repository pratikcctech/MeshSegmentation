#pragma once
#include "Point3D.h"
class Triangle
{
public:
    Triangle(Point3D inP1, Point3D inP2, Point3D inP3);
    ~Triangle();

    Point3D p1() const;
    Point3D p2() const;
    Point3D p3() const;

    void setP1(Point3D inP1);
    void setP2(Point3D inP2);
    void setP3(Point3D inP3);

private:
    Point3D mP1;
    Point3D mP2;
    Point3D mP3;
};


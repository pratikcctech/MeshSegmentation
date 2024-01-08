#pragma once

#include "Triangle.h"
#include "Point3D.h"

class CylindricalSurface
{
public:
	bool areNormalsConsistent(const Point3D& normal1, const Point3D& normal2);
	bool arePointsOnCylinder(const Point3D& p1, const Point3D& p2, const Point3D& p3);
	Point3D crossProduct(const Point3D& v1, const Point3D& v2);
	double distance(const Point3D& p1, const Point3D& p2);
	void cylindricalSurfaceDetection(QVector<GLfloat>& mVertices, QVector<GLfloat>& mColors, std::vector<Triangle>& mTriangles, std::vector<Point3D>& mNormals);
};


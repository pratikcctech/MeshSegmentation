#pragma once
#include "Point3D.h"
#include "Triangle.h"
#include <QVector>

class PlanarSurface
{

public:

	bool areNormalsConsistent(const Point3D& normal1, const Point3D& normal2);
	bool arePointsCoplanar(const Point3D& p1, const Point3D& p2, const Point3D& p3);
	void planarSurfaceDetection(QVector<GLfloat>& mVertices, QVector<GLfloat>& mColors, std::vector<Triangle>& mTriangles, std::vector<Point3D>& mNormals);
};


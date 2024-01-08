#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <iostream>
#include "Triangle.h"
#include "Point3D.h"
class Reader
{
public:
	void readSTL(QVector<GLfloat>& mVertices, QVector<GLfloat>& mColors, std::string mFileName, std::vector<Triangle>& mTriangles, std::vector<Point3D>& mNormals);
};


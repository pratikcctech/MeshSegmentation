#include "stdafx.h"
#include "Triangle.h"

Triangle::Triangle(Point3D inP1, Point3D inP2, Point3D inP3) :
	mP1(inP1), mP2(inP2), mP3(inP3)
{

}

Triangle::~Triangle()
{

}

Point3D Triangle::p1() const
{
	return mP1;
}

Point3D Triangle::p2() const
{
	return mP2;
}

Point3D Triangle::p3() const
{
	return mP3;
}


void Triangle::setP1(Point3D inP1)
{
	mP1 = inP1;
}


void Triangle::setP2(Point3D inP2)
{
	mP2 = inP2;
}

void Triangle::setP3(Point3D inP3)
{
	mP3 = inP3;
}
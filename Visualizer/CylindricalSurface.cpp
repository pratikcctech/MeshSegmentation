#include "stdafx.h"
#include "CylindricalSurface.h"



//the function to create the cylindrical surfaces
void CylindricalSurface::cylindricalSurfaceDetection(QVector<GLfloat>& mVertices, QVector<GLfloat>& mColors, std::vector<Triangle>& mTriangles, std::vector<Point3D>& mNormals)
{


    for (int i = 0; i < mTriangles.size(); i++)
    {
        for (int j = i + 1; j < mTriangles.size(); j++)
        {
            // Assuming you have a function areNormalsConsistent for checking normals consistency
            if (areNormalsConsistent(mNormals[i], mNormals[j]))
            {
                // Assuming you have a function arePointsOnCylinder for checking if points lie on a cylinder
                if (arePointsOnCylinder(mTriangles[i].p1(), mTriangles[i].p2(), mTriangles[i].p3()))
                {
                    mVertices << mTriangles[i].p1().x() * 0.1 << mTriangles[i].p1().y() * 0.1 << mTriangles[i].p1().z() * 0.1;
                    mVertices << mTriangles[i].p2().x() * 0.1 << mTriangles[i].p2().y() * 0.1 << mTriangles[i].p2().z() * 0.1;
                    mVertices << mTriangles[i].p3().x() * 0.1 << mTriangles[i].p3().y() * 0.1 << mTriangles[i].p3().x() * 0.1;

                    mVertices << mTriangles[j].p1().x() * 0.1 << mTriangles[j].p1().y() * 0.1 << mTriangles[j].p1().z() * 0.1;
                    mVertices << mTriangles[j].p2().x() * 0.1 << mTriangles[j].p2().y() * 0.1 << mTriangles[j].p2().z() * 0.1;
                    mVertices << mTriangles[j].p3().x() * 0.1 << mTriangles[j].p3().y() * 0.1 << mTriangles[j].p3().x() * 0.1;

                    mColors << 0.0 << 1.0 << 0.0; // Assuming green color for cylindrical surfaces
                    mColors << 0.0 << 1.0 << 0.0;
                    mColors << 0.0 << 1.0 << 0.0;

                    mColors << 0.0 << 1.0 << 0.0;
                    mColors << 0.0 << 1.0 << 0.0;
                    mColors << 0.0 << 1.0 << 0.0;


                }
            }
        }
    }

}

// Function to check if the normal vectors of two triangles are consistent
bool CylindricalSurface::areNormalsConsistent(const Point3D& normal1, const Point3D& normal2) {
    // Define a tolerance threshold to handle numerical precision issues
    double tolerance = 1e-6;

    // Check if the angle between the normals is very close to 0 degrees (or pi radians)
    double dotProduct = normal1.x() * normal2.x() + normal1.y() * normal2.y() + normal1.z() * normal2.z();
    double magnitudesProduct = std::sqrt(normal1.x() * normal1.x() + normal1.y() * normal1.y() + normal1.z() * normal1.z()) *
        std::sqrt(normal2.x() * normal2.x() + normal2.y() * normal2.y() + normal2.z() * normal2.z());

    // Check if the cosine of the angle is close to 1
    return std::abs(dotProduct / magnitudesProduct - 1.0) < tolerance;
}






// Function to check if three points are on a cylindrical surface
bool CylindricalSurface::arePointsOnCylinder(const Point3D& p1, const Point3D& p2, const Point3D& p3)
{
    // Calculate vectors representing edges of the triangle
    Point3D edge1(p2.x() - p1.x(), p2.y() - p1.y(), p2.z() - p1.z());
    Point3D edge2(p3.x() - p1.x(), p3.y() - p1.y(), p3.z() - p1.z());

    // Calculate cross product to find the normal vector of the triangle
    Point3D normal = crossProduct(edge1, edge2);

    // Assuming the cylinder is aligned with the Z-axis, check if the normal vector is approximately (0, 0, 1)
    double tolerance = 1e-6;
    if (std::abs(normal.x()) < tolerance && std::abs(normal.y()) < tolerance && std::abs(normal.z() - 1.0) < tolerance)
    {
        // Check if the points form a circular pattern in the XY plane
        double radius = 1.0; // Set your desired radius
        Point3D center((p1.x() + p2.x() + p3.x()) / 3.0, (p1.y() + p2.y() + p3.y()) / 3.0, (p1.z() + p2.z() + p3.z()) / 3.0);


        // Check if each point is at the specified radius from the center
        if (std::abs(distance(center, p1) - radius) < tolerance &&
            std::abs(distance(center, p2) - radius) < tolerance &&
            std::abs(distance(center, p3) - radius) < tolerance)
        {
            return true;
        }
    }

    return false;
}

// Function to calculate the cross product of two vectors
Point3D CylindricalSurface::crossProduct(const Point3D& v1, const Point3D& v2)
{
    Point3D result;
    result.setX(v1.y() * v2.z() - v1.z() * v2.y());
    result.setY(v1.z() * v2.x() - v1.x() * v2.z());
    result.setZ(v1.x() * v2.y() - v1.y() * v2.x());
    return result;
}

// Function to calculate the distance between two points
double CylindricalSurface::distance(const Point3D& p1, const Point3D& p2)
{
    return std::sqrt(std::pow(p2.x() - p1.x(), 2) + std::pow(p2.y() - p1.y(), 2) + std::pow(p2.z() - p1.z(), 2));
}
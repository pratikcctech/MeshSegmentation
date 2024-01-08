#include "stdafx.h"
#include "PlanarSurface.h"


// Function to check if the normal vectors of two triangles are consistent
bool PlanarSurface::areNormalsConsistent(const Point3D& normal1, const Point3D& normal2) {
    // Define a tolerance threshold to handle numerical precision issues
    double tolerance = 1e-6;

    // Check if the angle between the normals is very close to 0 degrees (or pi radians)
    double dotProduct = normal1.x() * normal2.x() + normal1.y() * normal2.y() + normal1.z() * normal2.z();
    double magnitudesProduct = std::sqrt(normal1.x() * normal1.x() + normal1.y() * normal1.y() + normal1.z() * normal1.z()) *
        std::sqrt(normal2.x() * normal2.x() + normal2.y() * normal2.y() + normal2.z() * normal2.z());

    // Check if the cosine of the angle is close to 1
    return std::abs(dotProduct / magnitudesProduct - 1.0) < tolerance;
}



//
//// Function to check if three points are coplanar
bool  PlanarSurface::arePointsCoplanar(const Point3D& p1, const Point3D& p2, const Point3D& p3) {
    // Equation of a plane: Ax + By + Cz + D = 0
    // Calculate coefficients A, B, C, and D using the given points
    double A = (p2.y() - p1.y()) * (p3.z() - p1.z()) - (p3.y() - p1.y()) * (p2.z() - p1.z());
    double B = (p2.z() - p1.z()) * (p3.x() - p1.x()) - (p3.z() - p1.z()) * (p2.x() - p1.x());
    double C = (p2.x() - p1.x()) * (p3.y() - p1.y()) - (p3.x() - p1.x()) * (p2.y() - p1.y());
    double D = -p1.x() * A - p1.y() * B - p1.z() * C;

    // Define a tolerance threshold to handle numerical precision issues
    double tolerance = 1e-6;

    // Check if all points satisfy the plane equation within the tolerance
    return std::abs(A * p1.x() + B * p1.y() + C * p1.z() + D) < tolerance &&
        std::abs(A * p2.x() + B * p2.y() + C * p2.z() + D) < tolerance &&
        std::abs(A * p3.x() + B * p3.y() + C * p3.z() + D) < tolerance;
}

// Slot for performing planar surface detection
void PlanarSurface::planarSurfaceDetection(QVector<GLfloat>& mVertices,QVector<GLfloat>& mColors , std::vector<Triangle>& mTriangles,std::vector<Point3D>& mNormals)
{
    int count = 0;

    for (int i = 0; i < mTriangles.size(); i++)
    {

        for (int j = i + 1; j < mTriangles.size(); j++)
        {

            //checking condition for the planar surface detection
            if (areNormalsConsistent(mNormals[i], mNormals[j]) && arePointsCoplanar(mTriangles[i].p1(), mTriangles[i].p2(), mTriangles[i].p3()))
            {
                mVertices << mTriangles[i].p1().x() * 0.1 << mTriangles[i].p1().y() * 0.1 << mTriangles[i].p1().z() * 0.1;
                mVertices << mTriangles[i].p2().x() * 0.1 << mTriangles[i].p2().y() * 0.1 << mTriangles[i].p2().z() * 0.1;
                mVertices << mTriangles[i].p3().x() * 0.1 << mTriangles[i].p3().y() * 0.1 << mTriangles[i].p3().x() * 0.1;
                mVertices << mTriangles[i].p1().x() * 0.1 << mTriangles[i].p1().y() * 0.1 << mTriangles[i].p1().z() * 0.1;
                mVertices << mTriangles[j].p1().x() * 0.1 << mTriangles[j].p1().y() * 0.1 << mTriangles[j].p1().z() * 0.1;
                mVertices << mTriangles[j].p2().x() * 0.1 << mTriangles[j].p2().y() * 0.1 << mTriangles[j].p2().z() * 0.1;
                mVertices << mTriangles[j].p3().x() * 0.1 << mTriangles[j].p3().y() * 0.1 << mTriangles[j].p3().x() * 0.1;
                mVertices << mTriangles[j].p1().x() * 0.1 << mTriangles[j].p1().y() * 0.1 << mTriangles[j].p1().z() * 0.1;
                mColors << 1.0 << 1.0 << 0.0;
                mColors << 1.0 << 1.0 << 0.0;
                mColors << 1.0 << 1.0 << 0.0;
                mColors << 1.0 << 1.0 << 0.0;
                mColors << 1.0 << 1.0 << 0.0;
                mColors << 1.0 << 1.0 << 0.0;
                mColors << 1.0 << 1.0 << 0.0;
                mColors << 1.0 << 1.0 << 0.0;
                count++;

            }


        }
    }

    

}
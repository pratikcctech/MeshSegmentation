#include "stdafx.h"
#include "Visualizer.h"
#include "OpenGLWindow.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cmath>
#include <string>
#include <set>
using namespace std;


// Constructor for Visualizer class
Visualizer::Visualizer(QWindow* parent) : QMainWindow(nullptr)
{
    setupUi();
    
    // Connect buttons to their corresponding slots
    connect(pushButton_3, &QPushButton::clicked, this, &Visualizer::browseFile);
    connect(pushButton_4, &QPushButton::clicked, this, &Visualizer::readSTL);
    connect(pushButton_2, &QPushButton::clicked, this, &Visualizer::planarSurfaceDetection);
    connect(pushButton, &QPushButton::clicked, this, &Visualizer::cylindricalSurfaceDetection);
}

Visualizer::~Visualizer()
{}


// Method to set up the user interface
void Visualizer::setupUi() {
    resize(800, 600);


    centralWidget = new QWidget(this);
    centralWidget->setObjectName("centralWidget");
    gridLayoutWidget = new QWidget(centralWidget);
    gridLayoutWidget->setObjectName("gridLayoutWidget");
    gridLayoutWidget->setGeometry(QRect(10, 10, 1571, 821));
    gridLayout = new QGridLayout(gridLayoutWidget);
    gridLayout->setSpacing(6);
    gridLayout->setContentsMargins(11, 11, 11, 11);
    gridLayout->setObjectName("gridLayout");
    gridLayout->setContentsMargins(0, 0, 0, 0);
    label_3 = new QLabel(gridLayoutWidget);
    label_3->setObjectName("label_3");

    gridLayout->addWidget(label_3, 0, 0, 1, 1);

    pushButton = new QPushButton(gridLayoutWidget);
    pushButton->setObjectName("pushButton");
    pushButton->setText("Cylindrical Surface");

    gridLayout->addWidget(pushButton, 8, 4, 1, 1);

    label_9 = new QLabel(gridLayoutWidget);
    label_9->setObjectName("label_9");

    gridLayout->addWidget(label_9, 4, 2, 1, 1);

    label_6 = new QLabel(gridLayoutWidget);
    label_6->setObjectName("label_6");

    gridLayout->addWidget(label_6, 6, 0, 1, 1);

    label_7 = new QLabel(gridLayoutWidget);
    label_7->setObjectName("label_7");

    gridLayout->addWidget(label_7, 4, 0, 1, 1);

    label = new QLabel(gridLayoutWidget);
    label->setObjectName("label");

    gridLayout->addWidget(label, 3, 0, 1, 1);

    label_5 = new QLabel(gridLayoutWidget);
    label_5->setObjectName("label_5");

    gridLayout->addWidget(label_5, 7, 0, 1, 1);

    label_8 = new QLabel(gridLayoutWidget);
    label_8->setObjectName("label_8");

    gridLayout->addWidget(label_8, 5, 0, 1, 1);
    pushButton_4 = new QPushButton(gridLayoutWidget);
    pushButton_4->setObjectName("pushButton_2");
    pushButton_4->setText("render STL");

    gridLayout->addWidget(pushButton_4, 8, 2, 1, 1);


    pushButton_2 = new QPushButton(gridLayoutWidget);
    pushButton_2->setObjectName("pushButton_2");
    pushButton_2->setText("planar Surface");

    gridLayout->addWidget(pushButton_2, 8, 3, 1, 1);

    label_4 = new QLabel(gridLayoutWidget);
    label_4->setObjectName("label_4");

    gridLayout->addWidget(label_4, 2, 3, 1, 1);

    label_10 = new QLabel(gridLayoutWidget);
    label_10->setObjectName("label_10");

    gridLayout->addWidget(label_10, 3, 1, 1, 1);

    label_2 = new QLabel(gridLayoutWidget);
    label_2->setObjectName("label_2");

    gridLayout->addWidget(label_2, 8, 5, 1, 1);

    pushButton_3 = new QPushButton(gridLayoutWidget);
    pushButton_3->setObjectName("pushButton_3");
    pushButton_3->setText("Browse STL");

    gridLayout->addWidget(pushButton_3, 8, 1, 1, 1);

    mRenderer =  new OpenGLWindow ( QColor(0, 0, 0), centralWidget);
    mRenderer->setObjectName("openGLWidget");

    gridLayout->addWidget(mRenderer, 0, 1, 7, 5);

    setCentralWidget(centralWidget);
    menuBar = new QMenuBar(this);
    menuBar->setObjectName("menuBar");
    menuBar->setGeometry(QRect(0, 0, 1602, 22));
    setMenuBar(menuBar);
    mainToolBar = new QToolBar(this);
    mainToolBar->setObjectName("mainToolBar");
    addToolBar(Qt::TopToolBarArea, mainToolBar);
    statusBar = new QStatusBar(this);
    statusBar->setObjectName("statusBar");
    setStatusBar(statusBar);
}


// Slot for browsing an STL file
void Visualizer::browseFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open STL File"), "", tr("STL Files(*.stl);; All Files(*)"));
    if (!fileName.isEmpty())
    {
        mFileName = fileName.toStdString();
    }
}


 
//slot for reading the stl file 
void Visualizer::readSTL()
{
    mTriangles.clear();
    mNormals.clear();
    std::string filePath = mFileName;

    std::ifstream dataFile;
    dataFile.open(filePath);
    if (!dataFile.is_open())
    {
        std::cout << "File not exist" << std::endl;
        return;
    }

    std::string line;
   
    //std::vectorriangle
    while (std::getline(dataFile, line))
    {
        if (line.find("facet normal") != std::string::npos)
        {
            std::istringstream iss(line);
            std::string token;
            double nx, ny, nz;
            iss >> token >> token >> nx >> ny >> nz;
            Point3D normal(nx, ny, nz);
            mNormals.push_back(normal);
            
        }
        if (line.find("vertex") != std::string::npos)
        {
            std::istringstream iss(line);
            std::string token;
            double x, y, z;
            iss >> token >> x >> y >> z;
            mVertices << x * 0.1 << y * 0.1 << z * 0.1;
            mColors << 1.0f << 1.0f << 1.0f;
            Point3D p1(x, y, z);

            std::getline(dataFile, line);
            std::istringstream iss1(line);
            std::string token1;
            double x1, y1, z1;
            iss1 >> token1 >> x1 >> y1 >> z1;
            
            mVertices << x1 * 0.1 << y1 * 0.1 << z1 * 0.1;
            mColors << 1.0f << 1.0f << 1.0f;
            Point3D p2(x1, y1, z1);
            
            std::getline(dataFile, line);
            std::istringstream iss2(line);
            std::string token2;
            double x2, y2, z2;
            iss2 >> token2 >> x2 >> y2 >> z2;
            mVertices << x2 * 0.1 << y2 * 0.1 << z2 * 0.1;
            mColors << 1.0f << 1.0f << 1.0f;
            Point3D p3(x2, y2, z2);
            
            Triangle t1(p1, p2, p3);
            mTriangles.push_back(t1);

            mVertices << x * 0.1 << y * 0.1 << z * 0.1;
            mColors << 1.0f << 1.0f << 1.0f;
            
        }

    }
    mRenderer->setVectorOfLines(mVertices);
    mRenderer->setColorOfLines(mColors);
    mRenderer->updateData(mVertices, mColors);
    mVertices.clear();
    mColors.clear();
    dataFile.close();
    
    

   
}






// Slot for performing planar surface detection
void Visualizer::planarSurfaceDetection()
{
    int count = 0;
   
    for (int i = 0; i < mTriangles.size(); i++)
    {

        for (int j = i+1; j < mTriangles.size(); j++)
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

    mRenderer->setVectorOfLines(mVertices);
    mRenderer->setColorOfLines(mColors);
    mRenderer->updateData(mVertices, mColors);
    mVertices.clear();
    mColors.clear();

}







// Function to check if the normal vectors of two triangles are consistent
bool Visualizer:: areNormalsConsistent(const Point3D& normal1, const Point3D& normal2) {
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
bool Visualizer::arePointsCoplanar(const Point3D& p1, const Point3D& p2, const Point3D& p3) {
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

void Visualizer::zoomSlider(int value)
{
    GLfloat zoomFactor = 0.5 + (value / 100.0) * 1.0;
    mRenderer->setZoomFactor(zoomFactor);
}







void Visualizer::cylindricalSurfaceDetection()
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

    mRenderer->setVectorOfLines(mVertices);
    mRenderer->setColorOfLines(mColors);
    mRenderer->updateData(mVertices, mColors);
    mVertices.clear();
    mColors.clear();
}









// Function to check if three points are on a cylindrical surface
bool Visualizer::arePointsOnCylinder(const Point3D& p1, const Point3D& p2, const Point3D& p3)
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
Point3D Visualizer::crossProduct(const Point3D& v1, const Point3D& v2)
{
    Point3D result;
    result.setX(v1.y() * v2.z() - v1.z() * v2.y());
    result.setY(v1.z() * v2.x() - v1.x() * v2.z());
    result.setZ(v1.x() * v2.y() - v1.y() * v2.x());
    return result;
}

// Function to calculate the distance between two points
double Visualizer::distance(const Point3D& p1, const Point3D& p2)
{
    return std::sqrt(std::pow(p2.x() - p1.x(), 2) + std::pow(p2.y() - p1.y(), 2) + std::pow(p2.z() - p1.z(), 2));
}
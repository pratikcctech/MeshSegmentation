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
    connect(mPushButton_3, &QPushButton::clicked, this, &Visualizer::browseFile);
    connect(mPushButton_4, &QPushButton::clicked, this, &Visualizer::readSTL);
    connect(mPushButton_2, &QPushButton::clicked, this, &Visualizer::planarSurfaceDetection);
    connect(mPushButton, &QPushButton::clicked, this, &Visualizer::cylindricalSurfaceDetection);
}

Visualizer::~Visualizer()
{}


// Method to set up the user interface
void Visualizer::setupUi() {
    resize(800, 600);


    mCentralWidget = new QWidget(this);
    mCentralWidget->setObjectName("mCentralWidget");
    mGridLayoutWidget = new QWidget(mCentralWidget);
    mGridLayoutWidget->setObjectName("gridLayoutWidget");
    mGridLayoutWidget->setGeometry(QRect(10, 10, 1571, 821));
    mGridLayout = new QGridLayout(mGridLayoutWidget);
    mGridLayout->setSpacing(6);
    mGridLayout->setContentsMargins(11, 11, 11, 11);
    mGridLayout->setObjectName("gridLayout");
    mGridLayout->setContentsMargins(0, 0, 0, 0);
    label_3 = new QLabel(mGridLayoutWidget);
    label_3->setObjectName("label_3");

    mGridLayout->addWidget(label_3, 0, 0, 1, 1);

    mPushButton = new QPushButton(mGridLayoutWidget);
    mPushButton->setObjectName("pushButton");
    mPushButton->setText("Cylindrical Surface");

    mGridLayout->addWidget(mPushButton, 8, 4, 1, 1);

    label_9 = new QLabel(mGridLayoutWidget);
    label_9->setObjectName("label_9");

    mGridLayout->addWidget(label_9, 4, 2, 1, 1);

    label_6 = new QLabel(mGridLayoutWidget);
    label_6->setObjectName("label_6");

    mGridLayout->addWidget(label_6, 6, 0, 1, 1);

    label_7 = new QLabel(mGridLayoutWidget);
    label_7->setObjectName("label_7");

    mGridLayout->addWidget(label_7, 4, 0, 1, 1);

    label = new QLabel(mGridLayoutWidget);
    label->setObjectName("label");

    mGridLayout->addWidget(label, 3, 0, 1, 1);

    label_5 = new QLabel(mGridLayoutWidget);
    label_5->setObjectName("label_5");

    mGridLayout->addWidget(label_5, 7, 0, 1, 1);

    label_8 = new QLabel(mGridLayoutWidget);
    label_8->setObjectName("label_8");

    mGridLayout->addWidget(label_8, 5, 0, 1, 1);
    mPushButton_4 = new QPushButton(mGridLayoutWidget);
    mPushButton_4->setObjectName("pushButton_2");
    mPushButton_4->setText("render STL");

    mGridLayout->addWidget(mPushButton_4, 8, 2, 1, 1);


    mPushButton_2 = new QPushButton(mGridLayoutWidget);
    mPushButton_2->setObjectName("pushButton_2");
    mPushButton_2->setText("planar Surface");

    mGridLayout->addWidget(mPushButton_2, 8, 3, 1, 1);

    label_4 = new QLabel(mGridLayoutWidget);
    label_4->setObjectName("label_4");

    mGridLayout->addWidget(label_4, 2, 3, 1, 1);

    label_10 = new QLabel(mGridLayoutWidget);
    label_10->setObjectName("label_10");

    mGridLayout->addWidget(label_10, 3, 1, 1, 1);

    label_2 = new QLabel(mGridLayoutWidget);
    label_2->setObjectName("label_2");

    mGridLayout->addWidget(label_2, 8, 5, 1, 1);

    mPushButton_3 = new QPushButton(mGridLayoutWidget);
    mPushButton_3->setObjectName("pushButton_3");
    mPushButton_3->setText("Browse STL");

    mGridLayout->addWidget(mPushButton_3, 8, 1, 1, 1);

    mRenderer =  new OpenGLWindow ( QColor(0, 0, 0), mCentralWidget);
    mRenderer->setObjectName("openGLWidget");

    mGridLayout->addWidget(mRenderer, 0, 1, 7, 5);

    setCentralWidget(mCentralWidget);
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
    
   
    PlanarSurface plane;
    plane.planarSurfaceDetection(mVertices, mColors, mTriangles, mNormals);

    mRenderer->setVectorOfLines(mVertices);
    mRenderer->setColorOfLines(mColors);
    mRenderer->updateData(mVertices, mColors);
    mVertices.clear();
    mColors.clear();

}


//the slot to updadet the zoomfactor of the points
void Visualizer::zoomSlider(int value)
{
    GLfloat zoomFactor = 0.5 + (value / 100.0) * 1.0;
    mRenderer->setZoomFactor(zoomFactor);
}


//the function to create the cylindrical surfaces
void Visualizer::cylindricalSurfaceDetection()
{
    

    CylindricalSurface cylinder;
    cylinder.cylindricalSurfaceDetection(mVertices, mColors, mTriangles, mNormals);

    mRenderer->setVectorOfLines(mVertices);
    mRenderer->setColorOfLines(mColors);
    mRenderer->updateData(mVertices, mColors);
    mVertices.clear();
    mColors.clear();
}



#pragma once

#include <QtWidgets/QMainWindow>
#include "Visualizer.h"
#include "OpenGLWindow.h"
#include <Qvector>
#include "Triangle.h"
#include "PlanarSurface.h"
#include "CylindricalSurface.h"


class OpenGLWindow;

class Visualizer : public QMainWindow {
    Q_OBJECT

public:
    Visualizer(QWindow* parent = nullptr);
    ~Visualizer();
    void zoomSlider(int);
    bool areNormalsConsistent(const Point3D& normal1, const Point3D& normal2);
    bool arePointsCoplanar(const Point3D& p1, const Point3D& p2, const Point3D& p3);
    Point3D crossProduct(const Point3D& a, const Point3D& b);
    Point3D subtract(const Point3D& a, const Point3D& b);
    float dotProduct(const Point3D& a, const Point3D& b);
    bool areTrianglesCoplanar(const Triangle& triangle1, const Triangle& triangle2);
    bool arePointsOnCylinder(const Point3D& p1, const Point3D& p2, const Point3D& p3);
    double distance(const Point3D& p1, const Point3D& p2);



    QWidget* mCentralWidget;
    QWidget* mGridLayoutWidget;
    QGridLayout* mGridLayout;
    QLabel* label_3;
    QLabel* label;
    QPushButton* mPushButton;
    QLabel* label_7;
    QLabel* label_6;
    QLabel* label_5;
    
    QPushButton* mPushButton_2;
    QLabel* label_4;
    QLabel* label_2;
    QPushButton* mPushButton_3;
    QPushButton* mPushButton_4;

    QLabel* label_8;
    QLabel* label_10;
    QLabel* label_9;
    QMenuBar* menuBar;
    QToolBar* mainToolBar;
    QStatusBar* statusBar;
    std::string mFileName;

private:
    void setupUi();

private slots:
    void readSTL();
    void browseFile();
    void planarSurfaceDetection();
    void cylindricalSurfaceDetection();

private:
   
    OpenGLWindow* mRenderer;
    QPushButton* mpushButton;
    QPushButton* mpushButtonRead;
    QVector<GLfloat>mVertices;
    QVector<GLfloat>mColors;
    std::vector<Triangle> mTriangles;
    std::vector<Point3D> mNormals;
    
};

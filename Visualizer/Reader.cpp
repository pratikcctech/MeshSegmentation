#include "stdafx.h"
#include "Reader.h"


void Reader::readSTL(QVector<GLfloat>& mVertices, QVector<GLfloat>& mColors, std::string mFileName, std::vector<Triangle>& mTriangles, std::vector<Point3D>& mNormals)
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
   
    dataFile.close();




}
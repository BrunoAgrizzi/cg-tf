#ifndef CUBE_H
#define CUBE_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

class Cube{
private:
    float scaleX, scaleY, scaleZ;
    float transX, transY, transZ;
    float rotationAngle;
public:

    // default constructor
    Cube();

    // sets the scale factor for x, y and z for the cube object
    void setScale(float sx, float sy, float sz);

    // sets the coordinates of translation
    void setTranslation(float tx, float ty, float tz);

    void setRotation(float angle);

    // x, y: cube's center will be drawn at these positions
    void draw();
};

#endif

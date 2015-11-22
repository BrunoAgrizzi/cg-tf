#ifndef CUBE_H
#define CUBE_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <GL/glut.h>

using namespace std;

class Cube{
private:
    GLfloat normals[6][3], vertexes[8][3];
    GLint  faces[6][4];
    float scaleX, scaleY, scaleZ;
    float transX, transY, transZ;
    float rotationAxis[3];
    float rotationAngle;
    float rotationAngleY;
    float materialColor[4];
    GLuint texture;
    char* texturePath;
public:

    // default constructor
    Cube();

    // sets the scale factor for x, y and z for the cube object
    void setScale(float sx, float sy, float sz);

    // sets the coordinates of translation
    void setTranslation(float tx, float ty, float tz);

    void setRotation(float angle);
    float getRotation();
    void setRotationY(float angle);
    float getRotationY();

    void setColor(float r, float g, float b, float q);

    GLuint getTexture();

    void setTexture(GLuint tex);

    void setTexturePath(char* path);

    void setRotationAxis(float x, float y, float z);

    // x, y: cube's center will be drawn at these positions
    void draw();

    void drawBC();
};

#endif

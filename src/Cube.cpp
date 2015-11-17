#include "Cube.h"
#include <string>
#include <math.h>
#include <GL/glut.h>
// #include "Utils.h"

using namespace std;

Cube::Cube(){}

void Cube::draw(){
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, this->materialColor);
    glPushMatrix();
        glTranslatef(this->transX, this->transY, this->transZ);
        glScalef(this->scaleX, this->scaleY, this->scaleZ);
        glutSolidCube(1.0);
    glPopMatrix();
}

void Cube::setScale(float sx, float sy, float sz){
    this->scaleX = sx;
    this->scaleY = sy;
    this->scaleZ = sz;
}

void Cube::setTranslation(float tx, float ty, float tz){
    this->transX = tx;
    this->transY = ty;
    this->transZ = tz;
}

void Cube::setRotation(float angle){
    this->rotationAngle = angle;
}

void Cube::setColor(float r, float g, float b, float q){
    this->materialColor[0] = r;
    this->materialColor[1] = g;
    this->materialColor[2] = b;
    this->materialColor[4] = q;
}

#include "Cube.h"
#include <string>
#include <math.h>
#include <GL/glut.h>
// #include "Utils.h"

using namespace std;

Cube::Cube(){}

void Cube::draw(){
    glPushMatrix();
        // TODO: make color dynamic
        glColor3f(1,0,0);
        glScalef(this->scaleX, this->scaleY, this->scaleZ);
        glTranslatef(this->transX, this->transY, this->transZ);
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

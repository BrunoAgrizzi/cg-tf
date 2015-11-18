#include "Cube.h"
#include <string>
#include <math.h>
#include <GL/glut.h>
// #include "Utils.h"

using namespace std;

Cube::Cube(){
    vertexes[0][0] = vertexes[1][0] = vertexes[2][0] = vertexes[3][0] = -1;
    vertexes[4][0] = vertexes[5][0] = vertexes[6][0] = vertexes[7][0] = 1;
    vertexes[0][1] = vertexes[1][1] = vertexes[4][1] = vertexes[5][1] = -1;
    vertexes[2][1] = vertexes[3][1] = vertexes[6][1] = vertexes[7][1] = 1;
    vertexes[0][2] = vertexes[3][2] = vertexes[4][2] = vertexes[7][2] = 1;
    vertexes[1][2] = vertexes[2][2] = vertexes[5][2] = vertexes[6][2] = -1;

    normals[0][0] = -1; normals[0][1] =  0; normals[0][2] = 0.0;
    normals[1][0] =  0; normals[0][1] =  1; normals[1][2] = 0.0;
    normals[2][0] =  1; normals[0][2] =  0; normals[2][2] = 0.0;
    normals[3][0] =  0; normals[0][3] = -1; normals[3][2] = 0.0;
    normals[4][0] =  0; normals[0][4] =  0; normals[4][2] = 1;
    normals[5][0] =  0; normals[0][5] =  0; normals[5][2] = -1;

    faces[0][0] = 0; faces[0][1] = 1; faces[0][2]= 2; faces[0][3] = 3;
    faces[1][0] = 3; faces[1][1] = 2; faces[1][2]= 6; faces[1][3] = 7;
    faces[2][0] = 7; faces[2][1] = 6; faces[2][2]= 5; faces[2][3] = 4;
    faces[3][0] = 4; faces[3][1] = 5; faces[3][2]= 1; faces[3][3] = 0;
    faces[4][0] = 5; faces[4][1] = 6; faces[4][2]= 2; faces[4][3] = 1;
    faces[5][0] = 7; faces[5][1] = 4; faces[5][2]= 0; faces[5][3] = 3;
}

void Cube::draw(){
    int i;
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, this->materialColor);
    glPushMatrix();
        glTranslatef(this->transX, this->transY, this->transZ);
        glRotatef(this->rotationAngle, 0,1,0);
        glScalef(this->scaleX, this->scaleY, this->scaleZ);
    for (i = 0; i < 6; i++){
        glBegin(GL_QUADS);
            glNormal3fv(&normals[i][0]);
            glVertex3fv(&vertexes[faces[i][0]][0]);
            glVertex3fv(&vertexes[faces[i][1]][0]);
            glVertex3fv(&vertexes[faces[i][2]][0]);
            glVertex3fv(&vertexes[faces[i][3]][0]);
        glEnd();
    }
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

#include "Cube.h"
#include <string>
#include <math.h>
#include <GL/glut.h>
// #include "Utils.h"
#include "imageloader.h"
using namespace std;


GLuint LoadTextureRAW(const char * filename);

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

    rotationAxis[0] = 0;
    rotationAxis[1] = 0;
    rotationAxis[2] = 0;
}

void Cube::draw(){
    int i;
    GLfloat materialEmission[] = { 1.0, 1.0, 1.0, 1};
    GLfloat materialColorA[] = { 0.2, 0.2, 0.2, 1};
    GLfloat materialColorD[] = { 1.0, 1.0, 1.0, 1};
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1};
    GLfloat mat_shininess[] = { 100.0 };
    glColor3f(1,1,1);

    glMaterialfv(GL_FRONT, GL_EMISSION, materialEmission);
    glMaterialfv(GL_FRONT, GL_AMBIENT, materialColorA);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, materialColorD);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);


    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT  );//X
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );//Y


    //glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, this->materialColor);
    glBindTexture (GL_TEXTURE_2D, this->texture);

    glPushMatrix();
        glTranslatef(this->transX, this->transY, this->transZ);
        if(rotationAxis[0] == 0 && rotationAxis[1] == 0 && rotationAxis[2] == 0){
            glRotatef(this->rotationAngle, 0,1,0);
        }else{
            glRotatef(this->rotationAngle, rotationAxis[0],rotationAxis[1], rotationAxis[2]);
        }
            glScalef(this->scaleX, this->scaleY, this->scaleZ);

          for (i = 0; i < 6; i++){
              glBegin(GL_QUADS);
                  glNormal3fv(&normals[i][0]);
                  glTexCoord2f (0, 0);
                  glVertex3fv(&vertexes[faces[i][0]][0]);
                  glTexCoord2f (0, 1);
                  glVertex3fv(&vertexes[faces[i][1]][0]);
                  glTexCoord2f (1, 1);
                  glVertex3fv(&vertexes[faces[i][2]][0]);
                  glTexCoord2f (1, 0);
                  glVertex3fv(&vertexes[faces[i][3]][0]);
              glEnd();
          }
    glPopMatrix();

}

void Cube::drawBC(){
    int i;
    GLfloat materialEmission[] = { 1.0, 1.0, 1.0, 1};
    GLfloat materialColorA[] = { 0.2, 0.2, 0.2, 1};
    GLfloat materialColorD[] = { 1.0, 1.0, 1.0, 1};
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1};
    GLfloat mat_shininess[] = { 100.0 };
    glColor3f(1,1,1);

    glMaterialfv(GL_FRONT, GL_EMISSION, materialEmission);
    glMaterialfv(GL_FRONT, GL_AMBIENT, materialColorA);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, materialColorD);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);


    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT  );//X
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );//Y


    //glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, this->materialColor);
    glBindTexture (GL_TEXTURE_2D, this->texture);

    glPushMatrix();
        glTranslatef(this->transX, this->transY, this->transZ);
        glRotatef(-90, 0,1,0);
        glRotatef(this->rotationAngleY, 1,0,0);
        glRotatef(this->rotationAngle, 0,1,0);

        glScalef(this->scaleX, this->scaleY, this->scaleZ);
        glBegin(GL_QUADS);
            // front
            glNormal3f(0,1,0);
            glTexCoord2f (0, 0);
            glVertex3f( 1.0f, 1.0f, 0.0);
            glTexCoord2f (0, 1);
            glVertex3f(-1.0f, 1.0f, 0.0);
            glTexCoord2f (1, 1);
            glVertex3f(-1.0f, 1.0f, 2.0);
            glTexCoord2f (1, 0);
            glVertex3f( 1.0f, 1.0f, 2.0);

            // back
            glNormal3f(0,-1,0);
            glTexCoord2f (0, 0);
            glVertex3f( 1.0f, -1.0f,  2.0f);
            glTexCoord2f (0, 1);
            glVertex3f(-1.0f, -1.0f,  2.0f);
            glTexCoord2f (1, 1);
            glVertex3f(-1.0f, -1.0f,  0.0f);
            glTexCoord2f (1, 0);
            glVertex3f( 1.0f, -1.0f,  0.0f);

            // top
            glNormal3f(0,0,1);
            glTexCoord2f (0, 0);
            glVertex3f( 1.0f,  1.0f, 2.0f);
            glTexCoord2f (0, 1);
            glVertex3f(-1.0f,  1.0f,2.0f);
            glTexCoord2f (1, 1);
            glVertex3f(-1.0f, -1.0f,2.0f);
            glTexCoord2f (1, 0);
            glVertex3f( 1.0f, -1.0f,2.0f);

            // bottom
            glNormal3f(0,0,-1);
            glTexCoord2f (0, 0);
            glVertex3f( 1.0f, -1.0f,0.0f);
            glTexCoord2f (0, 1);
            glVertex3f(-1.0f, -1.0f,0.0f);
            glTexCoord2f (1, 1);
            glVertex3f(-1.0f,  1.0f,0.0f);
            glTexCoord2f (1, 0);
            glVertex3f( 1.0f, 1.0f,0.0f);

            // left
            glNormal3f(-1,0,0);
            glTexCoord2f (0, 0);
            glVertex3f(-1.0f,  1.0f,2.0f);
            glTexCoord2f (0, 1);
            glVertex3f(-1.0f,  1.0f,0.0f);
            glTexCoord2f (1, 1);
            glVertex3f(-1.0f, -1.0f,0.0f);
            glTexCoord2f (1, 0);
            glVertex3f(-1.0f, -1.0f,2.0f);

            // right
            glNormal3f(1,0,0);
            glTexCoord2f (0, 0);
            glVertex3f(1.0f,  1.0f,0.0f);
            glTexCoord2f (0, 1);
            glVertex3f(1.0f,  1.0f,2.0f);
            glTexCoord2f (1, 1);
            glVertex3f(1.0f, -1.0f,2.0f);
            glTexCoord2f (1, 0);
            glVertex3f(1.0f, -1.0f,0.0f);
        glEnd();
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
void Cube::setRotationY(float angle){
    this->rotationAngleY = angle;
}
void Cube::setTexture(GLuint tex){
    this->texture = tex;
}
GLuint Cube::getTexture(){
  return this->texture;
}

void Cube::setColor(float r, float g, float b, float q){
    this->materialColor[0] = r;
    this->materialColor[1] = g;
    this->materialColor[2] = b;
    this->materialColor[4] = q;
}

void Cube::setTexturePath(char* path){
    this->texture = LoadTextureRAW(path);
}

float Cube::getRotation(){
    return this->rotationAngle;
}

float Cube::getRotationY(){
    return this->rotationAngleY;
}

void Cube::setRotationAxis(float x, float y, float z){
    rotationAxis[0] = x;
    rotationAxis[1] = y;
    rotationAxis[2] = z;
}
GLuint LoadTextureRAW( const char * filename ){

    GLuint texture;

    Image* image = loadBMP(filename);

    glGenTextures( 1, &texture );
    glBindTexture( GL_TEXTURE_2D, texture );
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR );
    glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
                             0,                            //0 for now
                             GL_RGB,                       //Format OpenGL uses for image
                             image->width, image->height,  //Width and height
                             0,                            //The border of the image
                             GL_RGB, //GL_RGB, because pixels are stored in RGB format
                             GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
                                               //as unsigned numbers
                             image->pixels);               //The actual pixel data
    delete image;

    return texture;
}

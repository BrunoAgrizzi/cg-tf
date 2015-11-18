#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include "imageloader.h"
#include "Cube.h"
#include <string.h>
#include "XMLConfig.h"
#include "Arena.h"
#include "Utils.h"

XMLConfig config;
Arena arena;
Helicopter player;

GLuint textureEarth;
GLuint textureSun;
GLuint texturePlane;

//Camera controls
double camDist=50;
double camXYAngle=0;
double camXZAngle=0;
int toggleCam = 0;
int camAngle = 60;
int lastX = 0;
int lastY = 0;
int buttonDown=0;

GLuint LoadTextureRAW( const char * filename );


void display (void){

    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};  /* white diffuse light. */
    GLfloat light_position[] = {0.0, 0.0, 1.0, 0.0};  /* Infinite light location. */
    //glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glPushMatrix();
    glTranslatef(0.0, 10.0, 10.0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glPopMatrix();

    glTranslatef(0,0,-camDist);
    glRotatef(camXZAngle,1,0,0);
    glRotatef(camXYAngle,0,1,0);

    //GLfloat light_position[] = { 0.0, 0.0, 0.0, 1.0 };
    //glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    //GLfloat light_position1[] = { 70.0, 70.0, 0.0, 1.0 };
    //GLfloat light1[] = {1,1,1,1};
    //glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
    //glLightfv(GL_LIGHT1, GL_DIFFUSE, light1);


    glPushMatrix();
    //arena.drawArena();
    glPopMatrix();

    /////////////////////////////////////////////////////player.draw();
    drawAxes();

    //glDisable(GL_LIGHTING);
    Cube c = Cube();
    c.setTexture(textureSun);
    c.setTranslation(0,0,0);
    c.setScale(5,5,5);
    c.draw();
    //glEnable(GL_LIGHTING);


    glutSwapBuffers();
}

void init (void){

     glEnable(GL_DEPTH_TEST);
     glEnable( GL_TEXTURE_2D );
     glEnable(GL_LIGHTING);    //    glShadeModel (GL_FLAT);
     glEnable(GL_LIGHT0);

     glShadeModel (GL_SMOOTH);
     glDepthFunc(GL_LEQUAL);

    textureSun = LoadTextureRAW( "../img/sun1.bmp" );
    //texturePlane = LoadTextureRAW( "stars1.bmp" );
    texturePlane = LoadTextureRAW( "../img/earth.bmp" );
    arena.setTexture(texturePlane);
    //setTexture(textureSun);


    //glMatrixMode(GL_PROJECTION);

    //glMatrixMode(GL_MODELVIEW);
}

void changeCamera(int angle, int w, int h){
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective (angle,(GLfloat)w / (GLfloat)h, 1, 150.0);
    glMatrixMode (GL_MODELVIEW);
}

void reshape (int w, int h) {

    glViewport (0, 0, (GLsizei)w, (GLsizei)h);
    changeCamera(camAngle, w, h);
}

void mouse_callback(int button, int state, int x, int y){
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        lastX = x;
        lastY = y;
        buttonDown = 1;
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {
        buttonDown = 0;
    }
}

void mouse_motion(int x, int y){
    if (!buttonDown)
        return;

    camXYAngle += x - lastX;
    camXZAngle += y - lastY;

    camXYAngle = (int)camXYAngle % 360;
    camXZAngle = (int)camXZAngle % 360;

    lastX = x;
    lastY = y;
}

void idle(){
    if(keys['a'] == 1 || keys['A'] == 1) player.rotate(1);
    if(keys['d'] == 1 || keys['D'] == 1) player.rotate(1 * -1);
    if(keys['w'] == 1 || keys['W'] == 1) player.move(-0.5);
    if(keys['s'] == 1 || keys['S'] == 1) player.move(+0.5);
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    // switch for the keys vector

    // switch 2

}

int main (int argc, char **argv) {
    char path[255];
	if(argc != 2){
		strcpy(path, "../config.xml");
	}else{
		strcpy(path, argv[1]);
		strcat(path, "config.xml");
	}

    config.readXML(path);
    arena.readXMLArena((config.getArena().getPath() + config.getArena().getName() + "." + config.getArena().getExtension()).c_str());
    player = config.readHelicopterConfig(path);

    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize (700, 700);
    glutInitWindowPosition  (100,0);
    glutCreateWindow ("Trabalho Final");
    init();
    glutDisplayFunc (idle);
    glutIdleFunc (display);
    glutReshapeFunc (reshape);
    // glutKeyboardFunc(keyboard);
    glutMotionFunc(mouse_motion);
    glutMouseFunc(mouse_callback);
    glutKeyboardFunc(setKeyDown);
	glutKeyboardUpFunc(setKeyUp);

    glutMainLoop ();

    return 0;
}

GLuint LoadTextureRAW( const char * filename )
{

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

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
double camDist=100;
double camXYAngle=0;
double camXZAngle=0;
int toggleCam = 0;
int camAngle = 60;
int lastX = 0;
int lastY = 0;
int buttonDown=0;

void display (void){

    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};  /* white diffuse light. */
    GLfloat light_position[] = {0.0, 0.0, 1.0, 0.0};  /* Infinite light location. */
    //glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glPushMatrix();
    glTranslatef(0.0, 10.0, 10.0);
    //glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glPopMatrix();

    if (toggleCam == 0){
        glTranslatef(0,0,-camDist);
        glRotatef(camXZAngle,1,0,0);
        glRotatef(camXYAngle,0,1,0);


        // glRotatef(camXZAngle,1,0,0);
        // glRotatef(camXYAngle,0,1,0);
    }
    if(toggleCam == 1){
         gluLookAt(-player.getGy(),10,player.getGx(), 0,0,0, 0,1,0);
    }
    if(toggleCam == 2){
        glTranslatef(player.getGy(), 20,player.getGx());
        glRotatef(-player.getAngle(),0,1,0);
        gluLookAt(
                    player.getGy(), 20,player.getGx(),
                    player.getGy(), 0, player.getGx(),
                    -1, 0, 0);
    }

    //GLfloat light_position[] = { 0.0, 0.0, 0.0, 1.0 };
    //glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    //GLfloat light_position1[] = { 70.0, 70.0, 0.0, 1.0 };
    //GLfloat light1[] = {1,1,1,1};
    //glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
    //glLightfv(GL_LIGHT1, GL_DIFFUSE, light1);



    arena.draw();
    player.draw();
    drawAxes();


    // arena.drawArena();

    glutSwapBuffers();
}

void init (void){
     glEnable(GL_DEPTH_TEST);
     glEnable( GL_TEXTURE_2D );
     glEnable(GL_LIGHTING);    //    glShadeModel (GL_FLAT);
     glEnable(GL_LIGHT0);

     glShadeModel (GL_SMOOTH);
     glDepthFunc(GL_LEQUAL);
     arena.init();


    //  standard camera
    toggleCam = 0;

     player.init();
    //setTexture(textureSun);
    //glMatrixMode(GL_PROJECTION);
    //glMatrixMode(GL_MODELVIEW);

    glMatrixMode(GL_PROJECTION);

    glMatrixMode(GL_MODELVIEW);
}

void changeCamera(int angle, int w, int h){
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective (angle,(GLfloat)w / (GLfloat)h, 1, 800.0);
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
    if(keys['0'] == 1) toggleCam = 0;
    if(keys['1'] == 1) toggleCam = 1;
    if(keys['2'] == 1) toggleCam = 2;

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

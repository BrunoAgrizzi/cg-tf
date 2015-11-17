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

//GLuint LoadTextureRAW( const char * filename );

void DrawAxes(){

    // GLfloat materialEmission[] = { 1.00, 0.00, 0.00, 1};
    GLfloat materialColor[] = { 1.0, 0.0, 0.0, 1};
    // GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1};
    // GLfloat mat_shininess[] = { 50.0 };


    // glMaterialfv(GL_FRONT, GL_EMISSION, materialEmission);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
    // glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    // glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    // GLfloat mat_ambient_r[] = { 1.0, 0.0, 0.0, 1.0 };
    // GLfloat mat_ambient_g[] = { 0.0, 1.0, 0.0, 1.0 };
    // GLfloat mat_ambient_b[] = { 0.0, 0.0, 1.0, 1.0 };

    // glPushAttrib(GL_ENABLE_BIT);
        // glDisable(GL_LIGHTING);
        // glDisable(GL_TEXTURE_2D);

        // glPushMatrix();
        //     Cube c = Cube();
        //     c.setColor(1,0,1,1);
        //     c.setScale(5,5,5);
        //     c.setTranslation(0.5,0,0);
        //     c.draw();
        // glPopMatrix();

        // glPopAttrib();

}


void display (void){
    // glClearColor (0.0,0.0,0.0,0.0);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0,0,-camDist);
    glRotatef(camXZAngle,1,0,0);
    glRotatef(camXYAngle,0,1,0);
    // camera inicia a uma distancia do obj

    //
    // GLfloat light_position[] = { 0.0, 0.0, 0.0, 1.0 };
    // glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    //
    // glEnable(GL_LIGHT1);
    // GLfloat light_position1[] = { 70.0, 70.0, 0.0, 1.0 };
    // GLfloat light1[] = {1,1,1,1};
    // glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
    // glLightfv(GL_LIGHT1, GL_DIFFUSE, light1);

    // glPushMatrix();
    //     glScalef(70,70,1);
    //     glTranslatef(0,0,-12);
    //     glRotatef(90,1,0,0);
    //    DisplayPlane (texturePlane);
    // glPopMatrix();
    player.draw();
    drawAxes();
    //DrawAxes();
    glFlush();
    glPushMatrix();
        // glRotatef(angleYear,0,1,0);
        // glTranslatef(0,0,-10);
        // glRotatef(angleDay,0,1,0);
        // glRotatef(90,1,0,0);
    glPopMatrix();

    glutSwapBuffers();
}

void init (void){
    // glEnable(GL_DEPTH_TEST);
    // glEnable( GL_TEXTURE_2D );
    // glEnable(GL_LIGHTING);    //    glShadeModel (GL_FLAT);
    // glShadeModel (GL_SMOOTH);
    //
    // glDepthFunc(GL_LEQUAL);
    //
    // glEnable(GL_LIGHT0);
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat mat_shininess[] = { 100.0 };
   GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };

   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_SMOOTH);

   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
   glLightfv(GL_LIGHT0, GL_POSITION, light_position);

   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_DEPTH_TEST);
}

void changeCamera(int angle, int w, int h){
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective (angle,
            (GLfloat)w / (GLfloat)h, 1, 150.0);
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
    if(keys['a'] == 1 || keys['A'] == 1) player.rotate(0.5);
    if(keys['d'] == 1 || keys['D'] == 1) player.rotate(0.5 * -1);

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

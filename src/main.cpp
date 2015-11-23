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
#include "Rect.h"

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
int toggleCam = 3;
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
    if(toggleCam == 1){ // first person OK
      float anguloPlayer = player.getAngle() * (3.1415 / 180);
           gluLookAt(player.getGy() +player.getCx() + 10 * cos(-anguloPlayer),player.getWorldHeight() + 30,player.getGx() + player.getCy() + 10 * sin(-anguloPlayer),
                    player.getGy()+player.getCx(), player.getWorldHeight() + 30, player.getGx()+player.getCy(),
                    0, 1, 0);
    }
    if(toggleCam == 2){ // third person-ish camera
      float anguloPlayer = player.getAngle() * (3.1415 / 180);
    //   glRotatef(player.getAngleGunUD()/2, 1,0,0);
    //   glRotatef(-player.getAngleGunLR()/2, 0,1,0);
    //   gluLookAt(player.getGy() +20,15,player.getGx(),
    //            player.getGy(), player.getWorldHeight() + 10, player.getGx(),
    //            0, 1, 0);

           gluLookAt(player.getGy() +player.getCx()+ 10 * cos(-anguloPlayer),player.getWorldHeight() + 30,player.getGx()+player.getCy() + 10 * sin(-anguloPlayer),
                    player.getGy()+player.getCx(), player.getWorldHeight() + 23, player.getGx()+player.getCy(),
                    0, 1, 0);
    }
    if(toggleCam == 3){ // OK
        float anguloPlayer = player.getAngle() * (3.1415 / 180);

        glTranslatef(0,0,-camDist);
        glRotatef(camXZAngle,1,0,0);
        glRotatef(camXYAngle,0,1,0);
        gluLookAt(player.getGy() +player.getCx()+ 10 * cos(-anguloPlayer),player.getWorldHeight() + 30,player.getGx() +player.getCy()+ 10 * sin(-anguloPlayer),
                 player.getGy()+player.getCx(), player.getWorldHeight() + 23, player.getGx()+player.getCy(),
                 0, 1, 0);
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

    // Disable color tracking
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);

    /*Orthogonal viewing*/
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 10000);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);


      /*Draw GAS*/
      glPushMatrix();
        glTranslatef(0.1, -1.8, 0);
        glScalef(0.2, 0.3, 0);
        glRotatef(90,0,0,1);
        Rect(0.0, 0.0, 1.0,10.0, "blue", 1.0, "black","").drawGasBar();
        glTranslatef(0.0,player.getGas()- 10 ,0.0);
        Rect(0.0,0.0,1.2,0.5,"",0.0,"","").drawGasIndicator();
      glPopMatrix();

      /*Restore the viewing mode*/
    	glMatrixMode(GL_PROJECTION);
    	glPopMatrix();
    	glMatrixMode(GL_MODELVIEW);
    	glPopMatrix();

      // Enable color tracking
glEnable(GL_COLOR_MATERIAL);
glEnable(GL_LIGHTING);
glEnable(GL_TEXTURE_2D);

    glutSwapBuffers();
}
void timerGasBar(int value){
	// on posto
	if(player.getFlying() || !onPosto(player, arena.getPostoAbastecimento())){
		player.decGas();
	}

	glutTimerFunc((1000),timerGasBar,0);
	glutPostRedisplay();
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
    toggleCam = 3;
    float hcx = arena.getPlayerStartX(), hcy = arena.getPlayerStartY();
     player.init();
     player.setInitialXY(arena.getPlayerStartX(), arena.getPlayerStartY());
}

void changeCamera(int angle, int w, int h){
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective (angle,(GLfloat)w / (GLfloat)h, 1, 1600.0);
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
    if (!buttonDown) return;

    if(lastY < y){
        if(camXZAngle + 1 < 90 && camXZAngle + 1 > -90){
            camXZAngle += 1;
            camXZAngle = (int)camXZAngle % 360;
        }
    }
    if(lastY > y){
        if(camXZAngle - 1 < 90 && camXZAngle -1  > -90){
            camXZAngle += -1;
            camXZAngle = (int)camXZAngle % 360;
        }
    }
    if(lastX < x){
        if(camXYAngle + 1 < 180 && camXYAngle + 1 > -180){
            camXYAngle += 1;
            camXYAngle = (int)camXYAngle % 360;
        }
    }
    if(lastX > x){
        if(camXYAngle - 1 < 180 && camXYAngle -1  > -180){
            camXYAngle += -1;
            camXYAngle = (int)camXYAngle % 360;
        }
    }

    lastX = x;
    lastY = y;
}

float mouseX = 0.0;
float mouseY = 0.0;
void mouse_passive_motion(int x , int y){
    static GLdouble previousTime = 0;
    GLdouble currentTime;
    GLdouble timeDifference;
    currentTime = glutGet(GLUT_ELAPSED_TIME);
    timeDifference = currentTime - previousTime;
    previousTime = currentTime;

    if(mouseX < x ) player.setAngleGunLR(timeDifference* -0.1);
	if(mouseX > x )	player.setAngleGunLR(timeDifference* 0.1);

    if(mouseY < y ) player.setAngleGunUD(timeDifference* 0.1);
    if(mouseY > y ) player.setAngleGunUD(timeDifference* -0.1);

	mouseX = x;
    mouseY = y;
}

void idle(){
    if(keys['a'] == 1 || keys['A'] == 1) player.rotate(1);
    if(keys['d'] == 1 || keys['D'] == 1) player.rotate(1 * -1);
    if(keys['w'] == 1 || keys['W'] == 1) player.move(-0.5 - 5);
    if(keys['s'] == 1 || keys['S'] == 1) player.move(+0.5 + 5);
    if(keys['0'] == 1) toggleCam = 0;
    if(keys['1'] == 1) toggleCam = 1;
    if(keys['2'] == 1) toggleCam = 2;
    if(keys['3'] == 1) toggleCam = 3;
    if(keys['+'] == 1) player.setWorldHeight(1);
    if(keys['-'] == 1) player.setWorldHeight(-1);
    if(!player.getFlying() && onPosto(player, arena.getPostoAbastecimento())){
        player.setGas(player.getTempoDeVoo() + 1);
    }
    if(player.getWorldHeight() < 15) {
        player.setFlying();
    }
    for(int i = 0; i < arena.getObjs().size() ; i++){
		// collision happende and object wasn't collected yet
		if(onObjetoResgate(player, arena.getObjetosResgate().at(i))){
                arena.getObjetosResgate().erase(arena.getObjetosResgate().begin() + i);
			// arena.collect(i);
			// player.setRescuedObjects(player.getRescuedObjects() + 1 );
		}
	}


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
    // TODO MUDAR PARA 500x500
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
    glutPassiveMotionFunc(mouse_passive_motion);
    //timers
    glutTimerFunc(1000, timerGasBar, 0);
    glutMainLoop ();

    return 0;
}

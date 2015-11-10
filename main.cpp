#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <math.h>
#include <cstring>
#include "XMLConfig.h"
#include "Arena.h"
#include "Helicopter.h"
#include "Utils.h"


#define ARENAX arena.getArena().getWidth()
#define ARENAY arena.getArena().getHeight()

using namespace std;
double Distance(double dX0, double dY0, double dX1, double dY1)
{
    return sqrt((dX1 - dX0)*(dX1 - dX0) + (dY1 - dY0)*(dY1 - dY0));
}

int hammerTime = 0;
bool shotFired[10];
Arena arena;
XMLConfig config;
Helicopter player;
vector<Shot> playerShots;
vector<Shot> enemyShots;
vector<Helicopter> enemies;
bool looksForPlayer = false;

void moveEnemies(){
	static GLdouble previousTime = 0;
	double currentTime, timeDifference;

	currentTime = glutGet(GLUT_ELAPSED_TIME);
	timeDifference = currentTime - previousTime;
	previousTime = currentTime;

}

void display(void){

	glClear (GL_COLOR_BUFFER_BIT);

		// arena and helicopter
		glPushMatrix();
			arena.drawArena(ARENAX, ARENAY);
		glPopMatrix();

		// checks if end message should be displayed
		if(!checkDefeat(player, ARENAX/2.0,ARENAY/2.0, enemyShots)
			&& !checkVictory(player, arena.getObjetosResgate().size(), ARENAX/2.0, ARENAY/2.0)){
			// shots
			glPushMatrix();
				for(int i = 0 ; i < playerShots.size() ; i++){
					if(!playerShots.at(i).getHitted()){
						playerShots.at(i).draw();
					}
				}
				if(enemyShots.size() > 0){
					for(int i = 0 ; i < enemyShots.size() ; i++){
						if(!enemyShots.at(i).getHitted())
						enemyShots.at(i).draw();
					}
				}
			glPopMatrix();

			glPushMatrix();
				player.draw();
			glPopMatrix();
			glPushMatrix();
			for(int i = 0 ; i < enemies.size() ; i++){
				if(!enemies.at(i).getIsDead()){
					enemies.at(i).draw();
				}
			}
			glPopMatrix();
		}
	glEnd();
	glutSwapBuffers();
}

void mouse(int button, int state, int x, int y){
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
		player.setFlying();
	}
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && player.getFlying()){
		// playerShots.push_back(Shot(player.getGunPosX(),
		// 							player.getGunPosY(),
		// 							player.getCurrentAngleGun(),
		// 							player.getAngle(),
		// 							player.getVelTiro(),
		// 							player.getAngleGun()));
		playerShots.push_back(Shot(player.getGunPosX(),
									player.getGunPosY(),
									player.getCurrentAngleGun(),
									player.getAngle(),
									player.getVelTiro(),
									player.getAngleGun()));
	}
}

void idle(){
	static GLdouble previousTime = 0;
    GLdouble currentTime;
    GLdouble timeDifference;

    currentTime = glutGet(GLUT_ELAPSED_TIME);
    timeDifference = currentTime - previousTime;
    previousTime = currentTime;
	float velPlayer = -player.getVelHelicoptero() * timeDifference;

	// key control
	if(keys['a'] == 1 || keys['A'] == 1) player.rotate(velPlayer);
	if(keys['d'] == 1 || keys['D'] == 1) player.rotate(velPlayer * -1);
	if(keys['w'] == 1 || keys['W'] == 1){
		// checks if next position exceeds boudaries
		if(!onArena(player, arena.getArena(), velPlayer)){
			if(!onPlayer(player, enemies.at(0)) &&
				!onPlayer(player, enemies.at(1)) &&
				!onPlayer(player, enemies.at(2))){
					player.moveY(velPlayer);
				}else{
					player.moveY(-velPlayer);
				}
		}
	}
	if(keys['s'] == 1 || keys['S'] == 1){
		// checks if next position exceeds boudaries
		if(!onArena(player, arena.getArena(), velPlayer))
		if(!onPlayer(player, enemies.at(0)) &&
			!onPlayer(player, enemies.at(1)) &&
			!onPlayer(player, enemies.at(2))){
				player.moveY(-velPlayer);
			}else{
				player.moveY(velPlayer);
			}
	}
	if(keys['+'] == 1) player.moveHelice(0.1 * timeDifference);
	if(keys['-'] == 1) player.moveHelice(-0.1 * timeDifference);

	// enemies conditional movement
	int r = (rand() % 10) ;
	for(int i = 0; i < enemies.size() ; i++){
		if(!enemies.at(i).getIsDead()){
			if(hammerTime == 0){
				float rndm = 40 + (rand() % (int)(80 - 40 + 1));
				float vel = -enemies.at(i).getVelHelicoptero() * timeDifference;
				bool arenaCollision = onArena(enemies.at(i), arena.getArena(), vel);
				bool isCollided = enemies.at(i).getCollided();
				int collidedWithEnemy = onEnemy(enemies, i);
				int collidedWithPlayer = onPlayer(player,enemies.at(i));

				// normal movement
				if(!arenaCollision && collidedWithEnemy == -1 && !collidedWithPlayer){
					enemies.at(i).moveY(vel);
					enemies.at(i).rotate(-vel/4);
				}

				// arena collision
				if(arenaCollision && collidedWithEnemy == -1 && !collidedWithPlayer){
					enemies.at(i).rotate(enemies.at(i).getVelHelicoptero() * timeDifference);
				}

				// arena and enemy collision
				if(arenaCollision && collidedWithEnemy != -1 && !collidedWithPlayer){
					enemies.at(i).rotate(vel);
				}

				// enemy collision
				if(!arenaCollision && collidedWithEnemy != -1 && !collidedWithPlayer){
					if(willCollide(enemies.at(i), enemies.at(collidedWithEnemy), vel) != -1){
						enemies.at(collidedWithEnemy).moveY(vel/6);
						enemies.at(collidedWithEnemy).rotate(vel *2);
					}
				}

				// player collision only
				if(!arenaCollision && collidedWithPlayer && collidedWithEnemy == -1){
					if(willCollide(player, enemies.at(i), vel) != -1){
						player.setCollided(true);
						enemies.at(i).moveY(vel/2);
						enemies.at(i).rotate(vel * 3);
					}
				}
			}
			if(hammerTime == 1){
				float angleEnemy = enemies.at(i).getAngle();
				float enemyX = enemies.at(i).getGunPosX();
				float enemyY = enemies.at(i).getGunPosY();
				float enemyXFar = (enemyX - 2000) * (cos(( 90 + enemies.at(i).getAngle()) * 3.1415/180.0));
				float enemyYFar = (enemyY - 2000) * (sin(( 90 + enemies.at(i).getAngle()) * 3.1415/180.0));
				float playerX = player.getGunPosX();
				float playerY = player.getGunPosY();
				float d1 = Distance(enemyX,enemyY,playerX,playerY);
				float d2 = Distance(playerX,playerY,
									(enemyX - 2000) * (cos(( 90 + enemies.at(i).getAngle()) * 3.1415/180.0)),
									(enemyY - 2000) * (sin(( 90 + enemies.at(i).getAngle()) * 3.1415/180.0)));
				float d3 = Distance( enemyX,enemyY,
									(enemyX - 2000) * (cos(( 90 + enemies.at(i).getAngle()) * 3.1415/180.0)),
									(enemyY - 2000) * (sin(( 90 + enemies.at(i).getAngle()) * 3.1415/180.0)));
				if(d1 + d2 < d3 +1.0 && d1 + d2 > d3 - 1.0 && !shotFired[i]){
						enemyShots.push_back(Shot(enemies.at(i).getGunPosX(),
														enemies.at(i).getGunPosY(),
														enemies.at(i).getAngle(),
														enemies.at(i).getAngle(),
														enemies.at(i).getVelTiro(),
														enemies.at(i).getAngleGun()));
						shotFired[i] = true;
				}else{
					enemies.at(i).rotate(-velPlayer);
				}
			}
		}
	}

	bool everybodyShot = true;
	for(int i = 0 ; i < enemies.size() ; i++){
		if(!shotFired[i]) everybodyShot = false;
	}
	if(everybodyShot){
		for(int i = 0; i < enemies.size(); i++){
			shotFired[i] = false;
		}
		hammerTime = 0;
	}

	// shot collision
	for(int i = 0 ; i < enemies.size() ; i++){
		int shot = wasShot(enemies.at(i), playerShots);
		if(shot != -1){
			//isDead = true, player isn't drawn anymore nor shoots
			enemies.at(i).setIsDead(true);
			// hitted= true for the shot, so it isn't drawn anymore
			playerShots.at(shot).setHitted(true);
		}
	}

	// rescue
	for(int i = 0; i < arena.getObjetosResgate().size() ; i++){
		// collision happende and object wasn't collected yet
		if(!arena.getObjetosResgate().at(i).getCollected()
			&& onObjetoResgate(player, arena.getObjetosResgate().at(i))){
			arena.collect(i);
			player.setRescuedObjects(player.getRescuedObjects() + 1 );
		}
	}

	// refuels
	if(!player.getFlying() && onPosto(player, arena.getPostoAbastecimento())){
		player.setGas(player.getTempoDeVoo() + 1);
	}

	glutPostRedisplay();
}

void timerEnemyMovement(int value){
	// int nextMove = (4 + rand() % (int)(6 - 4 + 1)) * 1000;
	// int directionMove = pow(-1,(1 + rand() % (int)(2 - 1 + 1)));
	// static GLdouble previousTime = 0;
	// double currentTime, timeDifference;
	// currentTime = glutGet(GLUT_ELAPSED_TIME);
	// timeDifference = currentTime - previousTime;
	// previousTime = currentTime;
	//
	//
	// for(int i = 0 ; i < enemies.size() ; i++){
	// 	enemies.at(i).setAngle(-90);
	// 	enemies.at(i).setDirection(directionMove);
	// }
	// glutTimerFunc(3000,timerEnemyMovement,0);
}

void timerGasBar(int value){
	// on posto
	if(player.getFlying() || !onPosto(player, arena.getPostoAbastecimento())){
		player.decGas();
	}

	glutTimerFunc((1000),timerGasBar,0);
	glutPostRedisplay();
}

void timerEnemyShooting(int value){

	if(hammerTime == 0){
		hammerTime = 1;

	} else{
		hammerTime = 0;
	}

	glutTimerFunc(1/enemies.at(0).getFreqTiro(),timerEnemyShooting,200);
	glutPostRedisplay();
}

float mouseX = 0.0;
void motion(int x, int y){

	static GLdouble previousTime = 0;
    GLdouble currentTime;
    GLdouble timeDifference;
    currentTime = glutGet(GLUT_ELAPSED_TIME);
    timeDifference = currentTime - previousTime;
    previousTime = currentTime;

	if(mouseX < x ) player.rotateGun(timeDifference* 0.1);
	if(mouseX > x )	player.rotateGun(timeDifference* -0.1);
	mouseX = x;
}

int main(int argc, char* argv[]){
	char path[255];
	if(argc != 2){
		cout << "Running at default path './config/config.xml'..." << endl;
		strcpy(path, "config.xml");
	}else{
		strcpy(path, argv[1]);
		strcat(path, "config.xml");
	}
	srand(time(NULL));

	config.readXML(path);
	arena.readXMLArena((config.getArena().getPath() + config.getArena().getName() + "." + config.getArena().getExtension()).c_str());
	player = config.readHelicopterConfig(path);
	player.setArena(ARENAX, ARENAY);

	enemies.push_back(config.readEnemyHelicopter(path, ARENAX/100 * 90, ARENAY/100 * 10));
	enemies.push_back(config.readEnemyHelicopter(path, ARENAX/100 * 90, ARENAY/100 * 90));
	enemies.push_back(config.readEnemyHelicopter(path, ARENAX/100 * 10, ARENAY/100 * 90));

	for(int i = 0; i < 10; i++){
		shotFired[i] = false;
	}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(ARENAX,ARENAY);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Arena");
	init(ARENAX, ARENAY);
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutIdleFunc(idle);
	glutKeyboardFunc(setKeyDown);
	glutKeyboardUpFunc(setKeyUp);

	//timers
	glutTimerFunc(1000, timerGasBar, 0);
	// glutTimerFunc(4000,timerEnemyMovement,0);
	glutTimerFunc(1/enemies.at(0).getFreqTiro(),timerEnemyShooting,200);

	glutPassiveMotionFunc(motion);
	glutMainLoop();

}

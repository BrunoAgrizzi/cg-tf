#include "Utils.h"
#include <string>
#include <GL/glut.h>
#include <math.h>

const float red[] = {1.0,0.0,0.0};
const float blue[] = {0.0,0.0,1.0};
const float green[] = {0.0,1.0,0.0};
const float gray[] = {0.5,0.5,0.5};
const float white[] = {1.0,1.0,1.0};
const float black[] = {0.0,0.0,0.0};
const float darkred[] = {0.8,0.0,0.0};
const float darkgreen[] = {0.0,0.8,0.0};

int keys[256];

void init (float arenaX, float arenaY){
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, arenaX, arenaY, 0.0, -1.0, 1.0);
}

bool gameOver = false;

// returns index of shot which collided at given helicopter
// returns -1 otherwise (helicopter wasn't shot)
int wasShot(Helicopter h, vector<Shot> shots){
	for(int i = 0 ; i < shots.size() ; i++){
		// is it the shot's first collision?
		if(!shots.at(i).getHitted() && checkCollision(h.getGunPosX(),
						h.getGunPosY(),
						h.getRadius(),
						shots.at(i).getX(),
						shots.at(i).getY(),
						shots.at(i).getCircle().getR())){
						return i;
		}
	}
	return -1;
}

// true = victory
// false = defeat
 bool checkDefeat(Helicopter player, float x, float y, vector<Shot> enemyShots){
	 if(wasShot(player, enemyShots) != -1){
		 gameOver = true;
	 }
	string message = "YOU LOSE";

	if(player.getGas() <= 0 || gameOver){
			glPushMatrix();
				glLineWidth(5);
				glTranslatef(x * 0.5, y, 0.0);
				glColor3f(0.0, 0.0, 0.0);
				glScalef(0.5, 0.5, 0.5);
				glRotatef(180.0, 1.0, 0.0, 0.0);
				for(int i = 0; message[i] != '\0' ; i++) glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN,message[i]);
				glLineWidth(1);
			glPopMatrix();
		return true;
	}
	return false;
}

bool checkVictory(Helicopter player, int nObjects, float x, float y){
	string message = "YOU WON";
	if(player.getRescuedObjects() == nObjects){
		glPushMatrix();
			glLineWidth(5);
			glTranslatef(x * 0.5, y, 0.0);
			glColor3f(0.0, 0.0, 0.0);
			glScalef(0.5, 0.5, 0.5);
			glRotatef(180.0, 1.0, 0.0, 0.0);
			for(int i = 0; message[i] != '\0' ; i++) glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN,message[i]);
			glLineWidth(1);
		glPopMatrix();
		return true;
	}
	return false;
}

void setKeyUp(unsigned char key, int x, int j){

	switch(key){
		case 'a': case 'A':	keys['a'] = 0; break;
		case 'D': case 'd':	keys['d'] = 0; break;
		case 'w': case 'W': keys['w'] = 0; break;
		case 'S': case 's': keys['s'] = 0; break;
		case '+': keys['+'] = 0; break;
		case '-': keys['-'] = 0; break;
		break;
	}
	glutPostRedisplay();
}

void setKeyDown(unsigned char key, int x, int j){
	switch(key){
		case 'a': case 'A':	keys['a'] = 1; break;
		case 'D': case 'd':	keys['d'] = 1; break;
		case 'w': case 'W': keys['w'] = 1; break;
		case 'S': case 's': keys['s'] = 1; break;
		case '+': keys['+'] = 1; break;
		case '-': keys['-'] = 1; break;
		break;
	}
	glutPostRedisplay();
}

int onEnemy(vector<Helicopter> enemies, int i){
	bool result = false;
	for(int j = 0 ; j < enemies.size(); j++){
		if(j != i){
			if(checkCollision(enemies.at(i).getGunPosX(),
							enemies.at(i).getGunPosY(),
							enemies.at(i).getRadius(),
							enemies.at(j).getGunPosX(),
							enemies.at(j).getGunPosY(),
							enemies.at(j).getRadius())){
								return j;
							}
		}
	}
	return -1;
}

bool onPlayer(Helicopter player, Helicopter enemy){
	if(enemy.getIsDead() == true){
		return false;
	}
	if(checkCollision(player.getGunPosX(),
					player.getGunPosY(),
					player.getRadius(),
					enemy.getGunPosX(),
					enemy.getGunPosY(),
					enemy.getRadius())){
		return true;
	}
	return false;
}

bool onPosto(Helicopter player, Rect posto){
	if(player.getGunPosX() > posto.getX()
		&& player.getGunPosX() < (posto.getX() + posto.getWidth())
		&& player.getGunPosY() > posto.getY()
		&& player.getGunPosY() < (posto.getY() + posto.getHeight())
	){
		// on posto
		return true;
	}
	// left posto
	return false;
}

bool checkCollision(float x, float y, float r, float a, float b, float c){
	float dist = sqrt(pow(x - a, 2) + pow(y - b, 2));
	bool result;
	if(dist <= (r + c)){
		result = true;
	}else{
		result = false;
	}
	return result;
}

bool onArena(Helicopter player, Rect arena, float displacement){
	float nextMoveX = player.getNextMoveX(displacement) + player.getCx();
	float nextMoveY = player.getNextMoveY(displacement) + player.getCy();

	if(nextMoveX + player.getRadius() > arena.getWidth()
		|| nextMoveX - player.getRadius() < 0.0
		|| nextMoveY + player.getRadius() > arena.getHeight()
		|| nextMoveY - player.getRadius() < 0.0){
			// left arena
			return true;
		}
	// on arena
	return false;
}

bool onObjetoResgate(Helicopter player, Circle objetoResgate){
	return checkCollision(player.getGunPosX(),
							player.getGunPosY(),
							0.0,
							objetoResgate.getCx(),
							objetoResgate.getCy(),
							objetoResgate.getR());
}

int willCollide(Helicopter h1, Helicopter h2, float displacement){
	float forwardXH1 = h1.getNextMoveX(displacement) + h1.getCx();
	float forwardYH1 = h1.getNextMoveY(displacement) + h1.getCy();

	float forwardXH2 = h2.getNextMoveX(displacement) + h2.getCx();
	float forwardYH2 = h2.getNextMoveY(displacement) + h2.getCy();

	float backwardXH1 = h1.getNextMoveX(-displacement) + h1.getCx();
	float backwardYH1 = h1.getNextMoveY(-displacement) + h1.getCy();

	float backwardXH2 = h2.getNextMoveX(-displacement) + h2.getCx();
	float backwardYH2 = h2.getNextMoveY(-displacement) + h2.getCy();

	//collides if both move forward
	if(!checkCollision(forwardXH1, forwardYH1, h1.getRadius(), forwardXH2, forwardYH2, h2.getRadius())){
		return 1;
	}

	if(!checkCollision(backwardXH1, backwardYH1, h1.getRadius(), forwardXH2, forwardXH2, h2.getRadius())){
		return 2;
	}

	if(!checkCollision(backwardXH1, backwardYH1, h1.getRadius(), backwardXH2, backwardYH2, h2.getRadius())){
		return 3;
	}

	if(!checkCollision(forwardXH1, forwardXH1, h1.getRadius(), backwardXH2, backwardYH2, h2.getRadius())){
		return 4;
	}

	return -1;

}

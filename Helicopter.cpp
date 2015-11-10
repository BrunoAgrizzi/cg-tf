#include <string>
#include <math.h>
#include <GL/glut.h>
#include "Helicopter.h"
#include "Utils.h"
#include "HelicopterConfig.h"

using namespace std;

Helicopter::Helicopter(){
	gX = 0.0;
	gY = 0.0;
}

// enemy
Helicopter::Helicopter(float freqTiro, float velHelicoptero, float cx, float cy){
	isEnemy = true;
	this->velTiro = 0.2;
	this->freqTiro = freqTiro;
	this->velHelicoptero= velHelicoptero;
	gX = 0.0,
	gY = 0.0;
	radius = bodyWidth*0.7;
	cX = cx;
	cY = cy;
	// angle = rand() % 360;
	this->angle = 0.0;
	flying = true;
	velHelice = 10.0;
	this->collided = false;
	this->rescuedObjects = 0;
	this->isDead = false;
	this->direction = 1;
	this->isRotating = false;
}

// player
Helicopter::Helicopter(float velTiro, float velHelicoptero, float tempoDeVoo){
	isEnemy = false;
	this->velTiro = velTiro;
	this->velHelicoptero = velHelicoptero;
	this->tempoDeVoo = tempoDeVoo;
	gas = tempoDeVoo;
	gX = 0.0;
	gY = 0.0;
	cX = initialX;
	cY = initialY;
	angle = 0.0;
	flying = false;
	velHelice = 0.0;
	radius = bodyWidth;
	this->rescuedObjects = 0;
	this->collided = false;
	this->direction = 1;
	this->isDead = false;
}

float Helicopter::getFreqTiro(){return this->freqTiro;}
float Helicopter::getVelTiro(){return this->velTiro;}
float Helicopter::getVelHelicoptero(){return this->velHelicoptero;}
float Helicopter::getCurrentAngleGun(){return angleGun + angle;}
float Helicopter::getGunPosX(){return cX + gX;}
float Helicopter::getGunPosY(){return cY + gY;}
float Helicopter::getAngle(){return angle;}
float Helicopter::getAngleGun(){return angleGun;}
bool Helicopter::getFlying(){return flying;}
float Helicopter::getTempoDeVoo(){return this->tempoDeVoo;}
void Helicopter::moveX(GLfloat value){}
void Helicopter::setAngle(float a){this->angle = a;}
float Helicopter::getGas(){return this->gas;};
void Helicopter::setGas(float g){this->gas = g;};
float Helicopter::getRadius(){return this->radius;};
float Helicopter::getGx(){return this->gX;};
float Helicopter::getCx(){return this->cX;};
float Helicopter::getGy(){return this->gY;};
float Helicopter::getCy(){return this->cY;};
void Helicopter::setIsDead(bool value){this->isDead = value;};
bool Helicopter::getIsDead(){return isDead;};
void Helicopter::setCollided(bool value){this->collided = value;};
bool Helicopter::getCollided(){return this->collided;};
void Helicopter::setRescuedObjects(int value){this->rescuedObjects = value;};
int Helicopter::getRescuedObjects(){return this->rescuedObjects;};
void Helicopter::setDirection(float value){this->direction = value;};
void Helicopter::setRotating(bool value){
	if(this->isRotating){
		this->isRotating = false;
	}else{
		this->isRotating = true;
	}

}
bool Helicopter::getRotating(){return this->isRotating;};
float Helicopter::getDirection(){return this->direction;};
float Helicopter::getNextMoveX( float val ){
	return this->gX + val * cos(( 90 + angle) * 3.1415/180.0);
}
float Helicopter::getNextMoveY( float val ){
	return this->gY + val * sin(( 90 + angle) * 3.1415/180.0);
}
void Helicopter::rotate(GLfloat value){
	angle += value;
}
void Helicopter::moveHelice(float value){
	velHelice += value;
}
void Helicopter::moveY(GLfloat value){
	if(flying){
		this->gX += value * cos(( 90 + angle) * 3.1415/180.0);
		this->gY += value * sin((angle + 90) * 3.1415/180.0);
	}
}
void Helicopter::setFlying(){
	if(flying){
		flying = false;
	}else{
		flying = true;
	}
}
void Helicopter::setArena(float aX, float aY){
	this->arenaX = aX;
	this->arenaY = aY;
}
void Helicopter::rotateGun(float value){
	if(fmod((angleGun + value),float(360.0)) < float(45.0) && fmod((angleGun + value),float(360.0)) > float(-45.0)){
		angleGun = angleGun + value;
	}
}
void Helicopter::decGas(){
	this->gas--;
}
void drawGun(float angleGun, float gunx, float guny, float angle){
	glPushMatrix();
		glTranslatef(gunx, guny,0.0);
		glRotatef(angleGun-180,0.0,0.0,1.0);
		Rect(0.0, 0.0, gunWidth, gunHeight, "black", 1.0, "black","").drawTC();
	glPopMatrix();
}

void drawHelicopter(GLfloat cX, GLfloat cY, GLfloat angle, GLfloat angleHelice, bool flying, float angleGun, bool isEnemy){
	if(flying){
		cX = cX/2.0;
		cY = cY/2.0;
	}

	glPushMatrix();
		glTranslatef(0.0, 0.0,0.0);
		if(isEnemy) Rect(0.0, 0.0, bodyWidth, bodyHeight, "darkred", 1.0, "black","").draw();
		if(!isEnemy)Rect(0.0, 0.0, bodyWidth, bodyHeight, "darkgreen", 1.0, "black","").draw();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.0 ,0.0 + bodyHeight,0);
		if(isEnemy) Rect(0.0, 0.0, tailWidth, tailHeight, "darkred", 1.0, "black", "").draw();
		if(!isEnemy)Rect(0.0, 0.0, tailWidth, tailHeight, "darkgreen", 1.0, "black", "").draw();

	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.0 + tailWidth/2.0 + tailRightWidth/2.0,
					0.0 + bodyHeight/2.0 + tailHeight,
					0.0);
		Rect(0.0, 0.0, tailRightWidth, tailRightHeight, "black", 1.0, "black", "").draw();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.0 - tailWidth/2.0 - tailLeftWidth/2.0,
					0.0 + bodyHeight/2.0 + tailHeight,
					0.0);
		Rect(0.0, 0.0, tailLeftWidth, tailLeftHeight, "black", 1.0, "black", "").draw();
	glPopMatrix();

	//helice 1
	glPushMatrix();
		glTranslatef(0.0, 0.0,0.0);
		glRotatef(angleHelice, 0.0, 0.0,1.0);
		Rect(0.0, 0.0, heliceWidth, heliceHeight, "black", 1.0, "black","").draw();
	glPopMatrix();

	//helice 2
	glPushMatrix();
		glTranslatef(0.0, 0.0 ,0.0);
		glRotatef(angleHelice-90, 0.0, 0.0,1.0);
		Rect(0.0, 0.0, heliceWidth, heliceHeight, "black", 1.0, "black","").draw();
	glPopMatrix();

	//base helice
	glPushMatrix();
		glTranslatef(0.0 ,0.0 ,0);
		Circle(0.0, 0.0, raioHeliceBase, "gray", "").draw();
	glPopMatrix();
}

void drawGas(int gas, int tempoDeVoo, float arenaX, float arenaY){
	glPushMatrix();
		if(gas >= 0){
			glTranslatef(arenaX * 0.05 ,(arenaY * 0.95),0.0);
			glRotatef(180 ,0.0 ,0.0 ,1.0);
			glScalef(arenaX/1000, arenaY/1000,0.0);
			Rect(0.0, 0.0, 40.0, tempoDeVoo * 10, "blue", 1.0, "black","").drawGasBar();
			glTranslatef(0.0, (gas -1) *10,0.0);
			Rect(0.0,0.0,50.0,10.0,"",0.0,"","").drawGasIndicator();
		}
	glPopMatrix();
}

void Helicopter::draw(){
	if(flying) angleHelice = angleHelice + velHelice + 1.0;
	// helicopter
	glPushMatrix();
		glTranslatef(cX+gX, cY+gY, 0.0);
		glRotatef(angle, 0.0,0.0,1.0);
		if(!flying) glScalef(1.0/1.5,1.0/1.5,1.0/1.5);
		drawGun(angleGun, 0.0, -bodyHeight/2.0 + 5.0, angle);
		drawHelicopter(cX, cY, angle, angleHelice, flying, angleGun, isEnemy);
	glPopMatrix();

	// gas
	if(!isEnemy && flying){
		glPushMatrix();
			drawGas(gas,tempoDeVoo, arenaX, arenaY);
		glPopMatrix();
	}
}
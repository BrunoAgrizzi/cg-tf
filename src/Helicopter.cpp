#include <string>
#include <math.h>
#include <GL/glut.h>
#include "Helicopter.h"
#include "Utils.h"
#include "Cube.h"

using namespace std;

Helicopter::Helicopter(){
	// gX = 0.0;
	// gY = 0.0;
}

void Helicopter::init(){
	this->base = Cube();
	this->tail = Cube();
	this->leftTail = Cube();
	this->rightTail = Cube();
	this->helix = Cube();
	this->helix2 = Cube();
	this->gas = this->tempoDeVoo;

	this->base.setTexturePath("../img/sun1.bmp");
	this->tail.setTexturePath("../img/sun1.bmp");
	this->leftTail.setTexturePath("../img/sun1.bmp");
	this->rightTail.setTexturePath("../img/sun1.bmp");
	this->helix.setTexturePath("../img/sun1.bmp");
	this->helix2.setTexturePath("../img/sun1.bmp");
	this->gun.setTexturePath("../img/stars1.bmp");
}

// enemy
Helicopter::Helicopter(float freqTiro, float velHelicoptero, float cx, float cy){
	this->velTiro = 0.2;
	this->freqTiro = freqTiro;
	this->velHelicoptero= velHelicoptero;
	this->worldHeight = 15;
	// cX = cx;
	// cY = cy;
	// gX = 0.0,
	// gY = 0.0;
	// radius = bodyWidth*0.7;
	// // angle = rand() % 360;
	// this->angle = 0.0;
	// flying = true;
	// velHelice = 10.0;
	// this->collided = false;
	// this->rescuedObjects = 0;
	// this->isDead = false;
	// this->direction = 1;
	// this->isRotating = false;
	// isEnemy = true;
}

// player
Helicopter::Helicopter(float velTiro, float velHelicoptero, float tempoDeVoo){
	this->velTiro = velTiro;
	this->velHelicoptero = velHelicoptero;
	this->tempoDeVoo = tempoDeVoo;
	this->angle = 0;
	this->worldHeight = 15;
	gX = 0.0;
	gY = 0.0;
	cX = 0;
	cY = 0;
	// gas = tempoDeVoo;
	// angle = 0.0;
	// flying = false;
	// velHelice = 0.0;
	// radius = bodyWidth;
	// this->rescuedObjects = 0;
	// this->collided = false;
	// this->direction = 1;
	// this->isDead = false;
	// isEnemy = false;
}

void drawHelicopter(float angleHelice,
					Cube base,
					Cube tail,
					Cube leftTail,
					Cube rightTail,
					Cube helix,
					Cube helix2,
					Cube gun,
					float angleGun,
					float angleGunY){
	const float baseScale[] = {7,4,4};
	const float baseSx = 6, baseSy = 4, baseSz = 4;
	const float baseTx = 0, baseTy = 0, baseTz = 0;
	const float tailSx = 7, tailSy = 1, tailSz = 1;
	const float tailTx = baseSx + 5, tailTy = 0, tailTz = 0;

	glPushMatrix();
		base.setScale(baseSx, baseSy, baseSz);
		base.setRotation(0);
		base.setTranslation(baseTx, baseTy, baseTz);
        base.draw();
    glPopMatrix();
    glPushMatrix();
        tail.setScale(tailSx, tailSy, tailSz);
        tail.setTranslation(tailTx,tailTy,tailTz);
		tail.setRotation(0);
        tail.draw();
    glPopMatrix();
    glPushMatrix();
        leftTail.setScale(3,1,1);
		rightTail.setScale(3,1,1);
		leftTail.setRotation(0);
		rightTail.setRotation(0);
        leftTail.setTranslation(baseSx+10,0,2);
		rightTail.setTranslation(baseSx+10,0,-2);

	    leftTail.draw();
		rightTail.draw();
    glPopMatrix();
	glPushMatrix();
		helix.setRotation(angleHelice);
		helix.setScale(12, 0.3, 1);
		helix.setTranslation(0,baseSy + 0.5,0);
		helix.draw();

		helix2.setRotation(0);
		helix2.setRotation(angleHelice-90);
		helix2.setScale(12, 0.3, 1);
		helix2.setTranslation(0,baseSy + 0.5,0);
		helix2.draw();
	glPopMatrix();
	glPushMatrix();
		gun.setTranslation(-5.5,0,0);
		gun.setScale(0.7,0.7,2);
		const float baseRotation = -90;
		gun.setRotation(angleGun);
		gun.setRotationY(angleGunY);
		// glTranslatef(-6,0,0);
		glutSolidCube(1.0);
		gun.drawBC();
		// gun.set()
	glPopMatrix();
}

void Helicopter::draw(){
	this->angleHelice = this->angleHelice + 15.27;
	glPushMatrix();
		// TODO Y dinamico
		glTranslatef(cX+gY, worldHeight,cY+ gX);
		glRotatef(angle,0,1,0);
		drawHelicopter(angleHelice,this->base, tail, leftTail, rightTail, helix, helix2, gun, angleGun, angleGunY);
	glPopMatrix();
}

void Helicopter::rotate(GLfloat value){
	angle += value;
}

void Helicopter::move(GLfloat value){
	// if(flying){
		this->gX += value * cos(( 90 + angle) * 3.1415/180.0);
		this->gY += value * sin((angle + 90) * 3.1415/180.0);
	// }
}
float Helicopter::getAngle(){
	return this->angle;
}
float Helicopter::getGx(){
	return this->gX;
}
float Helicopter::getGy(){
	return this->gY;
}
void Helicopter::setWorldHeight(float direction){
	if((this->worldHeight > 0 && direction == -1) ||
	(this->worldHeight < 800 && direction == 1)){
		this->worldHeight = worldHeight + direction;
	}
}
float Helicopter::getWorldHeight(){
	return this->worldHeight;
}
float Helicopter::getAngleGunLR(){
	return this->angleGun;
}
void Helicopter::setAngleGunLR(float value){
	if(fmod((angleGun + value),float(360.0)) < float(45.0) && fmod((angleGun + value),float(360.0)) > float(-45.0)){
		angleGun = angleGun + value;
	}
}
float Helicopter::getAngleGunUD(){
	return this->angleGunY;
}
void Helicopter::setAngleGunUD(float value){
	if(fmod((angleGunY + value),float(360.0)) < float(45.0) && fmod((angleGunY + value),float(360.0)) > float(-45.0)){
		angleGunY = angleGunY + value;
	}
}
float Helicopter::getTempoDeVoo(){
	return this->tempoDeVoo;
}
void Helicopter::decGas(){
 	this->gas--;
}
float Helicopter::getGas(){return this->gas;};
void Helicopter::setGas(float g){this->gas = g;};

Cube Helicopter::getGun(){
	return this->gun;
}
void Helicopter::setInitialXY(float x, float y){
	cX = x;
	cY = y;
}

float Helicopter::getCx(){
		return cX;
}

float Helicopter::getCy(){
	return cY;
}
// void Helicopter::move(GLfloat value){

//
// }
// float Helicopter::getFreqTiro(){return this->freqTiro;}
// float Helicopter::getVelTiro(){return this->velTiro;}
// float Helicopter::getVelHelicoptero(){return this->velHelicoptero;}
// float Helicopter::getCurrentAngleGun(){return angleGun + angle;}
// float Helicopter::getGunPosX(){return cX + gX;}
// float Helicopter::getGunPosY(){return cY + gY;}
// float Helicopter::getAngle(){return angle;}
// float Helicopter::getAngleGun(){return angleGun;}
// bool Helicopter::getFlying(){return flying;}
// float Helicopter::getTempoDeVoo(){return this->tempoDeVoo;}
// void Helicopter::moveX(GLfloat value){}
// void Helicopter::setAngle(float a){this->angle = a;}
// float Helicopter::getGas(){return this->gas;};
// void Helicopter::setGas(float g){this->gas = g;};
// float Helicopter::getRadius(){return this->radius;};
// float Helicopter::getGx(){return this->gX;};
// float Helicopter::getCx(){return this->cX;};
// float Helicopter::getGy(){return this->gY;};
// float Helicopter::getCy(){return this->cY;};
// void Helicopter::setIsDead(bool value){this->isDead = value;};
// bool Helicopter::getIsDead(){return isDead;};
// void Helicopter::setCollided(bool value){this->collided = value;};
// bool Helicopter::getCollided(){return this->collided;};
// void Helicopter::setRescuedObjects(int value){this->rescuedObjects = value;};
// int Helicopter::getRescuedObjects(){return this->rescuedObjects;};
// void Helicopter::setDirection(float value){this->direction = value;};
// void Helicopter::setRotating(bool value){
// 	if(this->isRotating){
// 		this->isRotating = false;
// 	}else{
// 		this->isRotating = true;
// 	}
//
// }
// bool Helicopter::getRotating(){return this->isRotating;};
// float Helicopter::getDirection(){return this->direction;};
// float Helicopter::getNextMoveX( float val ){
// 	return this->gX + val * cos(( 90 + angle) * 3.1415/180.0);
// }
// float Helicopter::getNextMoveY( float val ){
// 	return this->gY + val * sin(( 90 + angle) * 3.1415/180.0);
// }
// void Helicopter::moveHelice(float value){
// 	velHelice += value;
// }
// void Helicopter::setFlying(){
// 	if(flying){
// 		flying = false;
// 	}else{
// 		flying = true;
// 	}
// }
// void Helicopter::setArena(float aX, float aY){
// 	this->arenaX = aX;
// 	this->arenaY = aY;
// }
// void Helicopter::rotateGun(float value){
// 	if(fmod((angleGun + value),float(360.0)) < float(45.0) && fmod((angleGun + value),float(360.0)) > float(-45.0)){
// 		angleGun = angleGun + value;
// 	}
// }
// void Helicopter::decGas(){
// 	this->gas--;
// }
// void drawGun(float angleGun, float gunx, float guny, float angle){
// 	glPushMatrix();
// 		glTranslatef(gunx, guny,0.0);
// 		glRotatef(angleGun-180,0.0,0.0,1.0);
// 		Rect(0.0, 0.0, gunWidth, gunHeight, "black", 1.0, "black","").drawTC();
// 	glPopMatrix();
// }

// void drawHelicopter(GLfloat cX, GLfloat cY, GLfloat angle, GLfloat angleHelice, bool flying, float angleGun, bool isEnemy){
// 	if(flying){
// 		cX = cX/2.0;
// 		cY = cY/2.0;
// 	}
//
// 	glPushMatrix();
// 		glTranslatef(0.0, 0.0,0.0);
// 		if(isEnemy) Rect(0.0, 0.0, bodyWidth, bodyHeight, "darkred", 1.0, "black","").draw();
// 		if(!isEnemy)Rect(0.0, 0.0, bodyWidth, bodyHeight, "darkgreen", 1.0, "black","").draw();
// 	glPopMatrix();
// 	glPushMatrix();
// 		glTranslatef(0.0 ,0.0 + bodyHeight,0);
// 		if(isEnemy) Rect(0.0, 0.0, tailWidth, tailHeight, "darkred", 1.0, "black", "").draw();
// 		if(!isEnemy)Rect(0.0, 0.0, tailWidth, tailHeight, "darkgreen", 1.0, "black", "").draw();
//
// 	glPopMatrix();
// 	glPushMatrix();
// 		glTranslatef(0.0 + tailWidth/2.0 + tailRightWidth/2.0,
// 					0.0 + bodyHeight/2.0 + tailHeight,
// 					0.0);
// 		Rect(0.0, 0.0, tailRightWidth, tailRightHeight, "black", 1.0, "black", "").draw();
// 	glPopMatrix();
// 	glPushMatrix();
// 		glTranslatef(0.0 - tailWidth/2.0 - tailLeftWidth/2.0,
// 					0.0 + bodyHeight/2.0 + tailHeight,
// 					0.0);
// 		Rect(0.0, 0.0, tailLeftWidth, tailLeftHeight, "black", 1.0, "black", "").draw();
// 	glPopMatrix();
//
// 	//helice 1
// 	glPushMatrix();
// 		glTranslatef(0.0, 0.0,0.0);
// 		glRotatef(angleHelice, 0.0, 0.0,1.0);
// 		Rect(0.0, 0.0, heliceWidth, heliceHeight, "black", 1.0, "black","").draw();
// 	glPopMatrix();
//
// 	//helice 2
// 	glPushMatrix();
// 		glTranslatef(0.0, 0.0 ,0.0);
// 		glRotatef(angleHelice-90, 0.0, 0.0,1.0);
// 		Rect(0.0, 0.0, heliceWidth, heliceHeight, "black", 1.0, "black","").draw();
// 	glPopMatrix();
//
// 	//base helice
// 	glPushMatrix();
// 		glTranslatef(0.0 ,0.0 ,0);
// 		Circle(0.0, 0.0, raioHeliceBase, "gray", "").draw();
// 	glPopMatrix();
// }

// void drawGas(int gas, int tempoDeVoo, float arenaX, float arenaY){
// 	glPushMatrix();
// 		if(gas >= 0){
// 			glTranslatef(arenaX * 0.05 ,(arenaY * 0.95),0.0);
// 			glRotatef(180 ,0.0 ,0.0 ,1.0);
// 			glScalef(arenaX/1000, arenaY/1000,0.0);
// 			Rect(0.0, 0.0, 40.0, tempoDeVoo * 10, "blue", 1.0, "black","").drawGasBar();
// 			glTranslatef(0.0, (gas -1) *10,0.0);
// 			Rect(0.0,0.0,50.0,10.0,"",0.0,"","").drawGasIndicator();
// 		}
// 	glPopMatrix();
// }
//
// void Helicopter::draw(){
// 	if(flying) angleHelice = angleHelice + velHelice + 1.0;
// 	// helicopter
// 	glPushMatrix();
// 		glTranslatef(cX+gX, cY+gY, 0.0);
// 		glRotatef(angle, 0.0,0.0,1.0);
// 		if(!flying) glScalef(1.0/1.5,1.0/1.5,1.0/1.5);
// 		drawGun(angleGun, 0.0, -bodyHeight/2.0 + 5.0, angle);
// 		drawHelicopter(cX, cY, angle, angleHelice, flying, angleGun, isEnemy);
// 	glPopMatrix();
//
// 	// gas
// 	if(!isEnemy && flying){
// 		glPushMatrix();
// 			drawGas(gas,tempoDeVoo, arenaX, arenaY);
// 		glPopMatrix();
// 	}
// }

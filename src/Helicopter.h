#ifndef HELICOPTER_H
#define HELICOPTER_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include "Rect.h"
#include "Circle.h"
#include <GL/glut.h>
// #include "Shot.h"


using namespace std;

class Helicopter{
private:
	float velTiro;
	float velHelicoptero;
	float tempoDeVoo;
	float freqTiro;
	GLfloat gX;
	GLfloat gY;
	float cX, cY;
	GLfloat angle;
	float angleHelice;
	// bool flying;
	// bool isEnemy;
	// vector<Shot> shots;
	// float gunX, gunY;
	// float velHelice;
	// float arenaX, arenaY;
	// float gas;
	// float radius;
	// bool collided;
	// int rescuedObjects;
	// bool isDead;
	// bool isRotating;
	// float direction;

	// Rect body;
	// Rect gun;
	// float angleGun;
public:
	Helicopter();
	Helicopter(float freqTiro, float velHelicoptero, float cx, float cy);
	Helicopter(float velTiro, float velHelicoptero, float tempoDeVoo);
	void draw();
	void rotate(GLfloat value);
	void move(GLfloat value);
	// void drawEnemy();
    //
	// void moveHelice(float value);
	// Rect getGun();
	// void moveX(GLfloat value);
	// void rotateGun(float value);
	// void setFlying();
	// float getCurrentAngleGun();
	// float getGunPosY();
	// float getGunPosX();
	// float getAngle();
	// float getAngleGun();
	// float getTempoDeVoo();
	// bool getFlying();
	// float getVelHelicoptero();
	// void setArena(float aX, float aY);
	// void draw_gun();
	// void decGas();
	// float getFreqTiro();
	// float getVelTiro();
	// void setAngle(float a);
	// float getGas();
	// void setGas(float g);
	// float getRadius();
	// float getGx(); float getNextMoveX(float val); float getCx();
	// float getGy(); float getNextMoveY(float val); float getCy();
	// void setCollided(bool value); bool getCollided();
	// void setRescuedObjects(int value);
	// int getRescuedObjects();
	// void setIsDead(bool value);
	// bool getIsDead();
	// void setDirection(float value);
	// void setRotating(bool value);
	// bool getRotating();
	// float getDirection();
};
#endif

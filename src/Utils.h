#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
// #include "Helicopter.h"
using namespace std;

extern const float red[];
extern const float green[];
extern const float blue[];
extern const float gray[];
extern const float white[];
extern const float black[];
extern const float darkred[];
extern const float darkgreen[];

extern int keys[256];

void drawAxes();
void setKeyUp(unsigned char key, int x, int j);
void setKeyDown(unsigned char key, int x, int j);
// void init (float arenaX, float arenaY);
// void setKeyUp(unsigned char key, int x, int j);
// void setKeyDown(unsigned char key, int x, int j);
// bool checkDefeat(Helicopter player, float x, float y, vector<Shot> enemyShots);
// bool checkVictory(Helicopter player, int nObjects, float x, float y);
// bool onPosto(Helicopter player, Rect posto);
// bool onArena(Helicopter player, Rect arena, float displacement);
// bool checkCollision(float x, float y, float r, float a, float b, float c);
// int onEnemy(vector<Helicopter> enemies, int i);
// bool onObjetoResgate(Helicopter player, Circle objetosResgate);
// bool onPlayer(Helicopter player, Helicopter enemy);
// int wasShot(Helicopter h, vector<Shot> shots);
// int willCollide(Helicopter h1, Helicopter h2, float displacement);

#endif

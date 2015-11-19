#ifndef ARENA_H
#define AREHA_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include "Rect.h"
#include "Circle.h"
#include "Cube.h"
// #include "Helicopter.h"

using namespace std;

class Arena{
	private:
		Cube arenaBot;
		Cube arenaLeft;
		Cube arenaRight;
		Cube arenaFront;
		Cube arenaBack;
		Cube arenaTop;
		
		Rect arena;
		Rect postoAbastecimento;
		Circle jogador;
		vector<Circle> inimigos;
		vector<Circle> objetosResgate;
		GLuint texture;

	public:
		Arena();
		void readXMLArena(const char* path);
		void init();
		void draw();
		Rect getArena();
		// Rect getPostoAbastecimento();
		// Circle getJogador();
		// void drawArena(float x, float y);
		// vector<Circle> getInimigos();
		// vector<Circle> getObjetosResgate();
		// string verifyClick(int x, int y);
		// void collect(int i);
};

#endif

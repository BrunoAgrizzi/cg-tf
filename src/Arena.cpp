#include <GL/glut.h>
#include <string>
#include <vector>
#include "Arena.h"
#include "tinyxml2.h"
// #include "Helicopter.h"

using namespace std;
using namespace tinyxml2;

Arena::Arena(){}

void Arena::init(){

    arenaLeft = Cube();

  arenaBot.setTexturePath("../img/earth.bmp");
  arenaLeft.setTexturePath("../img/stars1.bmp");
  arenaRight.setTexturePath("../img/stars1.bmp");
  arenaFront.setTexturePath("../img/stars1.bmp");
  arenaBack.setTexturePath("../img/stars1.bmp");
  arenaTop.setTexturePath("../img/stars1.bmp");

  for(int j = 0; j < objetosResgate.size() ; j++){


      float objX = -arena.getWidth()/2 + objetosResgate.at(j).getCx() + objetosResgate.at(j).getR()/2;
      float objY = -arena.getWidth()/2 + objetosResgate.at(j).getCy() + objetosResgate.at(j).getR()/2;
      Cube c = Cube();
    //   cout << objetosResgate.at(j).getCx() << endl;
    //   c.setTranslation(300,15,200);
      c.setTranslation(objX, 15,objY);
      c.setScale(7,7,7);
      c.setTexturePath("../img/nic.bmp");
      objRes.push_back(c);
  }

  Cube c = Cube();
  float xPosto, yPosto;
  xPosto = -arena.getWidth()/2 + postoAbastecimento.getX() + postoAbastecimento.getWidth()/2;
  yPosto = -arena.getHeight()/2 + postoAbastecimento.getY() + postoAbastecimento.getHeight()/2;
  c.setTranslation(xPosto, 0, yPosto);
  c.setScale(postoAbastecimento.getWidth()/2, 5, postoAbastecimento.getHeight()/2);
  c.setTexturePath("../img/grass.bmp");
  postoAbs = c;

}

float Arena::getPlayerStartX(){
    return -arena.getWidth()/2 + postoAbastecimento.getX() + postoAbastecimento.getWidth()/2;
}
float Arena::getPlayerStartY(){
    return -arena.getHeight()/2 + postoAbastecimento.getY() + postoAbastecimento.getHeight()/2;
}

void Arena::draw(){
  glPushMatrix();
    arenaBot.setTranslation(0,0,0);
    arenaBot.setScale(arena.getWidth()/2,0.1,arena.getHeight()/2);
    arenaBot.draw();
  glPopMatrix();

  glPushMatrix();
    arenaLeft.setScale(arena.getWidth()/2,0.1,arena.getHeight()/2);
    arenaLeft.setRotation(-90);
    arenaLeft.setRotationAxis(0,0,1);
    arenaLeft.setTranslation((arena.getWidth())/2,arena.getWidth()/2,0);
    arenaLeft.draw();
  glPopMatrix();

  glPushMatrix();
  arenaRight.setScale(arena.getWidth()/2,0.1,arena.getHeight()/2);
  arenaRight.setRotation(90);
  arenaRight.setRotationAxis(0,0,1);
  arenaRight.setTranslation(-(arena.getWidth())/2,arena.getWidth()/2,0);
  arenaRight.draw();
  glPopMatrix();

  glPushMatrix();
    arenaFront.setScale(arena.getWidth()/2,0.1,arena.getHeight()/2);
    arenaFront.setRotation(-90);
    arenaFront.setRotationAxis(1,0,0);
    arenaFront.setTranslation(0,(arena.getHeight())/2,-arena.getHeight()/2);
    arenaFront.draw();
  glPopMatrix();

  glPushMatrix();
      arenaBack.setScale(arena.getWidth()/2,0.1,arena.getHeight()/2);
      arenaBack.setRotation(90);
      arenaBack.setRotationAxis(1,0,0);
      arenaBack.setTranslation(0,(arena.getHeight())/2,arena.getHeight()/2);
      arenaBack.draw();
  glPopMatrix();

  glPushMatrix();
      for(int j = 0; j < objRes.size() ; j++){
          objRes.at(j).draw();
      }
  glPopMatrix();

  glPushMatrix();
    postoAbs.draw();
  glPopMatrix();
}
Rect Arena::getArena(){
  return this->arena;
}
Rect Arena::getPostoAbastecimento(){
	return this->postoAbastecimento;
}


// void Arena::drawArena(float x, float y){
// 	glPushMatrix();
// 		glTranslatef(x/2.0, y/2.0,0.0);
// 		// arena
// 		arena.draw();
// 	glPopMatrix();
// 	glPushMatrix();
// 		glTranslatef(postoAbastecimento.getX() + postoAbastecimento.getWidth()/2.0,
// 			postoAbastecimento.getY() + postoAbastecimento.getHeight()/2.0,0.0);
// 		postoAbastecimento.draw();
// 	glPopMatrix();
//
// 	for(int j = 0; j < objetosResgate.size() ; j++){
// 		if(!objetosResgate.at(j).getCollected()){
// 		 	objetosResgate.at(j).draw();
// 		}
// 	}
// }

// void Arena::collect(int i){
// 	this->objetosResgate.at(i).setCollected(true);
// }
//
// Rect Arena::getArena(){
// 	return this->arena;
// }
//
//
// Circle Arena::getJogador(){
// 	return this->jogador;
// }
//
// vector<Circle> Arena:: getInimigos(){
// 	return this->inimigos;
// }
//
// vector<Circle> Arena::getObjetosResgate(){
// 	return this->objetosResgate;
// }

void Arena::readXMLArena(const char* path){
    cout << "Reading arena at: " << path << endl;
	XMLDocument doc;
	doc.LoadFile(path);

	XMLNode* svgObjs = doc.FirstChildElement("svg")->FirstChild();
	while(svgObjs != NULL){

		XMLElement * obj = svgObjs->ToElement();

		if(strcmp(obj->Attribute("id"),"Arena") == 0){
			this->arena = Rect(	atof(obj->Attribute("x")),
												atof(obj->Attribute("y")),
												atof(obj->Attribute("width")),
												atof(obj->Attribute("height")),
												obj->Attribute("fill"),
												atof(obj->Attribute("stroke-width")),
												obj->Attribute("stroke"),
												obj->Attribute("id"));
		}

		if(strcmp(obj->Attribute("id"),"PostoAbastecimento") == 0){
			this->postoAbastecimento = Rect(	atof(obj->Attribute("x")),
												atof(obj->Attribute("y")),
												atof(obj->Attribute("width")),
												atof(obj->Attribute("height")),
												obj->Attribute("fill"),
												atof(obj->Attribute("stroke-width")),
												obj->Attribute("stroke"),
												obj->Attribute("id"));
		}

		if(strcmp(obj->Attribute("id"),"Jogador") == 0){
			this->jogador = Circle(	atof(obj->Attribute("cx")),
									atof(obj->Attribute("cy")),
									atof(obj->Attribute("r")),
									obj->Attribute("fill"),
									obj->Attribute("id"));
		}

		if(strcmp(obj->Attribute("id"),"Inimigo") == 0){
			this->inimigos.push_back(Circle(	atof(obj->Attribute("cx")),
													atof(obj->Attribute("cy")),
													atof(obj->Attribute("r")),
													obj->Attribute("fill"),
													obj->Attribute("id")));
		}

		if(strcmp(obj->Attribute("id"),"ObjetoResgate") == 0){
			this->objetosResgate.push_back(Circle(	atof(obj->Attribute("cx")),
													atof(obj->Attribute("cy")),
													atoi(obj->Attribute("r")),
													obj->Attribute("fill"),
													obj->Attribute("id")));
		}

		svgObjs = svgObjs->NextSibling();
	}
    cout << "OK!" << endl;
}

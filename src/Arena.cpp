#include <string>
#include <vector>
#include "Arena.h"
#include "tinyxml2.h"
// #include "Helicopter.h"

using namespace std;
using namespace tinyxml2;

Arena::Arena(){}

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
// Rect Arena::getPostoAbastecimento(){
// 	return this->postoAbastecimento;
// }
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

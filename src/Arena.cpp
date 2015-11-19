#include <GL/glut.h>
#include <string>
#include <vector>
#include "Arena.h"
#include "tinyxml2.h"
// #include "Helicopter.h"

using namespace std;
using namespace tinyxml2;

Arena::Arena(){}

void Arena::addTexture(){

  GLfloat materialEmission[] = { 1.0, 1.0, 1.0, 1};
  GLfloat materialColorA[] = { 0.2, 0.2, 0.2, 1};
  GLfloat materialColorD[] = { 1.0, 1.0, 1.0, 1};
  GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1};
  GLfloat mat_shininess[] = { 100.0 };
  glColor3f(1,1,1);

  glMaterialfv(GL_FRONT, GL_EMISSION, materialEmission);
  glMaterialfv(GL_FRONT, GL_AMBIENT, materialColorA);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, materialColorD);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);


  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT  );//X
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );//Y

  glBindTexture (GL_TEXTURE_2D, this->texture);
  double textureS = 1; // Bigger than 1, repeat
  glBegin (GL_QUADS);
      glNormal3f(0,1,0);
      glTexCoord2f (0, 0);
      glVertex3f (-1, 0, -1);

      glNormal3f(0,1,0);
      glTexCoord2f (0, textureS);
      glVertex3f (-1, 0, +1);

      glNormal3f(0,1,0);
      glTexCoord2f (textureS, textureS);
      glVertex3f (+1, 0, +1);

      glNormal3f(0,1,0);
      glTexCoord2f (textureS, 0);
      glVertex3f (+1, 0, -1);
  glEnd();
}

void Arena::drawArena(){

  glPushMatrix();

    arenaBot.setTexturePath("../img/earth.bmp");
    arenaBot.setTranslation(0,0,0);
    arenaBot.setScale(arena.getWidth(),0,arena.getHeight());
    arenaBot.draw();
  glPopMatrix();

  glPushMatrix();
    arenaLeft.setTexturePath("../img/sun1.bmp");
    //arenaLeft.setScale(arena.getArena().getWidth(),0,arena.getArena().getHeight());
    glRotatef(90, 0,0,1);
    arenaLeft.setScale(50,0,50);

    arenaLeft.setTranslation(arena.getWidth()/2,arena.getHeight()/2,0);
    //arenaLeft.setTranslation(50,50,0);
    arenaLeft.draw();
  glPopMatrix();

}
void Arena::setTexture(GLuint tex){
    this->texture = tex;
}
GLuint Arena::getTexture(){
  return this->texture;
}
Rect Arena::getArena(){
  return this->arena;
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

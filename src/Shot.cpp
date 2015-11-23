#include "Shot.h"
#include <math.h>
using namespace std;

Shot::Shot(Circle c, float x, float y){
	this->circ = c;
	this->x = x;
	this->y = y;
}
Shot::Shot(Circle c){
	this->circ = c;
	this->x = 0.0;
	this->y = 0.0;
}

Shot::Shot(float x, float y, float angle, float angleHelicopter, float velTiro, float angleGun){
	this->circ = Circle(0.0, 0.0, 3.0, "blue", "");
	this->velTiro = velTiro;
	this->x = x;
	this->y = y;
	this->angle = angle;
	this->angleHelicopter = angleHelicopter;
	this->angleGun = angleGun;
	this->hitted = false;
}

Shot::Shot(Circle c, float ang){
}

void Shot::draw(){
	// this->x+= cos((angle -90.0)* 3.1415 / 180.0) * velTiro * 25;
	// this->y+= sin((angle -90.0)* 3.1415 / 180.0) * velTiro * 25;
    // this->z+= sin((ang))
	glPushMatrix();
		// glTranslatef(cos((angleHelicopter - 90.0) * 3.1415 / 180.0) * (/*bodyHeight/2.0*/ 6 - 5), sin((angle-angleGun - 90.0) * 3.1415 / 180.0) * (/*bodyHeight/2.0 */ 6- 5),0.0);
		glPushMatrix();
			// glTranslatef(this->x, this->y, 0.0);
			Cube c = Cube();
            c.setTexturePath("../img/sun1.bmp");
            c.setTranslation(x,0,y);
            c.setRotation(0);
            c.setScale(2,2,2);
            c.draw();
		glPopMatrix();
	glPopMatrix();
}

// void Shot::drawEnemyShot(float x, float y){
// 	this->x+= cos((angle -90.0)* 3.1415 / 180.0) * velTiro * 25;
// 	this->y+= sin((angle -90.0)* 3.1415 / 180.0) * velTiro * 25;
// 	glPushMatrix();
// 		glTranslatef(cos((angleHelicopter - 90.0) * 3.1415 / 180.0) * (bodyHeight/2.0 - 5), sin((angle-angleGun - 90.0) * 3.1415 / 180.0) * (bodyHeight/2.0 - 5),0.0);
// 		glPushMatrix();
// 			glTranslatef(this->x, this->y, 0.0);
// 			Circle(0.0, 0.0, 3.0, "blue", "").draw();
// 		glPopMatrix();
// 	glPopMatrix();
// }


float Shot::getAngle(){
	return this->angle;
}
Circle Shot::getCircle(){
	return this->circ;
}
float Shot::getX(){
	return x;
}
float Shot::getY(){
	return y;
}
bool Shot::getHitted(){
	return this->hitted;
};
void Shot::setHitted(bool value){
	this->hitted = value;
};

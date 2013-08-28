/*
 * datatypes.cpp
 *
 *  Created on: Aug 25, 2013
 *      Author: Alles Rebel
 */

#include "datatypes.h"

/*
 * Get magnitude of a 2D vector
 */
float Vec2::getMagnitude() {
	return sqrt(pow(x, 2) + pow(y, 2));
}

/*
 * Both important comparison operators == and !=
 */
bool Vec2::operator ==(const Vec2& rhs) {
	if (this->x - rhs.x >= FLT_EPSILON)
		return false;
	if (this->y - rhs.y >= FLT_EPSILON)
		return false;
	return true;
}
bool Vec2::operator !=(const Vec2& rhs) {
	if (this->x - rhs.x >= FLT_EPSILON)
		return true;
	if (this->y - rhs.y >= FLT_EPSILON)
		return true;
	return false;
}


/*
 * Constuctor - loads the image into the surface
 */
GraphicsObject::GraphicsObject(string fileName){
	frameHeight = 0;
	frameWidth = 0;
	currentFrame = 0;
	sprite = NULL;
	frameClip = NULL;
	location = NULL;
}

/*
 * Basic Draw Function for the object - doesn't do much other than that
 */
void GraphicsObject::draw(){
	SDL_BlitSurface(sprite,frameClip,SDL_GetVideoSurface(),location);
}

void GraphicsObject::setFrame(int number){

}

Figure::Figure(string fileName):GraphicsObject(fileName){

}



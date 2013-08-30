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
 * Constructor - loads the image into the surface
 * TODO: Make sequences - eg one for walking, one for jumping, etc
 * TODO: Code the sequences so that auto pick the right frame on draw
 * Probably did this function totally wrong :(
 */
GraphicsObject::GraphicsObject(SDL_Surface* sprite, int frameH, int frameW, int frameInit, SDL_Rect loc){
	frameHeight = frameH;
	frameWidth = frameW;
	currentFrame = frameInit;
	this->sprite = sprite;

	location = new SDL_Rect;
	*location = loc;

	//check if sprite is spirte sheet
	if(sprite->w == frameW && sprite->h == frameH){
		sheet = false;
	}

	if(sheet){
		//so the surface is a sprite sheet, get init frame
		frameClip = new SDL_Rect;
		//TODO: support more than one strip in function
		setFrame(frameInit);
		currentFrame = frameInit;
	}
	else{
		frameClip = NULL;
	}
}

/*
 * Basic Draw Function for the object - doesn't do much other than that
 * Figures out what the next frame should be
 * We should put the Frames in a queue though. ( and time based )
 */
void GraphicsObject::draw(){
	SDL_BlitSurface(sprite,frameClip,SDL_GetVideoSurface(),location);
	if(sheet){
		//TODO: make a sort of map queue as a private array
		currentFrame++;
		if(currentFrame*frameWidth > sprite->w){
			currentFrame = 0;
		}

		//apply new clipping rect
		setFrame(currentFrame);
	}
}

/*
 * Set current clip rect based on frame number given
 * @param int Number of desired display frame
 */
void GraphicsObject::setFrame(int number){
	int x = frameWidth*number;
	int y = 0;	//TODO: make the clip 2 layers maybe? For better organization of sheets

	int w = frameWidth;
	int h = frameHeight;

	frameClip = new SDL_Rect;

	frameClip->x = x;
	frameClip->y = y;
	frameClip->h = h;
	frameClip->w = w;
}

/*
 * Returns the locations of the object, in SDL coords
 * Conversion required if being used for vec2 positions
 */
SDL_Rect GraphicsObject::getPosition() {
	//returns a copy of the current location
	SDL_Rect copy = *location;
	return copy;
}

/*
 * Create an AABB based on object properties
 * Modify the init AABB based on current position
 */
AABB* GraphicsObject::getAABB() {

}


/*
 * Sets an object's position in SDL_Coords
 * Make sure Vecs have been converted to SDL_ Rects
 */
void GraphicsObject::setPosition(SDL_Rect newPosition){
	*location = newPosition;
}

/*
 * Figure constuctor. currently doesn't do anything
 * Uses the C++ equalivant of super
 */
Figure::Figure(SDL_Surface* sprite, int frameH, int frameW, int frameInit, SDL_Rect loc):GraphicsObject(sprite,frameH, frameW,frameInit,loc){

	
}

AABB Figure::generateAABBs() {


}

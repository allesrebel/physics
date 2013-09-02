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
	if (this->x - rhs.x >= FLT_EPSILON) return false;
	if (this->y - rhs.y >= FLT_EPSILON) return false;
	return true;
}
bool Vec2::operator !=(const Vec2& rhs) {
	if (this->x - rhs.x >= FLT_EPSILON) return true;
	if (this->y - rhs.y >= FLT_EPSILON) return true;
	return false;
}

/*
 * Constructor - loads the image into the surface
 * Does not creat deep copies of objects passed to it! (make sure you send in data as pointers)
 * TODO: Make sequences - eg one for walking, one for jumping, etc
 * TODO: Code the sequences so that auto pick the right frame on draw
 * TODO: maybe make this functino go through the data and do memcopy on them? (might be tough for physicsobjects)
 * Probably did this function totally wrong :(
 */
GraphicsObject::GraphicsObject(SDL_Surface* sprite, int frameH, int frameW, int frameInit, SDL_Rect loc,
		PhysicsObject* pO = NULL) {
	frameHeight = frameH;
	frameWidth = frameW;
	currentFrame = frameInit;
	this->sprite = sprite;

	location = new SDL_Rect;
	*location = loc;

	//check if sprite is spirte sheet
	if (sprite->w == frameW && sprite->h == frameH) {
		sheet = false;
	}

	if (sheet) {
		//so the surface is a sprite sheet, get init frame
		frameClip = new SDL_Rect;
		//TODO: support more than one strip in function
		setFrame(frameInit);
		currentFrame = frameInit;
	}
	else {
		frameClip = NULL;
	}

	if (pO != NULL) {
		objectProps = pO;
	}
}

/*
 * Basic Draw Function for the object - doesn't do much other than that
 * Figures out what the next frame should be
 * We should put the Frames in a queue though. ( and time based )
 */
void GraphicsObject::draw() {
	SDL_BlitSurface(sprite, frameClip, SDL_GetVideoSurface(), location);
	if (sheet) {
		//TODO: make a sort of map queue as a private array
		currentFrame++;
		if (currentFrame * frameWidth > sprite->w) {
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
void GraphicsObject::setFrame(int number) {
	int x = frameWidth * number;
	int y = 0; //TODO: make the clip 2 layers maybe? For better organization of sheets

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
 * Deconstructor for the class
 * destories allocated memory for this object
 */
GraphicsObject::~GraphicsObject() {
	delete location;
	objectProps->clear();
	delete objectProps;
	delete frameClip;
	SDL_FreeSurface(sprite);
}

/*
 * Create an AABB based on object properties
 * Modify the init AABB based on current position
 * and current frame being rendered
 */
AABB* GraphicsObject::getAABB() {
	//check if there are any physics associated with this object
	if (objectProps == NULL) {
		return NULL;
	}

	//object has physical properties, but no AABB. Not effected by collisions
	if (objectProps->initAABBs.empty()) {
		return NULL;
	}

	//return the AABB associated with this frame
	//Note, could still be NULL
	try {
		return objectProps->initAABBs.at(currentFrame);
	}
	catch (exception& e) {
		//is definitely a out of bounds exception
		return NULL;
	}
}

/*
 * Sets an object's position in SDL_Coords
 * Make sure Vecs have been converted to SDL_ Rects
 */
void GraphicsObject::setPosition(SDL_Rect newPosition) {
	*location = newPosition;
}

/*
 * Figure constuctor. currently doesn't do anything
 * Uses the C++ equalivant of super
 */
Figure::Figure(SDL_Surface* sprite, int frameH, int frameW, int frameInit, SDL_Rect loc) {

}

/*
 * Generate AABB's for all the graphic objects attached to this figure
 *  TODO: Should these ignore collisions with each other?
 */
vector<AABB*> Figure::generateAABBs() {
	vector<AABB*> result;
	for (int i = 0; i < (int) gObjects.size(); i++) {
		AABB* currentObject = gObjects[i]->getAABB();
		if (currentObject != NULL) {
			result.push_back(currentObject);
		}
	}

	return result;
}

/*
 * Method to clear information AABB information stored in the
 * Struct.
 */
void PhysicsObject::clear() {
	for (int i = 0; i < (int) initAABBs.size(); i++) {
		delete initAABBs[i];
	}
	initAABBs.clear();
}

/*
 * Get the graphics object associated with this AABB*
 * After collision detection, it may be needed to
 * do location modification
 * Returns NULL if there isn't any AABB associated
 */
GraphicsObject* Figure::getGraphicsObject(AABB* seeking) {
	for (int i = 0; i < (int) gObjects.size(); i++) {
		if (gObjects[i]->getAABB() == seeking) {
			return gObjects[i];
		}
	}

	return NULL;
}

PhysicsObject::PhysicsObject(float m, float res, float dens, Vec2 vel) {
	mass = m;

	if (m == 0) invMass = 0;
	else invMass = 1 / m;

	resitution = res;
	density = dens;
	velocity = vel;
}

/*
 * Multiplcation operator. Multiplies a vector with a scalar;
 */
Vec2 Vec2::operator* (float scalr) {
	Vec2 newVec = {this->x * scalr, this->y * scalr};
	return newVec;
}

/*
 * Addition operator, just adds together two vectors's components
 * and returns a new vector with the result
 */
Vec2 Vec2::operator +(const Vec2& other) {
	Vec2 result = { this->x + other.x , this->y + other.y};
	return result;
}

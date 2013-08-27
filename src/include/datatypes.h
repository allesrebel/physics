/*
 * datatypes.h
 *
 *  Created on: Aug 25, 2013
 *      Author: Alles Rebel
 */

#ifndef DATATYPES_H_
#define DATATYPES_H_

#include <SDL/SDL.h>
#include <cmath>
#include <cfloat>
#include <string>

using namespace std;

/*
 * simple 2d position vector
 */
struct Vec2{
	float x;
	float y;
	//bool operator=(const Vec2&); auto gen by compiler with 5 other func
	bool operator==(const Vec2&);
	bool operator!=(const Vec2&);
	float getMagnitude();
};

/*
 * 	Axis Aligned Bounding Boxes - basically a box
 *	that we will be checking for collisions in.
 */
struct AABB{
	Vec2 tLeftCorner; 	//top left
	Vec2 tRightCorner;	//top right
	Vec2 bLeftCorner;	//bottom left
	Vec2 bRightCorner;	//bottom right
};

/*
 * Class to represent all assests loaded
 * from images. Text isn't counted here
 * TODO: Load from a file
 * TODO: Possibly a priority system to limit overlap
 */
class GraphicsObject{
public:
	GraphicsObject(string);
	~GraphicsObject();
	void draw();
public:
	SDL_Surface* sprite;	//total sheet
	SDL_Rect* frame;		//clip rect
	SDL_Rect* location;		//location to blit to
};

/*
 * Figure class - basically combines
 * data needed for physics and graphics engines
 * TODO: More stuff here someday
 */
class Figure{
public:
	Figure();

	AABB generateAABB();
	SDL_Rect* getFrame();
public:
	SDL_Rect* frame;

public:
	Vec2 velocity;
	Vec2 force;
};

/*
 * Simple Circle primitive - nothing special about it yet
 */
struct Circle{
	float r;	//radius
	Vec2 pos;	//position vec
};

#endif /* DATATYPES_H_ */

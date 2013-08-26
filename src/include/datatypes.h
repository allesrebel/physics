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
 *	that we will be checking for collisions in. Can't
 *	rotate or do anything special (probably will be removed)
 */
struct AABB{
	Vec2 leftCorner; 	//top left
	Vec2 rightCorner;	//bottom right
};

/*
 * Simple Circle primitive - nothing special about it yet
 */
struct Circle{
	float r;	//radius
	Vec2 pos;	//position vec
};

#endif /* DATATYPES_H_ */

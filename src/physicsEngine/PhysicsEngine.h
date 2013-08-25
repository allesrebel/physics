/*
 * PhysicsEngine.h
 *
 *  Created on: Aug 24, 2013
 *      Author: Alles Rebel
 */

#ifndef PHYSICSENGINE_H_
#define PHYSICSENGINE_H_

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
 *	rotate or do anything special
 */
struct AABB{
	Vec2 leftCorner; 	//top left
	Vec2 rightCorner;	//bottom right
};

/*
 * Simple Circle Struct
 */
struct Circle{
	float r;	//radius
	Vec2 pos;	//position vec
};

class PhysicsEngine {
public:
	PhysicsEngine();
	static bool checkCollisionAABB(AABB, AABB);
	static bool checkCollisionCircle(Circle, Circle);
	//math helper functions
	static float getMagnitude(Vec2);
	static Vec2 makeUnitVector(Vec2);
	static Vec2 getNormal(Vec2, Vec2);
	static float distance(Vec2, Vec2);
	virtual ~PhysicsEngine();
};

#endif /* PHYSICSENGINE_H_ */

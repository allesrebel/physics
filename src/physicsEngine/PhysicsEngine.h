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
#include "..\include\datatypes.h"

class PhysicsEngine {
public:
	PhysicsEngine();
	virtual ~PhysicsEngine();

	//experimentation
	static bool checkCollisionAABB(AABB, AABB);
	static bool checkCollisionCircle(Circle, Circle);

	//generic case with just shapes


	//math helper functions
	static float getMagnitude(Vec2);
	static float dot(Vec2, Vec2);
	static Vec2 makeUnitVector(Vec2);
	static Vec2 getNormal(Vec2, Vec2);
	static float distance(Vec2, Vec2);
};

#endif /* PHYSICSENGINE_H_ */

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

	//core functionality
	static void applyVelocity(Vec2*, Vec2, float);
	static void applyAccel(Vec2*, Vec2, float);

	//experimentation
	static bool checkCollisionAABB(AABB, AABB);
	static bool checkCollisionCircle(Circle, Circle);

	//generic case with just shapes


	//math helper functions
	static float dot(Vec2, Vec2);
	static Vec2 makeUnitVector(Vec2);
	static Vec2 addVectors(Vec2, Vec2);
	static Vec2 getNormal(Vec2, Vec2);
	static float distance(Vec2, Vec2);
};

#endif /* PHYSICSENGINE_H_ */

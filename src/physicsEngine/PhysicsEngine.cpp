/*
 * PhysicsEngine.cpp
 *
 *  Created on: Aug 24, 2013
 *      Author: Alles Rebel
 */

#include "PhysicsEngine.h"

PhysicsEngine::PhysicsEngine() {
	// TODO Auto-generated constructor stub

}

PhysicsEngine::~PhysicsEngine() {
	// TODO Auto-generated destructor stub
}

/*
 * Checks if two AABB objects have collided
 */
bool PhysicsEngine::checkCollisionAABB(AABB a, AABB b) {
	//Applying the SAT theorem, if there is a axis between
	//two objects, then they are not touching

	//check if there's a line in the y direction (a gap in the x's)
	if (a.bRightCorner.x < b.tLeftCorner.x || a.tLeftCorner.x > b.bRightCorner.x)
		return false;

	//check if there's a line in the x direction (a gap in in the y's)
	if (a.bRightCorner.y < b.tLeftCorner.y || a.tLeftCorner.y > b.bRightCorner.y)
		return false;

	//if there is no seperating axis, then they must have collided
	return true;
}

bool PhysicsEngine::checkCollisionCircle(Circle a, Circle b) {
	float r = a.r + b.r;
	r = pow(r, 2); //to get rid of sqrt
	return r < pow((a.pos.x + b.pos.x), 2) + pow((a.pos.y + a.pos.y), 2);
}

/*
 * Takes a vector and makes produces a unit vector
 */
Vec2 PhysicsEngine::makeUnitVector(Vec2 a) {
	float mag = a.getMagnitude();
	a.x = a.x / mag;
	a.y = a.y / mag;
	return a;
}


/*
 * Returns the normal unit vector assuming clockwise rotation
 */
Vec2 PhysicsEngine::getNormal(Vec2 a, Vec2 b) {
	float dx = b.x - a.x;
	float dy = b.y - a.y;

	//applying [0 1; -1 0] rotation matrix
	Vec2 newVector = { -dy, dx };

	//convert to unit vector
	newVector = makeUnitVector(newVector);

	return newVector;
}


/*
 * Standard 2D Dot Product
 */
float PhysicsEngine::dot(Vec2 a, Vec2 b){
	return a.x * b.x + a.y * b.y;
}

/*
 * Simple distance calcuation using 2D vectors
 */
float PhysicsEngine::distance(Vec2 a, Vec2 b) {
	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

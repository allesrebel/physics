//============================================================================
// Name        : physics.cpp
// Author      : Alles Rebel
// Version     :
// Copyright   : none i guess?
// Description : Vector Based Physics Engine Testing
//============================================================================

#include <iostream>
#include <SDL/SDL.h>
#include <cfloat>

#include "physicsEngine/PhysicsEngine.h"

using namespace std;

void testDistance();
void testNormals();
void testMagnitude();
void testCollisions();
void testVectorMath();

int main(int argc, char* args[]) {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!

	cout<<"Performing test functions!"<<endl;
	testVectorMath();
	testCollisions();
	cout<<"All tests completed!"<<endl;

	return 0;
}

//Testing collisions
void testCollisions() {
	/*
	 * This requires c++11 standard, so make sure that's on!
	 */
	Vec2 newVec = { 0, 0 };
	Vec2 another = { 10, 10 };
	AABB newShape = { newVec, another };

	newVec = {11, 11};
	another = {15, 15};
	AABB anotherShape = { newVec, another };

	if (PhysicsEngine::checkCollisionAABB(newShape, anotherShape)) {
		cout << "Should have not tested true for a collision, error!" << endl;
	}

	newVec = {9,9};
	anotherShape = {newVec, another};

	if (!PhysicsEngine::checkCollisionAABB(anotherShape, newShape)) {
		cout << "Tested false, when there should have been a collision, error!"
				<< endl;
	}
}

//testing VectorMath stuff
void testVectorMath() {
	testDistance();
	testMagnitude();
	testNormals();
}

//testing Magnitude
void testMagnitude() {
	Vec2 newVec = { 0, 1 };
	float mag = newVec.getMagnitude();
	if (mag - 1 >= FLT_EPSILON) {
		printf("Error in magnitude calculation! %f vs %d \n", mag, 1);
	}
	Vec2 newVec2 = { 1, 1 };
	mag = newVec2.getMagnitude();
	if (fabs(mag - sqrt(2)) >= FLT_EPSILON) { //Difference is greater than error allowable
		printf("Error in magnitude function! %f vs %f \n", mag, sqrt(2));
	}
}

//testing normal gen
void testNormals(){
	Vec2 newvec = { 1, 0};
	Vec2 orgin = {0, 0};
	Vec2 norm = { 0, 1};
	Vec2 result = PhysicsEngine::getNormal(orgin,newvec);
	if(result != norm){
		printf("Error in getNormal function - result incorrect! \n");
		printf("%f, %f for vec1 %d, %d expected \n",result.x, result.y, 0, 1);
	}
}

//Testing Functions
void testDistance() {
	Vec2 newVec = { 0, 0 };
	Vec2 another = { 1, 1 };
	float distComputed = 0;
	distComputed = PhysicsEngine::distance(newVec, another);
	if (fabs(distComputed - sqrt(2)) >= FLT_EPSILON) { //Difference is greater than error allowable
		printf("Error in distance function! %f vs %f \n", distComputed,
				sqrt(2));
	}
}

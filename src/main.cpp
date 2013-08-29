//============================================================================
// Name        : physics.cpp
// Author      : Alles Rebel
// Version     :
// Copyright   : none i guess?
// Description : Vector Based Physics Engine Testing
//============================================================================

#include <iostream>
#include <cfloat>
#include <vector>

#include "include/datatypes.h"				//primitive data types, and containers
#include "physicsEngine/PhysicsEngine.h"	//physics engine *(just for testing)
#include "graphicsEngine/GraphicsEngine.h"	//graphics engine (just for testing)
#include "gameEngine/GameEngine.h"			//game engine
using namespace std;

void testDistance();
void testNormals();
void testMagnitude();
void testCollisions();
void testDotProduct();
void testVectorMath();

void testGraphicObjects(GraphicsEngine&);
void testRects(GraphicsEngine&);
void testText(GraphicsEngine&);
void testBG(GraphicsEngine&);
void testGraphics();

void waitForPress();

int main(int argc, char* args[]) {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!

	cout << "Performing test functions!" << endl;
	testVectorMath();
	testCollisions();
	cout << "All tests completed!" << endl;

	cout << "Testing Graphics Stuff" << endl;
	testGraphics();

	return 0;
}

//simple event, wait for key press to continue with test
void waitForPress() {
	bool done = false;
	while (!done) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_KEYDOWN) {
				done = true;
			} else if (event.type == SDL_QUIT) {
				exit(0);
			}
		}
	}
}

//graphics Testing
void testGraphics() {
	GraphicsEngine engine;

	printf("Starting visual background test;\n");
	testBG(engine);
	printf("Starting visual text test; \n");
	testText(engine);
	printf("Starting visual rects test; \n");
	testRects(engine);
	printf("Testing the graphics objects \n");
	testGraphicObjects(engine);
}

/*
 * Testing the graphics object class to see if animations work
 * like they are suppose to
 */
void testGraphicObjects(GraphicsEngine& engine) {
	vector<GraphicsObject> objects; //container for objects to render

	SDL_Surface* mySheetTest = SDL_LoadBMP("../res/mysheet.bmp");
	SDL_Rect myLoc = { 100, 100, 0, 0 };
	GraphicsObject* newObject;
	newObject = new GraphicsObject(mySheetTest, 100, 100, 0, myLoc);

	bool done = false;
	while (!done) {
		newObject->draw();
		engine.refreshScreen();

		SDL_Event event;
		while(SDL_PollEvent(&event)){
			if(event.type == SDL_KEYDOWN){
				done = true;
			}
			else if(event.type == SDL_QUIT){
				done = true;
			}
		}
	}
}

void testBG(GraphicsEngine& engine) {
	engine.refreshScreen(engine.black);
	waitForPress();
	engine.refreshScreen(engine.white);
	waitForPress();
	engine.refreshScreen(engine.red);
	waitForPress();
	engine.refreshScreen(engine.green);
	waitForPress();
	engine.refreshScreen(engine.blue);
	waitForPress();
	engine.refreshScreen(engine.black); //to display the blue in memory
	waitForPress();
}

//testing text rendering and vector conversion
void testText(GraphicsEngine& engine) {
	engine.blitText("Hellow World, this is Black", 0, 300, engine.black);
	engine.blitText("Hellow world, this is white", 0, 280, engine.white);
	engine.blitText("Hellow Pizza, this is red", 0, 260, engine.red);
	engine.blitText("Hey there, this be green", 0, 240, engine.green);
	engine.blitText("That's all world, this is blue", 0, 220, engine.blue);
	engine.refreshScreen(); //display text
	waitForPress();
}

//testing rect gen //actually testing images
void testRects(GraphicsEngine& engine) {
	engine.blitImage(0, 100);
	engine.blitImage(250, 100);
	engine.blitImage2(50, 200);
	engine.refreshScreen();
	waitForPress();
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
	testDotProduct();
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

//testing dot product
void testDotProduct() {
	Vec2 newvec = { 10, 10 };
	Vec2 orgin = { 0, 0 };
	Vec2 xHat = { 1, 0 };

	float result = PhysicsEngine::dot(orgin, xHat);
	if (result != 0) {
		printf("Error in dot product, returned non zero! \n");
	}

	result = PhysicsEngine::dot(xHat, newvec);
	if (result != 10) {
		printf("Error in dot product, should have been 10! got %f", result);
	}
}

//testing normal gen
void testNormals() {
	Vec2 newvec = { 1, 0 };
	Vec2 orgin = { 0, 0 };
	Vec2 norm = { 0, 1 };
	Vec2 result = PhysicsEngine::getNormal(orgin, newvec);
	if (result != norm) {
		printf("Error in getNormal function - result incorrect! \n");
		printf("%f, %f for vec1 %d, %d expected \n", result.x, result.y, 0, 1);
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

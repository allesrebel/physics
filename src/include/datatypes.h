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
#include <vector>

using namespace std;

/*
 * simple 2d position vector
 */
struct Vec2 {
	float x;
	float y;
	//bool operator=(const Vec2&); auto gen by compiler with 5 other func
	Vec2 operator+(const Vec2&);
	Vec2 operator* (float);
	bool operator==(const Vec2&);
	bool operator!=(const Vec2&);
	float getMagnitude();
};

/*
 * 	Axis Aligned Bounding Boxes - basically a box
 *	that we will be checking for collisions in.
 *	I don't think we'll be supporting circles?
 */
struct AABB {
	Vec2 tLeftCorner; 	//top left
	Vec2 tRightCorner;	//top right
	Vec2 bLeftCorner;	//bottom left
	Vec2 bRightCorner;	//bottom right
	Vec2 Position;		//middle of the AABB
};

/*
 * Physics object
 * These will be containers for the the physics
 * properties of an object
 * To be used in the physics engine
 *
 */
struct PhysicsObject {
	PhysicsObject(float m = 0, float res = 0, float dens = 0, Vec2 vel = {0,0});
	float mass;
	float invMass;

	float resitution;
	float density;

	Vec2 velocity;

	vector<AABB*> initAABBs;	//AABBs for given states. Access with frame num
	void clear();
};

/*
 * Class to represent all assests loaded
 * from images. Text isn't counted here
 * The figure will probably be composed of
 * a ton of these
 * Each will be specifying it's own hit box (AABB)
 * only if physics applys to the object
 * TODO: Load from a file
 * TODO: Possibly a priority system to limit overlap
 */
class GraphicsObject {
	public:
	GraphicsObject(SDL_Surface*, int, int, int, SDL_Rect, PhysicsObject*);
	~GraphicsObject();
	void draw();
	void setPosition(SDL_Rect);
	SDL_Rect getPosition();
	void setFrame(int);

	AABB* getAABB();

	//pointer to where physics for this object is, if it has physic properties
	PhysicsObject* objectProps;

	public:
	SDL_Surface* sprite;	//total sheet
	SDL_Rect* frameClip;		//clip rect
	SDL_Rect* location;		//location to blit to

	public:
	//cliping information
	int currentFrame;
	int frameWidth;	//properties of a single clip
	int frameHeight;	//properties of a single clip
	bool sheet;
};

/*
 * Figure class - basically combines
 * data needed for physics and graphics engines
 * TODO: More stuff here someday
 */
class Figure{
	public:
	Figure(SDL_Surface*, int, int, int, SDL_Rect);

	vector<AABB*> generateAABBs();
	GraphicsObject* getGraphicsObject(AABB*);
	public:
	//local data
	vector<GraphicsObject*> gObjects; //graphic objects contained in this figure

	public:
	PhysicsObject physicalProp;
};

/*
 * Simple Circle primitive - nothing special about it yet
 */
struct Circle {
	float r;	//radius
	Vec2 pos;	//position vec
};

#endif /* DATATYPES_H_ */

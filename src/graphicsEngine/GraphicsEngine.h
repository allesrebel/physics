/*
 * graphicsEngine.h
 *
 *  Created on: Aug 25, 2013
 *      Author: Alles Rebel
 */

#ifndef GRAPHICSENGINE_H_
#define GRAPHICSENGINE_H_

#include <SDL/SDL.h>
#include "../include/datatypes.h"

// window defaults
#define BPP 8
#define WIDTH 640
#define HEIGHT 480

class GraphicsEngine {
public:
	GraphicsEngine();
	~GraphicsEngine();
};

#endif /* GRAPHICSENGINE_H_ */

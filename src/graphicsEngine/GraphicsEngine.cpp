/*
 * graphicsEngine.cpp
 *
 *  Created on: Aug 25, 2013
 *      Author: Alles Rebel
 */

#include "GraphicsEngine.h"

GraphicsEngine::GraphicsEngine() {
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_SetVideoMode(WIDTH, HEIGHT, BPP, SDL_HWSURFACE);
}

GraphicsEngine::~GraphicsEngine() {
	SDL_Quit();
}


/*
 * graphicsEngine.h
 *
 * 	Running on modified Graphics Engine
 * 	No system for draw order - bare engine
 * 	Basically a SDL wrapper
 *
 *	Most functions are better documented in the
 *	cpp file. (Formal Documentation to come)
 *
 * 	Depends on SDL, SDL_ttf
 *
 *  Created on: Aug 25, 2013
 *      Author: Alles Rebel
 */

#ifndef GRAPHICSENGINE_H_
#define GRAPHICSENGINE_H_

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

#include "../include/datatypes.h"	//for custom data types
using namespace std;

/*
 * Universal Color Datatype!
 */
struct Color {
	Uint32 pixelColor;	//pixel format
	SDL_Color RGBColor;	//RGB format
};

/*
 * Utilities - SDL conversion stuff
 */
SDL_Rect toRect(Sint16, Sint16, Uint16, Uint16);

class GraphicsEngine {
public:
	GraphicsEngine();
	~GraphicsEngine();

public:
	void setupEndian(); //8 bits (FF) per color in correct order

public:
	//core functions
	Color getColor(Uint8, Uint8, Uint8);

public:
	//data creation
	SDL_Surface* createRect(SDL_Rect, Color);
	TTF_Font* loadFont(string, int);

public:
	//tools and utilities
	void applyColorKey(SDL_Surface*, Color);
	SDL_Rect convertToRect(Vec2);

public:
	//defaults and debugging stuffs
	void setupFonts();
	void setupColors();
	TTF_Font* getDefaultFont();

	//Enum of Colors defaults to starting with 0
	enum DefaultColors {
		black, white, red, green, blue
	};

	//cached colors, for easy access
	Color colors[5];
	vector<TTF_Font*> fonts;

	//debugging functions
	void blitText(string, int, int, DefaultColors);
	void blitRect(int, int, DefaultColors);
	void refreshScreen(DefaultColors color = black);

private:
	//bit masks, how the colors are actually represented in memory
	Uint32 rmask, gmask, bmask, amask;
	const SDL_VideoInfo* vidInfo; //cached info
public:
	// window defaults
	int BPP =  8;
	int WIDTH =  640;
	int HEIGHT =  480;
};

#endif /* GRAPHICSENGINE_H_ */

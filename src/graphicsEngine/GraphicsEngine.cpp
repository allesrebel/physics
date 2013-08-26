/*
 * graphicsEngine.cpp
 *
 * 	Running on modified Graphics Engine
 * 	No system for draw order - bare engine
 *
 * 	Depends on SDL, SDL_ttf
 *
 *  Created on: Aug 25, 2013
 *      Author: Alles Rebel
 */

#include "GraphicsEngine.h"

/*
 * Utilities
 */
SDL_Rect toRect(Sint16 x, Sint16 y, Uint16 h, Uint16 w) {
	SDL_Rect newRect = { x, y, h, w };
	return newRect;
}

/*
 * Initialize Engine - and libraries used
 */
GraphicsEngine::GraphicsEngine() {
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();

	//load defaults
	SDL_SetVideoMode(WIDTH, HEIGHT, BPP, SDL_HWSURFACE || SDL_DOUBLEBUF);

	setupEndian();
	setupFonts();
	setupColors();
	vidInfo = SDL_GetVideoInfo(); 	//pre cache
}

GraphicsEngine::~GraphicsEngine() {
	TTF_Quit();
	SDL_Quit();
}

//Get Default Font
TTF_Font* GraphicsEngine::getDefaultFont() {
	return fonts.at(0);
}

/*
 * Load default fonts - for easy debugging
 */
void GraphicsEngine::setupFonts() {
	//load default font
	fonts.push_back(TTF_OpenFont("bluehigh.ttf", 20));
	if (fonts.at(0) == NULL) {
		printf("Error opening font! %s", TTF_GetError());
	}

}

/*
 * Load default colors
 */
void GraphicsEngine::setupColors() {
	colors[0] = getColor(0, 0, 0);		//black
	colors[1] = getColor(255, 255, 255);	//white
	colors[2] = getColor(255, 0, 0);	//red
	colors[3] = getColor(0, 255, 0);	//green
	colors[4] = getColor(0, 0, 255);		//blue
}

// Creates color container with the given colors
Color GraphicsEngine::getColor(Uint8 r, Uint8 g, Uint8 b) {
	Uint32 pix = SDL_MapRGB(SDL_GetVideoInfo()->vfmt, r, g, b);
	SDL_Color rgb = { r, g, b };
	Color newColor = { pix, rgb };
	return newColor;
}

//Creates a custom rectangle surface
SDL_Surface* GraphicsEngine::createRect(SDL_Rect rect, Color color) {
	SDL_Surface* myRect = SDL_CreateRGBSurface(SDL_HWSURFACE, rect.w, rect.h,
			vidInfo->vfmt->BitsPerPixel, vidInfo->vfmt->Rmask,
			vidInfo->vfmt->Gmask, vidInfo->vfmt->Bmask, vidInfo->vfmt->Amask);
	SDL_FillRect(myRect, NULL, color.pixelColor);
	return myRect;
}

//loads a font with a  file path and desired font point size
TTF_Font* GraphicsEngine::loadFont(string filename, int ptsize) {
	TTF_Font* newFont = TTF_OpenFont(filename.c_str(), ptsize);
	if (newFont == NULL) {
		printf("Error in loadFont! Font %s wasn't found! \n", filename.c_str());
	}
	return newFont;
}

/*
 * Apply a simple color key, producing a surface with an alpha ch
 */
void GraphicsEngine::applyColorKey(SDL_Surface* src, Color colorkey) {
	SDL_SetColorKey(src, SDL_SRCCOLORKEY, colorkey.pixelColor);
}

/*
 * A Conversion between SDL_Rect and Vec2
 * Uses a simple transform to between Vec2 -> SDL_Rect and SDL_Rect -> Vec2
 * Only does position, doesn't do SDL_Rect's height or width
 * Relies on accurate Window Height
 */
SDL_Rect GraphicsEngine::convertToRect(Vec2 src){
	//some rounding errors here (src.y and src.x are floats)
	int oppositeY = src.y * -1;
	int maxY = HEIGHT;

	SDL_Rect newRect = {(Sint16)src.x, (Sint16)(maxY+oppositeY), 0 ,0};
	return newRect;
}

//Set up Endian, the way the pixels are represented in memory
//varies from machine to machine
void GraphicsEngine::setupEndian() {
	if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
		rmask = 0xff000000;
		gmask = 0x00ff0000;
		bmask = 0x0000ff00;
		amask = 0x000000ff;
	} else {
		rmask = 0x000000ff;
		gmask = 0x0000ff00;
		bmask = 0x00ff0000;
		amask = 0xff000000;
	}
}

/*
 * Blit Text - used for debugging, making sure everything works.
 * Draws only to current screen in memory
 * Specify string to print, and location. Color not required.
 */
void GraphicsEngine::blitText(string text, int x , int y, DefaultColors index = black) {
	SDL_Surface* textSurf = NULL;
	textSurf = TTF_RenderText_Blended(getDefaultFont(), text.c_str(), colors[index].RGBColor);
	if(textSurf == NULL){
		printf("Error creating text surf: %s! \n",text.c_str());
	}

	//format for display
	SDL_Surface* finalSurface = SDL_DisplayFormatAlpha(textSurf);

	Vec2 myPos = {(float)x, (float)y};
	SDL_Rect location = convertToRect(myPos);
	SDL_BlitSurface(textSurf, NULL, SDL_GetVideoSurface(), &location);

	//clean up
	SDL_FreeSurface(textSurf);
	SDL_FreeSurface(finalSurface);
}

/*
 * Flip the buffer and produce a clean screen for the next surf in memory
 * You can pick the color of the background, defaults to black
 */
void GraphicsEngine::refreshScreen(DefaultColors color){
	SDL_Flip(SDL_GetVideoSurface());
	SDL_FillRect(SDL_GetVideoSurface(),NULL,colors[color].pixelColor);
}

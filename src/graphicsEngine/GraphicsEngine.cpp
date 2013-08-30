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
	vidScreen = SDL_SetVideoMode(WIDTH, HEIGHT, BPP,
			SDL_HWSURFACE || SDL_DOUBLEBUF);
	if (vidScreen == NULL) {
		printf("Error creating SDL window!\n");
	}

	vidInfo = SDL_GetVideoInfo(); 	//pre cache

	printf("Setting up stuff\n");
	setupEndian();
	setupFonts();
	setupColors();
	printf("Finished setup!\n");
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
	fonts.push_back(TTF_OpenFont("res/bluehigh.ttf", 20));
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
	Uint32 pix = SDL_MapRGB(vidInfo->vfmt, r, g, b);
	SDL_Color rgb = { r, g, b };
	Color newColor = { pix, rgb };
	return newColor;
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
 * Quick transform to convert SDL coordinates to
 * Vec2 coordinates (Cartesian coords)
 */
Vec2 GraphicsEngine::convertToVec2(SDL_Rect rect) {
	int oppositeY = rect.y - HEIGHT;
	//now to get the real y
	int realY = oppositeY * -1;

	//possible loss of accuracy - converting from
	//floats to ints
	Vec2 newVec = { (float)rect.x , (float)realY };
	return newVec;
}

/*
 * A Conversion between SDL_Rect and Vec2
 * Uses a simple transform to between Vec2 -> SDL_Rect and SDL_Rect -> Vec2
 * Only does position, doesn't do SDL_Rect's height or width
 * Relies on accurate Window Height
 */
SDL_Rect GraphicsEngine::convertToRect(Vec2 src) {
	//some rounding errors here (src.y and src.x are floats)
	int oppositeY = src.y * -1;
	int maxY = HEIGHT;

	SDL_Rect newRect = { (Sint16) src.x, (Sint16) (maxY + oppositeY), 0, 0 };
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
void GraphicsEngine::blitText(string text, int x, int y, DefaultColors index =
		black) {
	SDL_Surface* textSurf = NULL;
	textSurf = TTF_RenderText_Blended(getDefaultFont(), text.c_str(),
			colors[index].RGBColor);
	if (textSurf == NULL) {
		printf("Error creating text surf: %s! \n", text.c_str());
	}

	//format for display
	SDL_Surface* finalSurface = SDL_DisplayFormatAlpha(textSurf);

	Vec2 myPos = { (float) x, (float) y };
	SDL_Rect location = convertToRect(myPos);
	SDL_BlitSurface(textSurf, NULL, vidScreen, &location);

	//clean up
	SDL_FreeSurface(textSurf);
	SDL_FreeSurface(finalSurface);
}

/*
 * Debugging blit function. reads debug.bmp
 * Blits a image to the screen at vec2 (bitmap)
 * simple transform to convert from Vec2 -> Sdl Coords
 */
void GraphicsEngine::blitImage(int x, int y) {
	Vec2 position = { (float) x, (float) y };
	SDL_Surface* myImage = readImage("res/debug.bmp");
	SDL_Rect sdlCoord = convertToRect(position);
	SDL_BlitSurface(myImage, NULL, vidScreen, &sdlCoord);

	//information pulled from myImage
	printf("Loaded debug image. %d w by %d h\n", myImage->w, myImage->h);

	SDL_FreeSurface(myImage);
}

void GraphicsEngine::blitImage2(int x, int y) {
	Vec2 position = { (float) x, (float) y };
	SDL_Surface* myImage = readImage("res/debug.bmp");
	SDL_Rect sdlCoord = convertToRect(position);
	SDL_FillRect(myImage, NULL, colors[4].pixelColor);

	SDL_BlitSurface(myImage, NULL, vidScreen, &sdlCoord);
	SDL_FreeSurface(myImage);
}

void GraphicsEngine::blitImage3(int x, int y) {
	Vec2 position = { (float) x, (float) y };
	SDL_Surface* myImage = readImage("res/debug.bmp");
	SDL_Rect sdlCoord = convertToRect(position);

	Uint32* pixels = new Uint32[300 * 300];
	for (int x = 0; x < 300; x++) {
		for (int y = 0; y < 300; y++) {
			pixels[x + y * 300] = colors[3].pixelColor;
		}
	}

	SDL_Surface* newSurf = SDL_CreateRGBSurfaceFrom((void*) pixels, 300, 300,
			vidScreen->format->BitsPerPixel, 300 * sizeof(int),
			vidScreen->format->Rmask, vidScreen->format->Gmask,
			vidScreen->format->Bmask, vidScreen->format->Amask);
	SDL_FillRect(newSurf,NULL,colors[3].pixelColor);
	SDL_BlitSurface(newSurf, NULL, vidScreen, NULL);

	SDL_FillRect(myImage, NULL, colors[4].pixelColor);

	SDL_BlitSurface(myImage, NULL, vidScreen, &sdlCoord);
	SDL_FreeSurface(myImage);
	SDL_FreeSurface(newSurf);
}

//Creates a custom rectangle surface
SDL_Surface* GraphicsEngine::readImage(string filename) {
	SDL_Surface* newSurf = NULL;
	SDL_Surface* optimizedSurf = NULL;

	newSurf = SDL_LoadBMP(filename.c_str());
	if (newSurf == NULL) {
		printf("Error reading image! filename : %s \n", filename.c_str());
	}

	optimizedSurf = SDL_DisplayFormat(newSurf);

	SDL_FreeSurface(newSurf);
	return optimizedSurf;
}

/*
 * Creates a surface with the format of another surface.
 * So bliting doesn't require a conversion, and thus doesn't
 * slow down.
 */
SDL_Surface* GraphicsEngine::createSurface(Uint32 flags, int width, int height,
		const SDL_Surface* display) {

	const SDL_PixelFormat& fmt = *(display->format);
	return SDL_CreateRGBSurface(flags, width, height, fmt.BitsPerPixel,
			fmt.Rmask, fmt.Gmask, fmt.Bmask, fmt.Amask);
}

/*
 * Flip the buffer and produce a clean screen for the next surf in memory
 * You can pick the color of the background, defaults to black
 */
void GraphicsEngine::refreshScreen(DefaultColors color) {
	SDL_Flip(vidScreen);
	SDL_FillRect(vidScreen, NULL, colors[color].pixelColor);
}



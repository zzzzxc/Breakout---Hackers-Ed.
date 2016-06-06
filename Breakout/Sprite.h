#ifndef SPRITE_H
#define SPRITE_H

#include"Globals.h"
#include"Sprite.h"

//EVERYTHING IN THE GAME IS A SPRITE. SPRITE IS THE BASE CLASS!

class Sprite{ 
public:
	Sprite();	//SETS STATE OF THE OBJECT TO TRUE
	SDL_Rect getRect();	//GETS THE RECTANGLE BOUNDING THE OBJECT
	void draw(SDL_Surface* dest);	//DRAWS THE OBJECT ON THE 'dest' SURFACE
	void setState(bool state);	//SETS STATE OF THE OBJECT
	bool getState();	//GETS STATE OF THE OBJECT
	void setXPos(float x);	//SET X COORDINATE
	void setYPos(float y);	//SET Y COORDINATE
	float getXPos();	//GET X COORDINATE
	float getYPos();	//GET Y COORDINATE
protected:
	SDL_Surface* mImage;	//SURFACE OF THE OBJECT
	SDL_Rect mRect;		//BOUNDING RECTANGLE OF THE OBJECT
	bool mState;	//STATE OF THE OBJECT
	float x, y;		//X AND Y COORDINATES
};

#endif
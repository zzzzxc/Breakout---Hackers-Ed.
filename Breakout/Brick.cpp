#include<iostream>
#include<SDL.h>
#include"Brick.h"

Brick brick[NUMBER_OF_BRICKS];

	void Brick::setProperties(int color, float x, float y, int w, int h) {
		mColor = color; 
		switch (mColor) {
		case Red:
			mImage = SDL_LoadBMP("Sprites/Bricks/Red.bmp");
			break;
		case DarkRed:
			mImage = SDL_LoadBMP("Sprites/Bricks/DarkRed.bmp");
			break;
		case Maroon:
			mImage = SDL_LoadBMP("Sprites/Bricks/Maroon.bmp");
			break;
		case Yellow:
			mImage = SDL_LoadBMP("Sprites/Bricks/Yellow.bmp");
			break;
		case Green:
			mImage = SDL_LoadBMP("Sprites/Bricks/Green.bmp");
			break;
		case DarkGreen:
			mImage = SDL_LoadBMP("Sprites/Bricks/DarkGreen.bmp");
			break;
		case Blue:
			mImage = SDL_LoadBMP("Sprites/Bricks/Blue.bmp");
			break;
		case DarkBlue:
			mImage = SDL_LoadBMP("Sprites/Bricks/DarkBlue.bmp");
			break;
		case Golden:
			mImage = SDL_LoadBMP("Sprites/Bricks/Golden.bmp");
			break;
		}
		SDL_SetColorKey(mImage, SDL_TRUE, SDL_MapRGB(mImage->format, 0, 0, 0));
		mRect = mImage->clip_rect;

		this->x = x;
		this->y = y;

		mRect.h = h;
		mRect.w = w;
		mRect.x = x - mRect.w/2;
		mRect.y = y - mRect.h/2;	
		
	}
	bool Brick::isLucky() {
		return !(rand()%luckyBrickProbability);
	}
	bool Brick::isGolden() {
		return (mColor == Golden);
	}
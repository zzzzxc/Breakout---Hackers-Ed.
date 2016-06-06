#include"Sprite.h"

	Sprite::Sprite() {
		x = 0.1f;
		y = 0.1f;
		mState = true;
	}
	SDL_Rect Sprite::getRect() {
		return mRect;
	}
	void Sprite::draw(SDL_Surface* dest) {
		if (mState) {
			mRect.x = (int) x;
			mRect.y = (int) y;
			SDL_BlitSurface(mImage, NULL, dest, &mRect); 
		}
	}
	void Sprite::setState(bool state) {
		mState = state;
	}
	bool Sprite::getState() {
		return mState;
	}
	void Sprite::setXPos(float x) {
		this->x = x;
		mRect.x = x;
	}
	void Sprite::setYPos(float y) {
		this->y = y;
		mRect.y = y;
	}
	float Sprite::getXPos() {
		return x;
	}
	float Sprite::getYPos() {
		return y;
	}
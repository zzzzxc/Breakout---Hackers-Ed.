#include<SDL.h>
#include"Ball.h"

Ball b;

	void Ball::setProperties(float x, float y, int w, int h) {
		mImage = SDL_LoadBMP("Sprites/Ball/ball.bmp");
		SDL_SetColorKey(mImage, SDL_TRUE, SDL_MapRGB(mImage->format, 0, 0, 0));;
		mRect = mImage->clip_rect;

		this->x = x;
		this->y = y;

		mRect.h = h;
		mRect.w = w;
		mRect.x = (int) x - mRect.w/2;
		mRect.y = (int) y - mRect.h/2;

		mInitiated = false;
	}
	
	void Ball::setVelocity(float xSpeed, float ySpeed) {
		mXSpeed = xSpeed;
		mYSpeed = ySpeed;
	}
	float Ball::getXSpeed() {
		return mXSpeed;
	}
	float Ball::getYSpeed() {
		return mYSpeed;
	}
	void Ball::setSuperBallState(bool state) {
		if (state) {
			mImage = SDL_LoadBMP("Sprites/Ball/Fireball.bmp");
			SDL_SetColorKey(mImage, SDL_TRUE, SDL_MapRGB(mImage->format, 0, 0, 0));
		}
		else {
			mImage = SDL_LoadBMP("Sprites/Ball/ball.bmp");
			SDL_SetColorKey(mImage, SDL_TRUE, SDL_MapRGB(mImage->format, 0, 0, 0));
		}
		mSuperBall = state;
	}
	void Ball::initiate() {
		mInitiated = true;
	}
	void Ball::halt() {
		mInitiated = false;
	}
	bool Ball::isSuperBall() {
		return mSuperBall;
	}
	bool Ball::isInitiated() {
		return mInitiated;
	}
	void Ball::setSuperBallStartTime(int startTime) {
		mSuperBallStartTime = startTime;
	}
	int Ball::getSuperBallStartTime() {
		return mSuperBallStartTime;
	}
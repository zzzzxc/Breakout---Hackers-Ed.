#include<SDL.h>
#include"Paddle.h"

int paddleWidth = 60;
Paddle p;

	void Paddle::setProperties(float x, float y, int w, int h) {

		mImage = SDL_LoadBMP("Sprites/Paddle/60.bmp");

		SDL_SetColorKey(mImage, SDL_TRUE, SDL_MapRGB(mImage->format, 0, 0, 0));
		mRect = mImage->clip_rect;
		this->x = x;
		this->y = y;
		
		mRect.w = w;
		mRect.h = h;
		mRect.x = (int) x - mRect.w/2;
		mRect.y = (int) y - mRect.h/2;

		mInvertPaddle = false;
		mRocketAmmo = 0;
		mRocketsEquipped = false;

		std::map<SDL_Surface*, SDL_Rect>::iterator it;
		for (it=mRocketImages.begin(); it!=mRocketImages.end();) {
			if (it->second.y - (rocketSpeed * gFTime) <= 0) {
				SDL_FreeSurface(it->first);
				mRocketImages.erase(it++);
			}
		}
	}
	void Paddle::setWidth(int w) {
		SDL_Rect oldRect = mRect;
		switch (w) {
		case 20:
			mImage = SDL_LoadBMP("Sprites/Paddle/20.bmp");
			break;
		case 40:
			mImage = SDL_LoadBMP("Sprites/Paddle/40.bmp");
			break;
		case 60:
			mImage = SDL_LoadBMP("Sprites/Paddle/60.bmp");
			break;
		case 80:
			mImage = SDL_LoadBMP("Sprites/Paddle/80.bmp");
			break;
		case 100:
			mImage = SDL_LoadBMP("Sprites/Paddle/100.bmp");
			break;
		case 120:
			mImage = SDL_LoadBMP("Sprites/Paddle/120.bmp");
			break;
		}
		SDL_SetColorKey(mImage, SDL_TRUE, SDL_MapRGB(mImage->format, 0, 0, 0));
		mRect = mImage->clip_rect;

		mRect.h = oldRect.h;
		mRect.w = w;
		mRect.x = oldRect.x - mRect.w/2;
		mRect.y = oldRect.y - oldRect.h/2;

		paddleWidth = w;
	}
	void Paddle::drawRockets(SDL_Surface* dest) {
		std::map<SDL_Surface*, SDL_Rect>::iterator it;
		for (it=mRocketImages.begin(); it!=mRocketImages.end();) {
			if (it->second.y - (rocketSpeed * gFTime) <= 0) {
				mRocketImages.erase(it++);
			}
			else {
				it->second.y -= (rocketSpeed * gFTime);
				SDL_BlitSurface(it->first, NULL, dest, &it->second);	
				++it;
			}
		}
	}
	void Paddle::equipRockets() {
		mRocketsEquipped = true;
		mRocketAmmo = 8;		
	}
	void Paddle::fireRockets() {
		mRocketAmmo--;
		bool rocketState = true;
		SDL_Surface* leftRocketImage = SDL_CreateRGBSurface(0, rocketWidth, rocketHeight, 32, 0, 0, 0, 0);
		SDL_Surface* rightRocketImage = SDL_CreateRGBSurface(0, rocketWidth, rocketHeight, 32, 0, 0, 0, 0);

		SDL_FillRect(leftRocketImage, NULL, SDL_MapRGB(leftRocketImage->format, 255, 0, 0));
		SDL_FillRect(rightRocketImage, NULL, SDL_MapRGB(rightRocketImage->format, 255, 0, 0));
		
		SDL_Rect leftRocketRect = leftRocketImage->clip_rect;
		SDL_Rect rightRocketRect = rightRocketImage->clip_rect;

		leftRocketRect.w = rocketWidth;
		leftRocketRect.h = rocketHeight;
		leftRocketRect.x = x;
		leftRocketRect.y = y - 20;

		rightRocketRect.w = rocketWidth;
		rightRocketRect.h = rocketHeight;
		rightRocketRect.x = x + paddleWidth - rocketWidth;
		rightRocketRect.y = y - 20;

		SDL_BlitSurface(leftRocketImage, NULL, gScreen, &leftRocketRect);
		SDL_BlitSurface(rightRocketImage, NULL, gScreen, &rightRocketRect);

		SDL_UpdateWindowSurface(gWindow);

		mRocketImages[leftRocketImage] = leftRocketRect;
		mRocketImages[rightRocketImage] = rightRocketRect;
	}
	void Paddle::setRocketAmmo(int ammo) {
		mRocketAmmo = ammo;
	}
	int Paddle::getRocketAmmo() {
		return mRocketAmmo;
	}
	void Paddle::updateRocketImages(std::map<SDL_Surface*, SDL_Rect> rocketImages) {
		mRocketImages = rocketImages;
	}
	std::map<SDL_Surface*, SDL_Rect>& Paddle::getRocketImages() {
		return mRocketImages;
	}
	void Paddle::setInvertState(bool state) {
		mInvertPaddle = state;
	}
	bool Paddle::getInvertState() {
		return mInvertPaddle;
	}
	void Paddle::setInvertStartTime(int startTime) {
		mInvertStartTime = startTime;
	}
	int Paddle::getInvertStartTime() {
		return mInvertStartTime;
	}
	void Paddle::setStickyPaddleState(bool state) {
		mStickyPaddle = state;
	}
	bool Paddle::getStickyPaddleState() {
		return mStickyPaddle;
	}
#include<iostream>
#include<SDL.h>
#include"Nerf.h"
#include"Brick.h"
#include"Ball.h"
#include"Paddle.h"

std::vector<Nerf> nerf;

	void Nerf::setProperties(float x, float y, int w, int h) {
		mNerfType = Gravity;
		switch (mNerfType) {
		case SmallerPaddle:
			mImage = SDL_LoadBMP("Sprites/Powers/Decrease_Paddle.bmp");
			break;
		case Gravity:
			mImage = SDL_LoadBMP("Sprites/Powers/Gravity.bmp");
			break;
		case InvertPaddle:
			mImage = SDL_LoadBMP("Sprites/Powers/InvertPaddle.bmp");
			break;
		case MinusFifty:
			mImage = SDL_LoadBMP("Sprites/Powers/MinusFifty.bmp");
			break;
		case InstantDeath:
			mImage = SDL_LoadBMP("Sprites/Powers/Death.bmp");
			break; 
		}
		mRect = mImage->clip_rect;

		this->x = x;
		this->y = y;

		mRect.h = h;
		mRect.w = w;
		mRect.x = x;
		mRect.y = y;

	}

	void Nerf::activateNerf() {
		switch (mNerfType) {
		case SmallerPaddle:
			Mix_PlayChannel(7, gShrinkPaddle, 0);
			smallerPaddle();
			break;
		case Gravity:
			Mix_PlayChannel(-1, gGravity, 0);
			gravity();
			break;
		case InvertPaddle:
			Mix_PlayChannel(-1, gInvertPaddle, 0);
			invertPaddle();
			break;
		case MinusFifty:
			Mix_PlayChannel(-1, gMinusFifty, 0);
			minusFifty();
			break;
		case InstantDeath:
			Mix_PlayChannel(-1, gDeath, 0);
			instantDeath();
			break;
		}
	}
	void Nerf::smallerPaddle() {
		if (p.getRect().w - 20 >= minPaddleWidth) {
			p.setWidth(p.getRect().w - 20);
			p.setXPos(p.getRect().x + p.getRect().w/2 + p.getRect().w/4);	
		}
	}
	void Nerf::gravity() {
		if (brick[NUMBER_OF_BRICKS-1].getYPos() <= maxLevelForGravity - gravityPullDown) {
			for (int i=0; i<NUMBER_OF_BRICKS; i++) {
				brick[i].setYPos(brick[i].getYPos() + gravityPullDown);
			}
		}
	}
	void Nerf::invertPaddle() {
		p.setInvertState(true);
		p.setInvertStartTime(gElapsedTime);
	}
	void Nerf::minusFifty() {
		gScore -= 50;
	}
	void Nerf::instantDeath() {
		b.setProperties(p.getXPos()+paddleWidth/2-ballWidth/2, p.getYPos()-paddleHeight-5);
		float randomXSpeed = 150 - rand()%301;
		b.setVelocity(randomXSpeed, 150.0f);
		p.setWidth(60);
		p.setInvertState(false);
		p.setRocketAmmo(0);
		b.setSuperBallState(false);
		gLives--;
		gBallHits = 0;
	
	}
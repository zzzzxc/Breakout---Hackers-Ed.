#include<iostream>
#include<SDL.h>
#include"Buff.h"
#include"Paddle.h"
#include"Ball.h"

std::vector<Buff> buff;

	void Buff::setProperties(float x, float y, int w, int h) {
		mBuffType = rand()%NUMBER_OF_BUFFS;
		switch (mBuffType) {
		case LargerPaddle:
			mImage = SDL_LoadBMP("Sprites/Powers/Increase_Paddle.bmp");
			break;
		case ExtraLife:
			mImage = SDL_LoadBMP("Sprites/Powers/heart.bmp");
			break;
		case SuperBall:
			mImage = SDL_LoadBMP("Sprites/Powers/Superball.bmp");
			break;
		case Rockets:
			mImage = SDL_LoadBMP("Sprites/Powers/Rockets.bmp");
			break;
		case PlusFifty:
			mImage = SDL_LoadBMP("Sprites/Powers/PlusFifty.bmp");
			break;
		case StickyPaddle:
			mImage = SDL_LoadBMP("Sprites/Powers/StickyPaddle.bmp");
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

	void Buff::activateBuff() {
		switch (mBuffType) {
		case LargerPaddle:
			Mix_PlayChannel(1, gIncreasePaddle, 0);
			largerPaddle();
			break;
		case ExtraLife:
			Mix_PlayChannel(2, gExtraLife, 0);
			extraLife();
			break;
		case SuperBall:
			Mix_PlayChannel(3, gSuperBall, 0);
			superBall();
			break;
		case Rockets:
			Mix_PlayChannel(4, gEquipRockets, 0);
			rockets();
			break;
		case PlusFifty:
			Mix_PlayChannel(5, gExtraLife, 0);
			plusFifty();
			break;
		case StickyPaddle:
			Mix_PlayChannel(6, gStickyPaddle, 0);
			stickyPaddle();
			break;
		}
	}

	void Buff::largerPaddle() {
		if (p.getRect().w + 20 <= maxPaddleWidth) {
			p.setWidth(p.getRect().w + 20);
			p.setXPos(p.getRect().x + p.getRect().w/2 - p.getRect().w/4);
		}
	}
	void Buff::superBall() {
		b.setSuperBallState(true);
		b.setSuperBallStartTime(gElapsedTime);
	}
	void Buff::extraLife() {
		gLives++;
	}
	void Buff::rockets() {
		p.equipRockets();
	}
	void Buff::stickyPaddle() {
		p.setStickyPaddleState(true);
	}
	void Buff::plusFifty() {
		gScore += 50;
	}
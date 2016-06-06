////////////////////////////////////////////////
//PROJECT TITLE: BREAKOUT HACKERS ED.///////////
//GROUP PARTNER: KHUBAIB ALI PIRZADA (BSCS-3A)//
////////////////////////////////////////////////

#include<SDL.h>
#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<ctime>
#include<SDL_ttf.h>
#include<SDL_mixer.h>
#include<math.h>
#include"Globals.h"
#include"Sprite.h"
#include"Paddle.h"
#include"Ball.h"
#include"Brick.h"
#include"Buff.h"
#include"Nerf.h"
#include"Breakout.h"

int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_EVERYTHING);
	loadEverything();
	bool running = true;
	bool paused = false;
	int framesCount = 0;
	Uint32 currentTick = SDL_GetTicks();
	Uint32 oldTick;
	//GAME LOOP
	while (running) {
		oldTick = currentTick;
		currentTick = SDL_GetTicks();
		framesCount++;
		if (framesCount%fps==0 && !paused && gBricksRemaining>0) {
			gElapsedTime++;
			gRemainingTime--;
		}
		gFTime = (currentTick - oldTick)/1000.0f; 
		if (!gVictory && !gDefeat) {
			SDL_BlitSurface(gBackground, NULL, gScreen, NULL);
			drawBricks();
			p.draw(gScreen);
			p.drawRockets(gScreen);
			b.draw(gScreen);
		}
		else if (gVictory) {
			gBackground = SDL_LoadBMP("Screens/victory (1000x600).bmp");
			SDL_BlitSurface(gBackground, NULL, gScreen, NULL);
		} 
		else {
			gBackground = SDL_LoadBMP("Screens/defeat (1000x600).bmp");
			SDL_BlitSurface(gBackground, NULL, gScreen, NULL);
		}
		drawText();
		SDL_PollEvent(&gEvent);
		if (gEvent.type == SDL_QUIT) {
			running = false;
		}
		else if (gEvent.type == SDL_KEYDOWN) {
			if (gEvent.key.keysym.sym == SDLK_g) {
					gGodMode = (gGodMode)?false:true;
			}
			else if (gEvent.key.keysym.sym == SDLK_x) {
				running = false;
			}
			else if (gEvent.key.keysym.sym == SDLK_SPACE) {
				if (b.isInitiated()) {
					if (p.getRocketAmmo()!=0) {
						p.fireRockets();
						Mix_PlayChannel(-1, gFireRockets, 0);
					}
				}
				else {
					b.initiate();
				}
			}
			else if (gEvent.key.keysym.sym == SDLK_p) {
				paused = (paused==0)? true: false;
			}
			else if (gEvent.key.keysym.sym == SDLK_r) {
				resetEverything();
				paused = false;
			}
		}
		else if (gEvent.type == SDL_MOUSEMOTION && !paused) {
			if (!p.getInvertState()) {
				if (gEvent.motion.x < p.getXPos() + paddleWidth/2) {
						if (p.getXPos() - (paddleSpeed*gFTime) >= arenaLeft) {
							p.setXPos(p.getXPos() - (paddleSpeed*gFTime));	
						}
				}
				else if (gEvent.motion.x > p.getXPos() + paddleWidth/2) {
					if (p.getXPos() + p.getRect().w + (paddleSpeed*gFTime) <= arenaRight) {
						p.setXPos(p.getXPos() + (paddleSpeed*gFTime)); 
					}
				}
			}
			else {
				if (gElapsedTime - p.getInvertStartTime() >= invertPaddleDuration) {
					p.setInvertState(false);
				}
				if (gEvent.motion.x > p.getXPos() + paddleWidth/2) {
						if (p.getXPos() - (paddleSpeed*gFTime) >= arenaLeft) {
							p.setXPos(p.getXPos() - (paddleSpeed*gFTime));	
						}
				}
				else if (gEvent.motion.x < p.getXPos() + paddleWidth/2) {
					if (p.getXPos() + p.getRect().w + (paddleSpeed*gFTime) < arenaRight) {
							p.setXPos(p.getXPos() + (paddleSpeed*gFTime)); 
						}
				}
			}
		}
		else if (gEvent.type == SDL_MOUSEBUTTONDOWN && !paused) {
			if (gEvent.button.button == SDL_BUTTON_LEFT) {
				if (b.isInitiated()) {
					if (p.getRocketAmmo()!=0) {
						p.fireRockets();
						Mix_PlayChannel(-1, gFireRockets, 0);
					}
				}
				else {
					b.initiate();
				}
			}
		}
		p.setRocketAmmo(10);
		if (!paused) {
			action();
		}
		gBallPPx = b.getXPos();
		gBallPPy = b.getYPos();
			
		if (!paused) {
			if (gBricksRemaining == 0) {
				gVictory = true;
				paused = true;
			}
			else if (gRemainingTime == 0 || gLives == 0) {
				gDefeat = true;
				paused = true;
			}
		}
		SDL_UpdateWindowSurface(gWindow);
		if (1000/fps > SDL_GetTicks() - currentTick) {
			SDL_Delay(1000/fps - (SDL_GetTicks() - currentTick));
		}
		gPrevFTime = gFTime;
	}

	quit();
	return 0;
}
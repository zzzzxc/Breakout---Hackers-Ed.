#include"Globals.h"
#include"Paddle.h"
#include"Ball.h"
#include"Brick.h"
#include"Buff.h"
#include"Nerf.h"

const Uint8 *gKeyStates;
SDL_Event gEvent;
SDL_Window* gWindow = NULL;
SDL_Surface* gScreen = NULL;
SDL_Surface* gText = NULL;
SDL_Surface* gBackground = NULL;
TTF_Font* gFont = NULL;

Mix_Chunk* gCollision = NULL;
Mix_Chunk* gDeath = NULL;
Mix_Chunk* gFireRockets = NULL;
Mix_Chunk* gShrinkPaddle = NULL;
Mix_Chunk* gIncreasePaddle = NULL;
Mix_Chunk* gExtraLife = NULL;
Mix_Chunk* gGravity = NULL; 
Mix_Chunk* gEquipRockets = NULL;
Mix_Chunk* gSuperBall = NULL;
Mix_Chunk* gStickyPaddle = NULL;
Mix_Chunk* gMinusFifty = NULL;
Mix_Chunk* gInvertPaddle = NULL;

int gElapsedTime;
int gRemainingTime;
int gScore;
int gLives;
int gBallHits;
int gBricksRemaining;
bool gVictory, gDefeat;
bool gGodMode;
float gBallPPx, gBallPPy;
float gPrevFTime;
float gFTime;


bool collision(SDL_Rect rect1, SDL_Rect rect2) {
	if (rect1.x > rect2.x + rect2.w) return false;
	if (rect1.x + rect1.w < rect2.x) return false;
	if (rect1.y > rect2.y + rect2.h) return false;
	if (rect1.y + rect1.h < rect2.y) return false;
	return true;
}

void loadEverything() {
	gBackground = SDL_LoadBMP("Screens/space (1000x600).bmp");
	gWindow = SDL_CreateWindow("Breakout", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

	gScreen = SDL_GetWindowSurface(gWindow);
	SDL_ShowCursor(0);
	srand(time(NULL));

	gKeyStates = SDL_GetKeyboardState(NULL);

	gElapsedTime = 0;
	gRemainingTime = 100;
	gLives = 3;
	gBricksRemaining = NUMBER_OF_BRICKS;
	gScore = 0;
	gBallHits = 0;
	gGodMode = false;

	p.setProperties(arenaLeft + (arenaWidth/2) - paddleWidth/2, arenaDown-15);
	b.setProperties(p.getXPos()+paddleWidth/2-ballWidth/2, p.getYPos()-paddleHeight-5);

	float randomXSpeed = 150 - rand()%301;
	b.setVelocity(randomXSpeed, 150.0f);

	int widthSpacing = arenaLeft + 70;
	int heightSpacing = arenaUp + 30;
	int brickColor = Red;
	for (int i=0; i<NUMBER_OF_BRICKS; i++) {
		brick[i].setProperties(brickColor%NUMBER_OF_COLORS, widthSpacing, heightSpacing);
		if (widthSpacing + 70 < arenaRight - 70)
			widthSpacing += 70;
		else {
			brickColor++;
			widthSpacing = arenaLeft + 70;
			heightSpacing += 30;
		}
		brick[i].draw(gScreen);
		brick[i].setState(true);
	}
	TTF_Init();
	gFont = TTF_OpenFont("Fonts/agencyfb-bold_0.ttf", 22);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	gCollision = Mix_LoadWAV("Sound/collision.wav");
	gFireRockets = Mix_LoadWAV("Sound/laser.wav");
	gShrinkPaddle = Mix_LoadWAV("Sound/chomp.wav");
	gExtraLife = Mix_LoadWAV("Sound/extralife.wav");
	gDeath = Mix_LoadWAV("Sound/death.wav");
	gIncreasePaddle = Mix_LoadWAV("Sound/IncreasePaddle.wav");
	gGravity = Mix_LoadWAV("Sound/gravity.wav");
	gEquipRockets = Mix_LoadWAV("Sound/EquipRockets.wav");
	gSuperBall = Mix_LoadWAV("Sound/SuperBall.wav");
	gStickyPaddle = Mix_LoadWAV("Sound/StickyPaddle.wav");
	gMinusFifty = Mix_LoadWAV("Sound/powerdown.wav");
	gInvertPaddle = Mix_LoadWAV("Sound/invertpaddle.wav");
}


void drawBricks() {
	for (int i=0; i<NUMBER_OF_BRICKS; i++) {
		brick[i].draw(gScreen);
	}
}	


void checkRocketCollisions() {
	std::map<SDL_Surface*, SDL_Rect> tempImages = p.getRocketImages();
	std::map<SDL_Surface*, SDL_Rect>::iterator it;
	for (it=tempImages.begin(); it!=tempImages.end();) {
		bool rocketCollided = false;
		if (collision(it->second, b.getRect())) {
			tempImages.erase(it++);
			float randomXSpeed = 150 - rand()%301;
			b.setVelocity(randomXSpeed, 150.0f);
			b.setProperties(p.getXPos()+paddleWidth/2-ballWidth/2, p.getYPos()+paddleHeight);
			gLives--;
			b.setSuperBallState(false);
			gBallHits = 0;
			p.setWidth(60);
			p.setInvertState(false);
			p.setRocketAmmo(0);
			Mix_PlayChannel(-1, gDeath, 0);
			rocketCollided = true;
		}
		else {
			for (int i=0; i<NUMBER_OF_BRICKS; i++) {
				if (brick[i].getState()) {
					if (collision(it->second, brick[i].getRect())) {
						tempImages.erase(it++);
						brick[i].setState(false);
						gBricksRemaining--;
						rocketCollided = true;
						if (brick[i].isGolden()) {
							gScore += 30;
						}
						else {
							gScore += 5;
						}
						if (brick[i].isLucky()) {
							Buff randomBuff;	
							Nerf randomNerf;
							if (rand()%2) {
								randomBuff.setProperties(brick[i].getXPos()+brickWidth/4, brick[i].getYPos()-brickHeight/4);
								buff.push_back(randomBuff);			
							}
							else {
								randomNerf.setProperties(brick[i].getXPos()+brickWidth/4, brick[i].getYPos()-brickHeight/4);
								nerf.push_back(randomNerf);
							}
						}
						break;
					}
				}
			}
		}
		if (!rocketCollided) {
			++it;
		}
	}
	p.updateRocketImages(tempImages);
}

void checkCollisionWithBricks() {
	for (int i=0; i<NUMBER_OF_BRICKS; i++) {
		if (gElapsedTime >= 30) {
			if (brick[i].isGolden() && brick[i].getState()) {
				brick[i].setState(false);
				gBricksRemaining--;
			}
		}
		if (brick[i].getState()) {
			if (collision(brick[i].getRect(), b.getRect())) {
				bool hitTheCorner = false;
					
				if (!b.isSuperBall()) {
					if (gBallPPx > brick[i].getXPos() && gBallPPx < brick[i].getXPos() + brickWidth && gBallPPy < brick[i].getYPos()) {
						if (b.getXPos() > brick[i].getXPos() && b.getXPos() < brick[i].getXPos() + brickWidth && b.getYPos() < brick[i].getYPos() + brickHeight) {
						//top
							b.setVelocity(b.getXSpeed(), -b.getYSpeed());
						}
					}
					else if (gBallPPx > brick[i].getXPos() && gBallPPx < brick[i].getXPos() + brickWidth && gBallPPy > brick[i].getYPos() + brickHeight) {
						if (b.getXPos() > brick[i].getXPos() && b.getXPos() < brick[i].getXPos() + brickWidth && b.getYPos() > brick[i].getYPos()) {
						//bot
							b.setVelocity(b.getXSpeed(), -b.getYSpeed());
						}
					}
					else if (gBallPPx < brick[i].getXPos() && gBallPPy > brick[i].getYPos() && gBallPPy < brick[i].getYPos() + brickHeight) {
						if (b.getRect().x < brick[i].getXPos() + brickWidth && b.getYPos() > brick[i].getYPos() && b.getYPos() < brick[i].getYPos() + brickHeight) {
							//left
							b.setVelocity(-b.getXSpeed(), b.getYSpeed());
						}
					}
					else if (gBallPPx > brick[i].getXPos() + brickWidth && gBallPPy > brick[i].getYPos() && gBallPPy < brick[i].getYPos() + brickHeight) {
						if (b.getRect().x > brick[i].getXPos() && b.getYPos() > brick[i].getYPos() && b.getYPos() < brick[i].getYPos() + brickHeight) {
							//right
							b.setVelocity(-b.getXSpeed(), b.getYSpeed());
						}
					}
					else {
						//reference: http://gamedev.stackexchange.com/questions/17502/how-to-deal-with-corner-collisions-in-2d/18589#18589
						float timeXCollision, timeYCollision;
						SDL_Rect intersectRect;
						SDL_IntersectRect(&b.getRect(), &brick[i].getRect(), &intersectRect);
						timeXCollision =  abs((intersectRect.w)/(b.getXSpeed()*gFTime));
						timeYCollision = abs((intersectRect.h)/(b.getYSpeed()*gFTime));

						if (timeXCollision < timeYCollision) {
							b.setVelocity(-b.getXSpeed(), b.getYSpeed());
						}
						else if (timeXCollision > timeYCollision) {
							b.setVelocity(b.getXSpeed(), -b.getYSpeed());
						}
						else {
							hitTheCorner = true;
						}
					}
					
				}
				if (!hitTheCorner) {
					Mix_PlayChannel(-1, gCollision, 0);
					brick[i].setState(false);
					gBricksRemaining--;
					if (brick[i].isGolden()) {
						gScore += 30;
					}
					else {
						gScore += 5;
					}
					if (brick[i].isLucky()) {
						Buff randomBuff;	
						Nerf randomNerf;
						if (rand()%2) {
							randomBuff.setProperties(brick[i].getXPos()+brickWidth/4, brick[i].getYPos()-brickHeight/4);
							buff.push_back(randomBuff);			
						}
						else {
							randomNerf.setProperties(brick[i].getXPos()+brickWidth/4, brick[i].getYPos()-brickHeight/4);
							nerf.push_back(randomNerf);
						}
					}
				}
				break;
			}
		}
	}
}


void checkCollisionWithBuffs() {
	std::vector<Buff>::iterator it;
	for (it=buff.begin(); it!=buff.end(); it++) {
		if ((*it).getState()) {
			if (collision((*it).getRect(), p.getRect())) {
				(*it).activateBuff();
				(*it).setState(false);
			}
		}
	}
}

void checkCollisionWithNerfs() {
	std::vector<Nerf>::iterator it;
	for (it=nerf.begin(); it!=nerf.end(); it++) {
		if ((*it).getState()) {
			if (collision((*it).getRect(), p.getRect())) {
				(*it).activateNerf();
				(*it).setState(false);
			}
		}
	}
}

void activateGodMode() {
	float ballSpeed = sqrtf(b.getXSpeed()*b.getXSpeed() + b.getYSpeed()*b.getYSpeed());
	if (p.getXPos() + paddleWidth/2 > b.getXPos() + ballWidth/2) {
		if (p.getXPos() - (ballSpeed*gFTime) >= arenaLeft) {	
			p.setXPos(p.getXPos() - (ballSpeed*gFTime));	
		}
	}
	else if (p.getXPos() + paddleWidth/2 < b.getXPos() + ballWidth/2) {
		if (p.getXPos() + paddleWidth + (ballSpeed*gFTime) <= arenaRight) {	
			p.setXPos(p.getXPos() + (ballSpeed*gFTime));	
		}
	}
}

void action() {
	SDL_PumpEvents();
	if (gGodMode) {
		activateGodMode();
	}
	else {
		if (!p.getInvertState()) {
			if (gKeyStates[SDL_SCANCODE_LEFT]) {
				if (p.getXPos() - (paddleSpeed*gFTime) >= arenaLeft) {
					p.setXPos(p.getXPos() - (paddleSpeed*gFTime));	
				}
			}
			if (gKeyStates[SDL_SCANCODE_RIGHT]) {
				if (p.getXPos() + p.getRect().w + (paddleSpeed*gFTime) <= arenaRight) {
					p.setXPos(p.getXPos() + (paddleSpeed*gFTime)); 
				}
			}
		}
		else {
			if (gElapsedTime - p.getInvertStartTime() >= invertPaddleDuration) {
				p.setInvertState(false);
			}
			if (gKeyStates[SDL_SCANCODE_RIGHT]) {
				if (p.getXPos() - (paddleSpeed*gFTime) >= arenaLeft) {
					p.setXPos(p.getXPos() - (paddleSpeed*gFTime));	
				}
			}
			if (gKeyStates[SDL_SCANCODE_LEFT]) {
				if (p.getXPos() + p.getRect().w + (paddleSpeed*gFTime) <= arenaRight) {
					p.setXPos(p.getXPos() + (paddleSpeed*gFTime)); 
				}
			}
		}
		if (!b.isInitiated()) {
			if (gKeyStates[SDL_SCANCODE_SPACE]) {
				b.initiate();
			}
			else {
				bool superBall = false;
				if (b.isSuperBall()) {
					superBall = true;
				}
				b.setProperties(p.getXPos()+paddleWidth/2-ballWidth/2, p.getYPos()-paddleHeight-5);
				b.setXPos(p.getXPos()+paddleWidth/2-ballWidth/2);
				b.setYPos(p.getYPos()-paddleHeight-5);
				b.setSuperBallState(superBall);
			}
		}
	}

	if (b.isSuperBall()) {
		if (gElapsedTime - b.getSuperBallStartTime() >= 6) {
			b.setSuperBallState(false);
		}
	}

	if (b.isInitiated()) {
		b.setXPos(b.getXPos() + (b.getXSpeed()*gFTime));
		checkCollisionWithBricks();
		b.setYPos(b.getYPos() + (b.getYSpeed()*gFTime));
		checkCollisionWithBricks();
	}

	if (b.getXPos()+ballWidth+(b.getXSpeed()*gFTime) > arenaRight || b.getXPos()+(b.getXSpeed()*gFTime) <= arenaLeft) {
		b.setVelocity(-b.getXSpeed(), b.getYSpeed());
		Mix_PlayChannel(-1, gCollision, 0);
	}
	if (b.getYPos()+(b.getYSpeed()*gFTime) <= arenaUp) {
		b.setVelocity(b.getXSpeed(), -b.getYSpeed());
		Mix_PlayChannel(-1, gCollision, 0);
	}
	if (b.getYPos() >= arenaDown) {		
		b.setProperties(p.getXPos()+paddleWidth/2-ballWidth/2, p.getYPos()-paddleHeight-5);
		float randomXSpeed = 150 - rand()%301;
		b.setVelocity(randomXSpeed, 150.0f);
		p.setWidth(60);
		p.setInvertState(false);
		p.setRocketAmmo(0);
		gLives--;
		b.setSuperBallState(false);
		gBallHits = 0;
		Mix_PlayChannel(-1, gDeath, 0);
		p.setStickyPaddleState(false);
	}

	if (collision(p.getRect(), b.getRect())) {
		gBallPPx = b.getXPos();
		gBallPPy = b.getYPos();
		Mix_PlayChannel(-1, gCollision, 0);
			//Reference: http://www.scriptedfun.com/arinoid-an-arkanoid-clone/
			float ballpos = ballWidth + b.getXPos() - p.getXPos() - 1;
			float ballmax = ballWidth + paddleWidth - 2;
			float factor = float (ballpos)/ballmax;
			float angle = maxAngle - factor*(maxAngle - minAngle);
			float speed = sqrt(b.getXSpeed()*b.getXSpeed() + b.getYSpeed()*b.getYSpeed());
			b.setVelocity((speed*cos(angle)), -speed*sin(angle));
			b.setYPos(b.getYPos()-5);
			gBallHits++;
			if (p.getStickyPaddleState() && !gGodMode) {
				b.halt();
			}
		
		if (gBallHits<=10) {
			float newXSpeed, newYSpeed;
			if (b.getXSpeed() < 0) {
				newXSpeed = b.getXSpeed() - hitSpeedChangeOffset;
			}
			else {
				newXSpeed = b.getXSpeed() + hitSpeedChangeOffset;
			}
			if (b.getYSpeed() < 0) {
				newYSpeed = b.getYSpeed() - hitSpeedChangeOffset;
			}
			else {
				newYSpeed = b.getYSpeed() + hitSpeedChangeOffset;
			}
			b.setVelocity(newXSpeed, newYSpeed);
		}
	}
	std::vector<Buff>::iterator b_it;
	std::vector<Nerf>::iterator n_it;
	for (b_it=buff.begin(); b_it!=buff.end(); b_it++) {
		(*b_it).draw(gScreen);
		(*b_it).setYPos((*b_it).getYPos()+2);
		if ((*b_it).getYPos() + buffHeight >= arenaDown-2) {
			(*b_it).setState(false);
		}
	}
	for (n_it=nerf.begin(); n_it!=nerf.end(); n_it++) {
		(*n_it).draw(gScreen);
		(*n_it).setYPos((*n_it).getYPos()+2);
		if ((*n_it).getYPos() + nerfHeight >= arenaDown-2) {
			(*n_it).setState(false);
		}
	}
	checkCollisionWithBuffs();
	checkCollisionWithNerfs();
	checkRocketCollisions();
}

void quit() {
	SDL_FreeSurface(gBackground);
	SDL_FreeSurface(gText);
	SDL_DestroyWindow(gWindow);
	TTF_CloseFont(gFont);
	TTF_Quit();
	Mix_FreeChunk(gCollision);
	Mix_FreeChunk(gDeath);
	Mix_FreeChunk(gExtraLife);
	Mix_FreeChunk(gFireRockets);
	Mix_FreeChunk(gShrinkPaddle);
	Mix_FreeChunk(gIncreasePaddle);
	Mix_FreeChunk(gGravity);
	Mix_FreeChunk(gEquipRockets);
	Mix_FreeChunk(gSuperBall);
	Mix_FreeChunk(gMinusFifty);
	Mix_FreeChunk(gInvertPaddle);
	Mix_FreeChunk(gStickyPaddle);
	SDL_Quit();
}

void drawText() {
	SDL_Rect livesRect = {20, 200, 50, 25};
	SDL_Rect timeRect = {20, 225, 50, 25};
	SDL_Rect scoreRect = {20, 250, 50, 25};
	SDL_Rect bricksRect = {20, 275, 50, 25};
	SDL_Rect textRect = {20, 350, 50, 50};
	SDL_Color livesColor = {0, 0, 255};
	SDL_Color scoreColor = {0, 255, 0};
	SDL_Color timeColor = {255, 0, 0};
	SDL_Color bricksColor = {0, 255, 255};
	SDL_Color textColor = {255, 255, 255};
	std::string str_text;
	str_text = "Lives: ";
	str_text += std::to_string(gLives);
	gText = TTF_RenderText_Solid(gFont, str_text.c_str(), livesColor);
	SDL_BlitSurface(gText, NULL, gScreen, &livesRect);
	str_text = "Timer: ";
	str_text += std::to_string(gRemainingTime);
	gText = TTF_RenderText_Solid(gFont, str_text.c_str(), timeColor);
	SDL_BlitSurface(gText, NULL, gScreen, &timeRect);
	str_text = "Score: ";
	str_text += std::to_string(gScore);
	gText = TTF_RenderText_Solid(gFont, str_text.c_str(), scoreColor);
	SDL_BlitSurface(gText, NULL, gScreen, &scoreRect);
	str_text = "Bricks Remaining: ";
	str_text += std::to_string(gBricksRemaining);
	gText = TTF_RenderText_Solid(gFont, str_text.c_str(), bricksColor);
	SDL_BlitSurface(gText, NULL, gScreen, &bricksRect);
	
	
	str_text = "P: Pause";
	gText = TTF_RenderText_Solid(gFont, str_text.c_str(), textColor);
	SDL_BlitSurface(gText, NULL, gScreen, &textRect);
	textRect.y += 20;
	str_text = "R: Restart";
	gText = TTF_RenderText_Solid(gFont, str_text.c_str(), textColor);
	SDL_BlitSurface(gText, NULL, gScreen, &textRect);
	textRect.y += 20;
	str_text = "G: Toggle God Mode";
	gText = TTF_RenderText_Solid(gFont, str_text.c_str(), textColor);
	SDL_BlitSurface(gText, NULL, gScreen, &textRect);
	textRect.y += 20;
	str_text = "X: Exit";
	gText = TTF_RenderText_Solid(gFont, str_text.c_str(), textColor);
	SDL_BlitSurface(gText, NULL, gScreen, &textRect);
	textRect.y += 30;
	str_text = "Credits:";
	gText = TTF_RenderText_Solid(gFont, str_text.c_str(), textColor);
	SDL_BlitSurface(gText, NULL, gScreen, &textRect);
	textRect.y += 20;
	str_text = "Bricks by Gatlin1";
	gText = TTF_RenderText_Solid(gFont, str_text.c_str(), textColor);
	SDL_BlitSurface(gText, NULL, gScreen, &textRect);

}

void resetEverything() {
	gBackground = SDL_LoadBMP("Screens/space (1000x600).bmp");
	gElapsedTime = 0;
	gRemainingTime = 100;
	gLives = 3;
	gVictory = false;
	gDefeat = false;
	gBricksRemaining = NUMBER_OF_BRICKS;
	gScore = 0;
	gBallHits = 0;
	gGodMode = false;

	p.setProperties(arenaLeft + (arenaWidth/2) - paddleWidth/2, arenaDown-15);
	b.setProperties(p.getXPos()+paddleWidth/2-ballWidth/2, p.getYPos()-paddleHeight-5);

	float randomXSpeed = 150 - rand()%301;
	b.setVelocity(randomXSpeed, 150.0f);
		
	int widthSpacing = arenaLeft + 70;
	int heightSpacing = arenaUp + 30;
	int brickColor = Red;
	for (int i=0; i<NUMBER_OF_BRICKS; i++) {
		brick[i].setProperties(brickColor%NUMBER_OF_COLORS, widthSpacing, heightSpacing);
		if (widthSpacing + 70 < arenaRight - 70)
			widthSpacing += 70;
		else {
			brickColor++;
			widthSpacing = arenaLeft + 70;
			heightSpacing += 30;
		}
		brick[i].draw(gScreen);
		brick[i].setState(true);
	}
	buff.clear();
	nerf.clear();
}

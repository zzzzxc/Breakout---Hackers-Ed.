#ifndef GLOBALS_H
#define GLOBALS_H

#include<iostream>
#include<vector>
#include<map>
#include<ctime>
#include<string>
#include<SDL.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>


const int NUMBER_OF_BRICKS = 108;
const int ballWidth = 10;
const int ballHeight = 10;
const int WIDTH = 1000;
const int HEIGHT = 600;
const int arenaWidth = 765;
const int arenaHeight = 565;
const int arenaLeft = 220;
const int arenaUp = 15;
const int arenaRight = arenaLeft + arenaWidth;
const int arenaDown = arenaUp + arenaHeight;
extern int paddleWidth;
const int maxPaddleWidth = 120;
const int minPaddleWidth = 20;
const int paddleHeight = 10;
const float paddleSpeed = 500.0f;
const int maxBallSpeed = 6;
const int brickWidth = 50;
const int brickHeight = 15;
const int gravityPullDown = 50;
const int maxLevelForGravity = 550;
const int buffWidth = 20;
const int buffHeight = 20;
const int nerfWidth = 20;
const int nerfHeight = 20;
const int rocketWidth = 2;
const int rocketHeight = 8;
const int invertPaddleDuration = 8;
const float maxAngle = 2.656;
const float minAngle = 0.4854;
const float rocketSpeed = 200.0f;
const float hitSpeedChangeOffset = 10.0f;
const int luckyBrickProbability = 3;
const int fps = 100;

extern int gElapsedTime;
extern int gRemainingTime;
extern int gScore;
extern int gLives;
extern int gBallHits;
extern int gBricksRemaining;
extern bool gVictory, gDefeat;
extern bool gGodMode;
extern float gBallPPx, gBallPPy;
extern float gPrevFTime;
extern float gFTime;


enum BrickColors{
	Red,
	DarkRed,
	Maroon,
	Yellow,
	Golden,
	Green,
	DarkGreen,
	Blue,
	DarkBlue,
	NUMBER_OF_COLORS
};

enum Buffs{
	LargerPaddle,
	ExtraLife,
	SuperBall,
	Rockets,
	StickyPaddle,
	PlusFifty,
	NUMBER_OF_BUFFS
};

enum Nerfs{
	SmallerPaddle,
	Gravity,
	InvertPaddle,
	InstantDeath,
	MinusFifty,
	NUMBER_OF_NERFS
};

extern SDL_Window* gWindow;
extern SDL_Surface* gScreen;
extern SDL_Surface* gBackground;
extern SDL_Event gEvent;
extern const Uint8 *gKeyStates;
extern TTF_Font* gFont;
extern SDL_Surface* gText;

extern Mix_Chunk* gCollision;
extern Mix_Chunk* gDeath;
extern Mix_Chunk* gFireRockets;
extern Mix_Chunk* gShrinkPaddle;
extern Mix_Chunk* gIncreasePaddle;
extern Mix_Chunk* gExtraLife;
extern Mix_Chunk* gGravity;
extern Mix_Chunk* gEquipRockets;
extern Mix_Chunk* gSuperBall;
extern Mix_Chunk* gStickyPaddle;
extern Mix_Chunk* gMinusFifty;
extern Mix_Chunk* gInvertPaddle;

#endif
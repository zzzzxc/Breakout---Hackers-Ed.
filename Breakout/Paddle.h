#ifndef PADDLE_H
#define PADDLE_H

#include"Globals.h"
#include"Sprite.h"

class Paddle : public Sprite{
public:
	void setProperties(float x, float y, int w=paddleWidth, int h=paddleHeight); //INITIALIZES THE OBJECT (THIS FUNCTION MUST BE CALLED ON THE OBJECT BEFORE USE)
	void setWidth(int w);	//SETS PADDLE WIDTH TO 'w'
	void drawRockets(SDL_Surface* dest);	//DRAWS ROCKETS ON THE 'dest' SURFACE
	void equipRockets();
	void fireRockets();
	void setRocketAmmo(int ammo);
	int getRocketAmmo();
	void updateRocketImages(std::map<SDL_Surface*, SDL_Rect> rocketImages); //UPDATE IMAGES OF ROCKETS THAT HAVEN'T COLLIDED OR ESCAPED ARENA YET
	std::map<SDL_Surface*, SDL_Rect>& getRocketImages();	//GET ACTIVE ROCKET IMAGES
	void setInvertState(bool state);	//TRUE: INVERT PADDLE, FALSE: PADDLE STAYS NORMAL
	bool getInvertState();
	void setInvertStartTime(int startTime);
	int getInvertStartTime();
	void setStickyPaddleState(bool state);	//TRUE: MAKE PADDLE STICKY, FALSE: DON'T DO ANYTHING
	bool getStickyPaddleState();
private:
	std::map<SDL_Surface*, SDL_Rect> mRocketImages;	//USED TO DRAW ROCKETS
	bool mRocketsEquipped;
	int mRocketAmmo;
	bool mInvertPaddle;
	int mInvertStartTime;
	bool mStickyPaddle;
};

extern Paddle p;

#endif
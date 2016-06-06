#ifndef BRICK_H
#define BRICK_H

#include"Globals.h"
#include"Sprite.h"

class Brick : public Sprite{ 
public:
	void setProperties(int color, float x, float y, int w=brickWidth, int h=brickHeight); //INITIALIZES THE OBJECT (THIS FUNCTION MUST BE CALLED ON THE OBJECT BEFORE USE)
	bool isLucky();		//RETURNS TRUE IF BRICK YIELDS SOME POWER
	bool isGolden();	//RETURNS TRUE IF BRICK IS GOLDEN
private:
	int mColor;
};

extern Brick brick[NUMBER_OF_BRICKS];

#endif
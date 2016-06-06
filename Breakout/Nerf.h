#ifndef NERF_H
#define NERF_H

#include"Globals.h"
#include"Sprite.h"

class Nerf : public Sprite{
public:
	void setProperties(float x, float y, int w=nerfWidth, int h=nerfHeight); //INITIALIZES THE OBJECT (THIS FUNCTION MUST BE CALLED ON THE OBJECT BEFORE USE)
	void activateNerf();
	void smallerPaddle();
	void gravity();
	void invertPaddle();
	void minusFifty();
	void instantDeath();
private:
	int mNerfType;
};

extern std::vector<Nerf> nerf;

#endif
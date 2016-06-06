#ifndef BUFF_H
#define BUFF_H

#include"Globals.h"
#include"Sprite.h"

class Buff : public Sprite{
public:
	void setProperties(float x, float y, int w=buffWidth, int h=buffHeight); //INITIALIZES THE OBJECT (THIS FUNCTION MUST BE CALLED ON THE OBJECT BEFORE USE)
	void activateBuff();
	void largerPaddle();
	void superBall();
	void extraLife();
	void rockets();
	void stickyPaddle();
	void plusFifty();
private:
	int mBuffType;
};

extern std::vector<Buff> buff;

#endif
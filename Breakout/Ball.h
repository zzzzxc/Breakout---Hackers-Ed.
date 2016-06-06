#ifndef BALL_H
#define BALL_H

#include"Globals.h"
#include"Sprite.h"

class Ball : public Sprite{
public:
	void setProperties(float x, float y, int w=ballWidth, int h=ballHeight); //INITIALIZES THE OBJECT (THIS FUNCTION MUST BE CALLED ON THE OBJECT BEFORE USE)
	void setVelocity(float xSpeed, float ySpeed);
	float getXSpeed();
	float getYSpeed();
	void setSuperBallState(bool state); //TRUE: ACTIVATES SUPERBALL; FALSE: DEACTIVATES SUPERBALL
	void initiate();	//INITIATES BALL MOVEMENT
	void halt();	//STOPS BALL MOVEMENT
	bool isSuperBall();	//RETURNS TRUE IF SUPERBALL IS ACTIVATED
	bool isInitiated();	//RETURNS TRUE IF THE BALL IS MOVING
	void setSuperBallStartTime(int startTime);
	int getSuperBallStartTime();
private:
	float mXSpeed;
	float mYSpeed;
	bool mSuperBall;
	bool mInitiated;
	int mSuperBallStartTime;
};

extern Ball b;
#endif
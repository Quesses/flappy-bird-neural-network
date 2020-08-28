#pragma once
#include "Config.h"
#include <iostream>
#include "MyRectangle.h"
using namespace std;
class Obstacle
{
private:
	double xPos, yPos, width, height, holeHeight, holeSize;
	MyRectangle topRect, bottomRect;
public:
	static double lastXPos;
	Obstacle(int holeHeight);
	void tick();
	void render();
	double getXPos() { return xPos; };
	double getHoleHeight() { return holeHeight; }
	double getHoleSize() { return holeSize; }
	MyRectangle getTopRect() { return topRect; }
	MyRectangle getBottomRect() { return bottomRect; }
};


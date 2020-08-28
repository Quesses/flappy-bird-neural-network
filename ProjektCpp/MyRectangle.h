#pragma once
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include "Config.h"
using namespace std;
class MyRectangle
{
private:
	int x, y, w, h;
public:
	MyRectangle();
	MyRectangle(int x, int y, int w, int h);
	bool collides(MyRectangle rect);
	void setX(int val) { x = val; }
	void setY(int val) { y = val; }
	void setHeight(int val) { h = val; }
	void setWidth(int val) { w = val; }
	void render();
	int getX() { return x; }
	int getY() { return y; }
	int getW() { return w; }
	int getH() { return h; }
};


#include "MyRectangle.h"
MyRectangle::MyRectangle()
	:x(0), y(0), w(25), h(25)
{

}
MyRectangle::MyRectangle(int x, int y, int w, int h)
	: x(x), y(y), w(w), h(h)
{

}

bool MyRectangle::collides(MyRectangle rect) {
	if (rect.x < x + w &&
		rect.x + rect.w > x&&
		rect.y < y + h &&
		rect.y + rect.h > y) {
		return true;
	}

	return false;
}

void MyRectangle::render() {
	al_draw_filled_rectangle(x, y, x + w, y + h, al_map_rgb(255, 255, 255));
}
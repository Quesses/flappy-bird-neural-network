#include "Obstacle.h"

double Obstacle::lastXPos = Config::getStartingObstaclePositionX();
Obstacle::Obstacle(int holeHeight)
	:xPos(lastXPos), yPos(0), width(Config::getObstacleWidth()), height(Config::getWinHeight()), holeHeight(holeHeight), holeSize(Config::getObstacleHoleSize())

{
	topRect = MyRectangle(xPos, yPos, width, holeHeight);
	bottomRect = MyRectangle(xPos, holeHeight + holeSize, width, height);
	lastXPos += Config::getSpaceBetweenObstacles();

}
void Obstacle::tick() {
	xPos -= Config::getBirdVelocityX();
	if (xPos + Config::getObstacleWidth() < 0) {
		xPos += Config::getSpaceBetweenObstacles() * Config::getObstacleCount();
		holeHeight = rand() % (Config::getWinHeight() - 250 - Config::getObstacleHoleSize()) + 25;
	}

	topRect.setX(xPos); //Do wyjebania
	bottomRect.setX(xPos); //Do wyjebania
	topRect.setHeight(holeHeight);
	bottomRect.setY(holeHeight + holeSize);
}
void Obstacle::render() {
	al_draw_bitmap(Config::getBottomObstacleImage(), xPos, holeHeight + holeSize, 0);
	al_draw_bitmap(Config::getTopObstacleImage(), xPos, -al_get_bitmap_height(Config::getTopObstacleImage()) + holeHeight, 0);
}


#include "Bird.h"

unsigned Bird::deathsNumber = 0;
unsigned Bird::bestDistanceEver = 0;

Bird::Bird()
	:velocityY(Config::getBirdVelocityY()), xPosition(Config::getDefaultBirdStartingPositionX()), yPosition(Config::getDefaultBirdStartingPositionY()),
	closestObstacle(NULL), isDead(false), width(al_get_bitmap_width(Config::getBirdImage())), height(al_get_bitmap_width(Config::getBirdImage())),
	birdDistance(0), fitness(0.0)
{
	rect = MyRectangle(xPosition + width / 4, yPosition + height / 4, width / 2, height / 2);
	net = NeuralNetwork(vector<unsigned>{5, 4, 3, 1});
}
void Bird::tick() {
	handleBirdMovement();
	updateCollisionRectPosition();
	if (checkForCollision() && !isDead) {
		isDead = true;
		deathsNumber++;
		al_play_sample(Config::getHitSoundEffec(), 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
	}

}
void Bird::render() {
	float radianAngle = atan(velocityY / Config::getBirdVelocityX());
	al_draw_rotated_bitmap(Config::getBirdImage(), width / 2, height / 2, xPosition + width / 2, yPosition + height / 2, radianAngle, 0);
	//rect.render();
	al_draw_textf(Config::getFont30(), al_map_rgb(255, 255, 255), 25, 75, 0, "Distance: %d", (int)birdDistance);
}
void Bird::updateCollisionRectPosition() {
	rect.setX(xPosition + width / 4);
	rect.setY(yPosition + height / 4);
}
void Bird::handleBirdMovement() {
	if (closestObstacle != NULL)
		net.feedForward(prepareNeuralNetInput());

	if (velocityY < Config::getMaxBirdVelocityY())
		velocityY += Config::getGravityForce();

	if ((net.getResult() > 0.5 && !isDead))
		//if(Config::isSpacePressed())
	{
		velocityY = -450.0 / 60;
	}
	if (yPosition > 0 || velocityY > 0)
		yPosition += velocityY;
	else
		velocityY = 0;
	if (!isDead) {
		birdDistance += Config::getBirdVelocityX() / Config::getSpaceBetweenObstacles();
		if (birdDistance > bestDistanceEver)
			bestDistanceEver = birdDistance;
	}

}
void Bird::searchForClosestObstacle(std::vector<Obstacle>& obstacles) {
	double minDist = Config::getWinWidth();

	for (Obstacle& o : obstacles)
		if ((o.getXPos() + Config::getObstacleWidth() - xPosition < minDist) and (o.getXPos() + Config::getObstacleWidth() - xPosition > 0)) {
			closestObstacle = &o;
			minDist = o.getXPos() - xPosition;
		}
}
bool Bird::checkForCollision() {
	if (closestObstacle != NULL) {


		if (rect.collides(closestObstacle->getTopRect()) or rect.collides(closestObstacle->getBottomRect()))
			return true;
		if (yPosition > (int)Config::getWinHeight() - al_get_bitmap_height(Config::getGroundImage())) {
			return true;
		}
	}
	return false;
}
vector<double> Bird::prepareNeuralNetInput() {
	vector<double> input;
	if (closestObstacle != NULL) {
		input.push_back(closestObstacle->getXPos() - xPosition); // odleglosc ptaka od poczatku przeszkody
		input.push_back(closestObstacle->getXPos() - xPosition + Config::getObstacleWidth()); // odleglosc ptaka od konca przeszkody
		input.push_back(yPosition - closestObstacle->getHoleHeight()); // roznica wysokosci ptaka i gornej przeszkody
		input.push_back(yPosition - closestObstacle->getHoleHeight() - closestObstacle->getHoleSize());  // roznica wysokosci dolnej przeszkody i ptaka
		input.push_back(velocityY);
	}

	return input;
}
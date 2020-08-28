#include "Game.h"
Game::Game()
	:geneticAlgorithm(GeneticAlgorithm(birds, Config::getBirdsNumber(), Config::getCrossoverRate(), Config::getMutationRate(), 10))
{
	geneticAlgorithm.createRandomPopulation();

	for (unsigned i = 0; i < Config::getObstacleCount(); i++)
		obstacles.push_back(Obstacle(rand() % (Config::getWinHeight() - Config::getObstacleHoleSize() - 250) + 25)); //wysokosc dziury

}
void Game::tick() {

	for (Obstacle& o : obstacles) {
		o.tick();
	}

	for (Bird& b : birds) {
		if (!b.getIsDead()) {
			b.tick();
			b.searchForClosestObstacle(obstacles);
		}
	}
	if (Bird::deathsNumber == Config::getBirdsNumber()) {
		Bird::deathsNumber = 0;
		GeneticAlgorithm::generation++;
		resetObstaclesPosition();
		geneticAlgorithm.createNextPopulation();
	}
}
void Game::render() {
	handleBackgroundRender();
	for (Obstacle& o : obstacles)
		o.render();
	for (Bird& b : birds)
		if (!b.getIsDead()) {
			b.render();
		}
	handleGroundRender();
	
	al_draw_textf(Config::getFont30(), al_map_rgb(255, 255, 255), 25, 25, 0, "GENERATION: %d", GeneticAlgorithm::generation);
	al_draw_textf(Config::getFont30(), al_map_rgb(255, 255, 255), 25, 50, 0, "BEST: %d", Bird::bestDistanceEver);
	al_draw_textf(Config::getFont30(), al_map_rgb(255, 255, 255), 25, 100, 0, "ALIVE: %d", Config::getBirdsNumber() - Bird::deathsNumber);

	switch (Config::getOption()) {
	case 1:
		al_draw_textf(Config::getFont30(), al_map_rgb(244, 69, 69), 25, 690, 0, "CROSSOVER RATE: %.2f", Config::getCrossoverRate());
		al_draw_textf(Config::getFont30(), al_map_rgb(88, 97, 60), 25, 715, 0, "MUTATION RATE: %.3f", Config::getMutationRate());
		al_draw_textf(Config::getFont30(), al_map_rgb(88, 97, 60), 25, 740, 0, "FPS: %d", Config::getFPS());
		break;
	case 2:
		al_draw_textf(Config::getFont30(), al_map_rgb(88, 97, 60), 25, 690, 0, "CROSSOVER RATE: %.2f", Config::getCrossoverRate());
		al_draw_textf(Config::getFont30(), al_map_rgb(244, 69, 69), 25, 715, 0, "MUTATION RATE: %.3f", Config::getMutationRate());
		al_draw_textf(Config::getFont30(), al_map_rgb(88, 97, 60), 25, 740, 0, "FPS: %d", Config::getFPS());
		break;
	case 3:
		al_draw_textf(Config::getFont30(), al_map_rgb(88, 97, 60), 25, 690, 0, "CROSSOVER RATE: %.2f", Config::getCrossoverRate());
		al_draw_textf(Config::getFont30(), al_map_rgb(88, 97, 60), 25, 715, 0, "MUTATION RATE: %.3f", Config::getMutationRate());
		al_draw_textf(Config::getFont30(), al_map_rgb(244, 69, 69), 25, 740, 0, "FPS: %d", Config::getFPS());
		break;
	}


	al_draw_textf(Config::getFont30(), al_map_rgb(88, 97, 60), 400, 690, 0, "POPULATION: %d", Config::getBirdsNumber());
	
	
	
}

void Game::handleBackgroundRender() {
	if (bgPosX1 <= -al_get_bitmap_width(Config::getBgImage())) bgPosX1 = 0;
	for (int i = 0; i < int(Config::getWinWidth() / al_get_bitmap_width(Config::getBgImage()) + 2); i++) {  //do poprawy aby dostosowywalo sie do wielkosci ekranu
		al_draw_bitmap(Config::getBgImage(), i * al_get_bitmap_width(Config::getBgImage()) + bgPosX1, 0, 0); //sub_bitmap xd
	}
	bgPosX1--; //szybkosc przemieszczania sie tla

}

void Game::handleGroundRender() {
	if (groundPosX <= -al_get_bitmap_width(Config::getGroundImage()))
		groundPosX = 0;
	for (int i = 0; i < int(Config::getWinWidth() / al_get_bitmap_width(Config::getGroundImage()) + 2); i++) {
		al_draw_bitmap(Config::getGroundImage(), i * al_get_bitmap_width(Config::getGroundImage()) + groundPosX, Config::getWinHeight() - al_get_bitmap_height(Config::getGroundImage()), 0);
	}
	groundPosX -= Config::getBirdVelocityX();
}

void Game::resetObstaclesPosition() {
	obstacles.clear();
	Obstacle::lastXPos = Config::getStartingObstaclePositionX();
	for (unsigned i = 0; i < Config::getObstacleCount(); i++)
		obstacles.push_back(Obstacle(rand() % (Config::getWinHeight() - Config::getObstacleHoleSize() - 250) + 25)); //wysokosc dziury
}
#pragma once
#include<allegro5\allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <vector>
#include "Config.h"
#include "GeneticAlgorithm.h"
#include "Bird.h"
#include "Obstacle.h"
#include <time.h>
#include <iostream>
using namespace std;
class Game
{
private:
	int bgPosX1, groundPosX;
	vector<Bird> birds;
	vector<Obstacle> obstacles;
	GeneticAlgorithm geneticAlgorithm;
	void handleBackgroundRender(); // renderuje tlo
	void handleGroundRender(); // renderuje podloze
	void resetObstaclesPosition(); // resetuje przeszkody
public:
	Game();
	void tick(); // oblicza nastepny fps gry
	void render(); // rysuje gre na ekranie
};


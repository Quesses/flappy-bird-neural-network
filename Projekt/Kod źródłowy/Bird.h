#pragma once
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "Config.h"
#include "Obstacle.h"
#include "MyRectangle.h"
#include <vector>
#include "NeuralNetwork.h"
typedef vector<int> chromosome;
class Bird
{
private:
	NeuralNetwork net;
	vector<chromosome> chromosomes;
	double reproductionChanceInterval[2]; //metoda ruletki ustawiany jest przedzial liczbowy do rozmnazania, np [0, 0.12], kolejny ptak [0.12, 0.43] itd. az do [x, 1]
	int xPosition, yPosition;
	int width, height;
	double velocityY;
	double birdDistance;
	double fitness;
	MyRectangle rect;
	Obstacle* closestObstacle; 
	void updateCollisionRectPosition(); //przemieszczenie hitboxa ptaka
	void handleBirdMovement(); //Przemieszczenie ptaka
	bool checkForCollision(); //Sprawdza czy ptakt jest w kolizji z ktoras z przeszkod
	bool isDead;
	vector<double> prepareNeuralNetInput(); // Przygotowuje wartosci inputowe do sieci neuronowej, zwraca wszystkie parametry

public:
	static unsigned deathsNumber; //ilosc martwych ptakow, wspolna zmienna dla wszystkich
	static unsigned bestDistanceEver; //przebyta wartosc najlepszego ptaka

	Bird();
	void tick(); // Przemieszczenie sie ptaka i sprawdzenie kolizji z przeszkoda
 	void render(); // Narysowanie ptaka na ekranie
	void searchForClosestObstacle(std::vector<Obstacle>& obstacles); // sprawdzanie do ktorej przeszkody jest najnizszy nieujemny dystans

	/*GETTERS & SETTERS*/
	bool getIsDead() { return isDead; }
	double getFitness() { return fitness; }
	void setFitness(double val) { fitness = val; }
	double* getReproductionChanceInterval() { return reproductionChanceInterval; }
	void setReproductionChanceInterval(double start, double end) { reproductionChanceInterval[0] = start; reproductionChanceInterval[1] = end; }
	double getDistance() { return birdDistance; }
	vector<chromosome>& getChromosomes() { return chromosomes; }
	void setChromosomes(vector<chromosome> val) { chromosomes = val; }
	NeuralNetwork& getNet() { return net; }

};


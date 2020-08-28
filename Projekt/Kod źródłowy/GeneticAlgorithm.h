#pragma once
#include <vector>
#include "Bird.h"
#include "NeuralNetwork.h"
#include <time.h>

using namespace std;
class GeneticAlgorithm
{
private:
	double mutationRate; // szansa na mutacje pojedynczego genu
	double crossoverRate; // szansa na krzyzowanie genow
	unsigned populationSize;
	unsigned genesResolution; // rozdzielczosc liczby kodowanej przez gen [-lg(X)] <- lg to log o podstawie 2, dla parametru =10 geny koduja liczby z dokladnoscia do 0,0009765625‬

	vector<Bird>& population;
	void setFitness(Bird& bird); // na podstawie punktow zdobytych przez ptaka ustawia wartosc poziomu dopasowania sieci
	Bird crossover(Bird& parent1, Bird& parent2); // bierze geny dwoch osobnikow i na ich podstawie tworzy nowego
	void mutate(Bird& bird); // zwykla mutacja
	Bird pickRandomBird(); // losuje ptaka zgodnie z zasada ruletki
	double decodeChromosome(vector<int> chromosome); // wyciaga wartosc liczbowa z kodu genetycznego chromosomu
	void setWeightsAccordingToGenes(Bird& bird);
	void setReproductionChanceInterval();
	void setRandomChromosomes(Bird& b);
	vector<int> randomSingleChromosome();
public:
	GeneticAlgorithm(vector<Bird>& birdsPopulation, unsigned populationSize, double crossoverRate, double mutationRate, unsigned genesResolution);
	void createNextPopulation();
	void createRandomPopulation();
	void printGenerationData();
	static unsigned generation;

};


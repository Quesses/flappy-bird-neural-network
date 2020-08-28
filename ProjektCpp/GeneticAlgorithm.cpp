#include "GeneticAlgorithm.h"

unsigned GeneticAlgorithm::generation = 1;

GeneticAlgorithm::GeneticAlgorithm(vector<Bird>& birdsPopulation, unsigned populationSize, double crossoverRate, double mutationRate, unsigned genesResolution)

	:population(birdsPopulation), populationSize(populationSize), crossoverRate(crossoverRate), mutationRate(mutationRate), genesResolution(genesResolution)
{
	srand(time(NULL));
}
void GeneticAlgorithm::createNextPopulation() 
{

	mutationRate = Config::getMutationRate();
	crossoverRate = Config::getCrossoverRate();

	for (Bird& b : population)
		setFitness(b);

	setReproductionChanceInterval();

	//tworzenie nowej populacji
	vector<Bird>* newPopulation = new vector<Bird>(); // tu beda przechowywane nowe ptaki
	for (unsigned birdNum = 0; birdNum < populationSize; ++birdNum) { // tworzenie tylu nowych ptakow, ile wynosi obecna populacja
		Bird* newBird = new Bird();
		if (rand() / (double)RAND_MAX < crossoverRate) {
			Bird parent1 = pickRandomBird();
			Bird parent2 = pickRandomBird();
			*newBird = crossover(parent1, parent2);
		}
		else {
			*newBird = pickRandomBird();
		}
		mutate(*newBird); //funkcja probuje zmutowac kazdy gen ptaka z szansa 0.003, jest zawsze wywolana na kazdym ptaku
		setWeightsAccordingToGenes(*newBird); //odkodowuje geny i zmienia wagi na polaczeniach neuronow
		newPopulation->push_back(*newBird);
	}


	population.clear();
	population = *newPopulation;
	delete newPopulation;

}

void GeneticAlgorithm::setFitness(Bird& bird) {
	bird.setFitness(3.0 + pow(bird.getDistance(), 2.0));
}
Bird GeneticAlgorithm::crossover(Bird& parent1, Bird& parent2) {
	Bird* child = new Bird();
	chromosome ch;
	int randomValue = 0;
	for (unsigned i = 0; i < parent1.getChromosomes().size(); ++i) {
		randomValue = rand() % parent1.getChromosomes().size();
		for (int geneNum = 0; geneNum < parent1.getChromosomes()[i].size(); geneNum++) {
			if (geneNum < randomValue)
				ch.push_back(parent1.getChromosomes()[i][geneNum]);
			else
				ch.push_back(parent2.getChromosomes()[i][geneNum]);

		}
		child->getChromosomes().push_back(ch);
		ch.clear();
	}
	return *child;
}
void GeneticAlgorithm::mutate(Bird& bird) {
	for (chromosome& ch : bird.getChromosomes())
		for (int& gene : ch)
			if (rand() / (double)RAND_MAX < mutationRate) {
				gene = !gene;
			}
}

Bird GeneticAlgorithm::pickRandomBird() {
	double val = rand() / (double)RAND_MAX;
	Bird newBird;
	for (Bird b : population)
		if (val >= b.getReproductionChanceInterval()[0] and val < b.getReproductionChanceInterval()[1]) {
			newBird.setChromosomes(b.getChromosomes());
			return newBird;
		}

}

void GeneticAlgorithm::setWeightsAccordingToGenes(Bird& b) {
	int index = 0;
	vector<vector<Neuron>>& layers = b.getNet().getLayers();
	for (vector<Neuron>& layer : layers)
		for (Neuron& n : layer)
			for (unsigned i = 0; i < n.getConnections().size(); ++i) {

				n.setConnectionWeight(i, decodeChromosome(b.getChromosomes()[index]) * 2 - 1); // <--------------- losuje liczbe z przedzialu -1 do 1
				index++;
			}
}

void GeneticAlgorithm::createRandomPopulation() {
	population.clear();
	for (unsigned i = 0; i < populationSize; ++i)
		population.push_back(Bird());
	for (Bird& b : population)
		setRandomChromosomes(b);
}

void GeneticAlgorithm::setReproductionChanceInterval() {
	double sum = 0.0;
	double currentIntervalStartingPosition = 0.0;
	for (Bird& b : population)
		sum += b.getFitness();
	for (Bird& b : population) {
		b.setReproductionChanceInterval(currentIntervalStartingPosition, currentIntervalStartingPosition + b.getFitness() / sum);
		currentIntervalStartingPosition += b.getFitness() / sum;
	}
}
void GeneticAlgorithm::setRandomChromosomes(Bird& b) {
	vector<int> chromosome;
	b.getChromosomes().clear();

	vector<vector<Neuron>>& layers = b.getNet().getLayers();
	for (vector<Neuron>& layer : layers)
		for (Neuron& n : layer)
			for (unsigned i = 0; i < n.getConnections().size(); ++i) {
				chromosome = randomSingleChromosome();
				b.getChromosomes().push_back(chromosome);
				n.setConnectionWeight(i, decodeChromosome(chromosome) * 2 - 1); // <--------------- losuje liczbe z przedzialu -1 do 1

			}
}
void GeneticAlgorithm::printGenerationData() {
	for (Bird& b : population) {
		cout << "Rep. %: " << b.getReproductionChanceInterval()[1] - b.getReproductionChanceInterval()[0];

		cout << endl;
	}
}
vector<int> GeneticAlgorithm::randomSingleChromosome() {
	vector<int> chromosome;
	for (int i = 0; i < genesResolution; ++i) {
		if (rand() % 2 == 0)
			chromosome.push_back(0);
		else
			chromosome.push_back(1);
	}
	return chromosome;
}
double GeneticAlgorithm::decodeChromosome(vector<int> chromosome) {
	double val = 0.0;
	double base = 0.5;
	for (int gene : chromosome) {
		val += base * gene;
		base = base * 0.5;
	}
	return val;
}
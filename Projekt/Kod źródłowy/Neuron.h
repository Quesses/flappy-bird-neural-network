#pragma once
#include <vector>
#include <time.h>
#include <iostream>
#include <cstdlib>
#include <windows.h>
using namespace std;
class Neuron;
typedef std::vector<Neuron> layer;
struct connection {
	double weight;
};

class Neuron
{
private:
	double value;
	unsigned m_myIndex;
	vector<connection> m_outputWeights;
	double randWeight() { return 2.0 * rand() / (double)RAND_MAX - 1.0; }
public:
	Neuron(unsigned numOutputs, unsigned myIndex);
	void setValue(double val) { value = val; }
	double getValue() { return value; }
	void setConnectionWeight(unsigned index, double value) { m_outputWeights[index].weight = value; }
	vector<connection>& getConnections() { return m_outputWeights; }
	void feedForward(layer& prevLayer);

};


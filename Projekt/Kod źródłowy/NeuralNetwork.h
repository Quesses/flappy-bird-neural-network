#pragma once
#include <cassert>
#include <vector>
#include <iostream>
#include "Neuron.h"
using namespace std;
class NeuralNetwork
{
private:
	vector<layer> layers;
public:
	NeuralNetwork();
	NeuralNetwork(vector<unsigned> topology);
	void feedForward(vector<double> inputValues);
	double getResult();
	void scaleInput(vector<double>& inputValues);
	vector<layer>& getLayers() { return layers; }
};


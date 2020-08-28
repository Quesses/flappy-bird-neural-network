#include "NeuralNetwork.h"
NeuralNetwork::NeuralNetwork() {}
NeuralNetwork::NeuralNetwork(vector<unsigned> topology)
{
	unsigned numLayers = topology.size();
	for (unsigned layerNum = 0; layerNum < numLayers; layerNum++) {
		layers.push_back(layer());
		unsigned numOutputs = layerNum == topology.size() - 1 ? 0 : topology[layerNum + 1] + 1;
		for (unsigned neuronNum = 0; neuronNum <= topology[layerNum]; neuronNum++) {
			layers.back().push_back(Neuron(numOutputs, neuronNum));
		}
		layers.back().back().setValue(1.0);
	}
}

void NeuralNetwork::feedForward(vector<double> inputValues) {
	scaleInput(inputValues);
	assert(inputValues.size() == layers[0].size() - 1);
	for (unsigned index = 0; index < inputValues.size(); index++)
		layers[0][index].setValue(inputValues[index]);


	for (unsigned layerNum = 1; layerNum < layers.size(); layerNum++)
		for (unsigned neuronNum = 0; neuronNum < layers[layerNum].size(); neuronNum++) {
			layers[layerNum][neuronNum].feedForward(layers[layerNum - 1]);
		}



}

double NeuralNetwork::getResult() {
	return layers.back().back().getValue();
}

void NeuralNetwork::scaleInput(vector<double>& inputValues) {
	vector<double> resultVector;
	double squareSum = 0.0;
	for (double value2 : inputValues)
		squareSum += value2 * value2;
	squareSum = sqrt(squareSum);
	for (double value : inputValues) {
		resultVector.push_back(value / squareSum);
	}

	inputValues = resultVector;
}
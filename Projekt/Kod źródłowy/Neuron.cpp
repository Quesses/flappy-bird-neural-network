#include "Neuron.h"

Neuron::Neuron(unsigned numOutputs, unsigned myIndex) {
	for (unsigned num = 0; num < numOutputs; num++) {
		m_outputWeights.push_back(connection());
		m_outputWeights.back().weight = 0.0;
	}
	m_myIndex = myIndex;
}

void Neuron::feedForward(layer& prevLayer) {

	double sum = 0.0;
	for (unsigned index = 0; index < prevLayer.size(); index++)
		sum += prevLayer[index].getValue() * prevLayer[index].m_outputWeights[m_myIndex].weight;

	value = tanh(sum);
}
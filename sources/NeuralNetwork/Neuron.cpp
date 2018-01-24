//
// Neuron.cpp for  in /Users/vicostudio/Documents/Shared Folder/Work/NeuralNetwork/CPP/BasicNeural/sources/
//
// Made by Sousa Victor
// Login   <sousa_v@epitech.eu>
//
// Started on  Sun Apr 23 19:12:47 2017 Sousa Victor
// Last update Thu Jun  1 17:38:36 2017 Sousa Victor
//

#include "Neuron.hpp"

Neural::Neuron::Neuron(unsigned numOutputs, unsigned myIndex, double eta, double alpha) {
    this->_eta = eta;
    this->_alpha = alpha;
    for (unsigned c = 0; c < numOutputs; ++c) {
        this->_outputWeights.push_back(Connection());
        this->_outputWeights.back().weight = randomWeight();
    }

    this->_myIndex = myIndex;
}

Neural::Neuron::~Neuron() {

}

Neural::Neuron::Neuron(const Neural::Neuron &neuron) {
    this->_eta = neuron._eta;
    this->_alpha = neuron._alpha;
    this->_outputVal = neuron._outputVal;
    this->_outputWeights = neuron._outputWeights;
    this->_myIndex = neuron._myIndex;
    this->_gradient = neuron._gradient;
}

Neural::Neuron &Neural::Neuron::operator =(const Neural::Neuron &neuron) {
    this->_eta = neuron._eta;
    this->_alpha = neuron._alpha;
    this->_outputVal = neuron._outputVal;
    this->_outputWeights = neuron._outputWeights;
    this->_myIndex = neuron._myIndex;
    this->_gradient = neuron._gradient;
    return *this;
}

void Neural::Neuron::setOutputVal(double val) {
    this->_outputVal = val;
}

double Neural::Neuron::getOutputVal(void) const {
    return this->_outputVal;
}

void Neural::Neuron::feedForward(const Layer &prevLayer) {
    double sum = 0.0;

    // Sum the previous layer's outputs (which are our inputs)
    // Include the bias node from the previous layer.
    for (unsigned n = 0; n < prevLayer.size(); ++n) {
        sum += prevLayer[n].getOutputVal() *
                prevLayer[n]._outputWeights[this->_myIndex].weight;
    }
    this->_outputVal = Neural::Neuron::transferFunction(sum);
}

void Neural::Neuron::calcOutputGradients(double targetVal) {
    double delta = targetVal - this->_outputVal;
    this->_gradient = delta * Neural::Neuron::transferFunctionDerivative(this->_outputVal);
}

void Neural::Neuron::calcHiddenGradients(const Layer &nextLayer) {
    double dow = sumDOW(nextLayer);
    this->_gradient = dow * Neural::Neuron::transferFunctionDerivative(this->_outputVal);
}

void Neural::Neuron::updateInputWeights(Layer &prevLayer) {
    // The weights to be updated are in the Connection container
    // in the neurons in the preceding layer
    for (unsigned n = 0; n < prevLayer.size(); ++n) {
        Neuron &neuron = prevLayer[n];
        double oldDeltaWeight = neuron._outputWeights[this->_myIndex].deltaWeight;

        double newDeltaWeight =
                // Individual input, magnified by the gradient and train rate:
                this->_eta
                * neuron.getOutputVal()
                * this->_gradient
                // Also add momentum = a fraction of the previous delta weight;
                + this->_alpha
                * oldDeltaWeight;

        neuron._outputWeights[this->_myIndex].deltaWeight = newDeltaWeight;
        neuron._outputWeights[this->_myIndex].weight += newDeltaWeight;
    }
}

std::vector<Neural::INeuron::Connection> const &Neural::Neuron::getConnection() const {
    return this->_outputWeights;
}

void Neural::Neuron::setConnection(unsigned index, Neural::INeuron::Connection const &data) {
    this->_outputWeights[index].weight = data.weight;
    this->_outputWeights[index].deltaWeight = data.deltaWeight;
}

unsigned Neural::Neuron::getConnectionCount() const {
    return this->_outputWeights.size();
}

double Neural::Neuron::transferFunction(double x) const {
    // tanh - output range [-1.0..1.0]
    return tanh(x);
}

double Neural::Neuron::transferFunctionDerivative(double x) const {
    // tanh derivative
    return 1.0 - x * x;
}

double Neural::Neuron::randomWeight(void) const {
     return (static_cast <double> (std::rand()) / static_cast <double> (RAND_MAX)) - (static_cast <double> (std::rand()) / static_cast <double> (RAND_MAX));
}

double Neural::Neuron::sumDOW(const Neural::Layer &nextLayer) const {
    double sum = 0.0;

    // Sum our contributions of the errors at the nodes we feed.
    for (unsigned n = 0; n < nextLayer.size() - 1; ++n) {
        sum += this->_outputWeights[n].weight * nextLayer[n]._gradient;
    }
    return sum;
}

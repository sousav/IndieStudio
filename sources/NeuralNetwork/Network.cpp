//
// Network.cpp for  in /Users/vicostudio/Documents/Shared Folder/Work/NeuralNetwork/CPP/BasicNeural/sources/
//
// Made by Sousa Victor
// Login   <sousa_v@epitech.eu>
//
// Started on  Sun Apr 23 19:21:31 2017 Sousa Victor
// Last update Thu Jun  1 14:13:45 2017 Sousa Victor
//

#include "Network.hpp"

Neural::Network::Network(const std::vector<unsigned> &topology, double recentAverageSmoothingFactor): ANetworkData(topology, recentAverageSmoothingFactor) {

}

Neural::Network::~Network() {

}

Neural::Network::Network(const Neural::Network &network) : ANetworkData(network) {

}

Neural::Network &Neural::Network::operator=(const Neural::Network &network) {
    Neural::ANetworkData::operator=(network);
    return *this;
}

void Neural::Network::train(INetworkTrainer const &trainer) {
    std::vector<Neural::INetworkTrainer::TrainingData> const trainingData = trainer.getTrainingData();

    int trainingPass = 0;
    for (auto const &data: trainingData) {
        if (trainer.getDebugFLag()) {
            std::cout << std::endl << "Pass " << trainingPass;
            showVectorVals(": Inputs:", data.input);
        }
        this->feedForward(data.input);
        std::vector<double> result = this->getResults();
        if (trainer.getDebugFLag()) {
            showVectorVals("Outputs:", result);
            showVectorVals("Targets:", data.output);
        }
        if (data.output.size() != trainer.getTopology().back()) {
            throw Neural::InvalidTrainingFile("Your are requesting " + std::to_string(data.output.size()) + " output data but your network can only output " + std::to_string(trainer.getTopology().back()) + "..");
            return;
        }
        this->backProp(data.output);
        if (trainer.getDebugFLag())
            std::cout << "Network recent average error: " << this->getRecentAverageError() << std::endl;

        trainingPass++;
    }
    if (trainer.getDebugFLag())
        std::cout << std::endl << "Done" << std::endl;
}

void Neural::Network::feedForward(const std::vector<double> &inputVals) {
    if (inputVals.size() != this->_layers[0].size() - 1) {
        throw Neural::InvalidInput("You want to input " + std::to_string(inputVals.size()) + " values but your network can only accept " + std::to_string(this->_layers[0].size() - 1));
    }

    // Assign (latch) the input values into the input neurons
    for (unsigned i = 0; i < inputVals.size(); ++i) {
        this->_layers[0][i].setOutputVal(inputVals[i]);
    }

    // forward propagate
    for (unsigned layerNum = 1; layerNum < this->_layers.size(); ++layerNum) {
        Layer &prevLayer = this->_layers[layerNum - 1];
        for (unsigned n = 0; n < this->_layers[layerNum].size() - 1; ++n) {
            this->_layers[layerNum][n].feedForward(prevLayer);
        }
    }
}

std::vector<double> const Neural::Network::getResults() const {
    std::vector<double> resultVals;

    for (unsigned n = 0; n < this->_layers.back().size() - 1; ++n) {
        resultVals.push_back(this->_layers.back()[n].getOutputVal());
    }
    return resultVals;
}

void Neural::Network::backProp(const std::vector<double> &targetVals) {
    // Calculate overall net error (RMS of output neuron errors)
    Layer &outputLayer = this->_layers.back();
    this->_error = 0.0;

    for (unsigned n = 0; n < outputLayer.size() - 1; ++n) {
        double delta = targetVals[n] - outputLayer[n].getOutputVal();
        this->_error += delta * delta;
    }
    this->_error /= outputLayer.size() - 1; // get average error squared
    this->_error = sqrt(this->_error); // RMS

    // Implement a recent average measurement
    this->_recentAverageError = (this->_recentAverageError * this->_recentAverageSmoothingFactor + this->_error) / (this->_recentAverageSmoothingFactor + 1.0);

    // Calculate output layer gradients
    for (unsigned n = 0; n < outputLayer.size() - 1; ++n) {
        outputLayer[n].calcOutputGradients(targetVals[n]);
    }

    // Calculate hidden layer gradients
    for (unsigned layerNum = this->_layers.size() - 2; layerNum > 0; --layerNum) {
        Layer &hiddenLayer = this->_layers[layerNum];
        Layer &nextLayer = this->_layers[layerNum + 1];
        for (unsigned n = 0; n < hiddenLayer.size(); ++n) {
            hiddenLayer[n].calcHiddenGradients(nextLayer);
        }
    }

    // For all layers from outputs to first hidden layer,
    // update connection weights
    for (unsigned layerNum = this->_layers.size() - 1; layerNum > 0; --layerNum) {
        Layer &layer = this->_layers[layerNum];
        Layer &prevLayer = this->_layers[layerNum - 1];
        for (unsigned n = 0; n < layer.size() - 1; ++n) {
            layer[n].updateInputWeights(prevLayer);
        }
    }
}

Neural::Genome Neural::Network::toGenome() const {
    Neural::Genome genome;

    std::vector<float> weight;
    for (auto const &layer: this->_layers) {
        for (auto const &neuron: layer) {
            std::vector<Neural::INeuron::Connection> connections = neuron.getConnection();
            for (auto const &connection: connections) {
                weight.push_back(connection.weight);
            }
        }
    }

    genome.setWeights(weight);

    return genome;
}

void Neural::Network::fromGenome(Neural::Genome const &genome) {
    std::vector<float> weight = genome.getWeights();
    int i = 0;
    for (auto const &layer: this->_layers) {
        for (auto const &neuron: layer) {
            std::vector<Neural::INeuron::Connection> connections = neuron.getConnection();
            for (auto const &connection: connections) {
                i++;
            }
        }
    }
    if (i != weight.size()) {
        throw Neural::InvalidInput("You want to load a genome which has " + std::to_string(weight.size()) + " neurons in a network that contains " + std::to_string(i) + " neurons...");
    }

    i = 0;
    for (auto const &layer: this->_layers) {
        for (auto const &neuron: layer) {
            std::vector<Neural::INeuron::Connection> connections = neuron.getConnection();
            for (auto &connection: connections) {
                connection.weight = weight[i];
                i++;
            }
        }
    }
}

void Neural::Network::showVectorVals(std::string const &label, std::vector<double> const &v) const {
    std::cout << label << " ";
    for (unsigned i = 0; i < v.size(); ++i) {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;
}

std::ostream &operator<<(std::ostream& os, const Neural::Network &network) {
    os << std::endl << "|------------- NETWORK INFO -------------|" << std::endl;
    std::vector<Neural::Layer> const layers = network.getLayer();
    os << "\tNetwork has " << network.getLayerCount() << " layer" << (network.getLayerCount() > 1 ? "s" : "") << std::endl;
    os << "\tIt takes " << network.getInputCount() << " input" << (network.getInputCount() > 1 ? "s" : "") <<" and give in return " << network.getOutputCount() << " output" << (network.getOutputCount() > 1 ? "s" : "") << std::endl;
    os << "\tIt has a total of " << network.getNeuronCount() << " neurons and " << network.getConnectionCount() << " connections" << std::endl;
    os << "\tIts recent average error factor is " << network.getRecentAverageError() << std::endl;
    os << std::endl << "\t|--------- Layer Status ---------|" << std::endl;
    unsigned i = 0;
    for (auto const &layer: layers) {
        os << "\t\tLayer " << i << (i == 0 ? ", Input layer" : i == layers.size() - 1 ? ", Output layer" : "") << ", " << layer.size() - 1 << " neuron" << (layer.size() - 1 > 1 ? "s" : "") << std::endl;
        unsigned j = 0;
        for (auto const &neuron: layer) {
            std::vector<Neural::INeuron::Connection> connections = neuron.getConnection();
            os << "\t\t\tNeuron " << j << " with " << connections.size() << " connection" << (connections.size() > 1 ? "s" : "") << (j == layer.size() - 1 ? " (bias neuron)" : "") << std::endl;
            unsigned k = 0;
            for (auto const &connection: connections) {
                os << "\t\t\t\tConnection " << k << " with a weight of " << connection.weight << std::endl;
                k++;
            }
            os << std::endl;
            j++;
        }
        os << std::endl;
        i++;
    }
    os << "\t|--------------------------------|" << std::endl;
    os << "|----------------------------------------|" << std::endl;
    return os;
}

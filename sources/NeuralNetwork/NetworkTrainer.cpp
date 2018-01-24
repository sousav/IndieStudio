//
// TrainingData.cpp for  in /Users/vicostudio/Documents/Shared Folder/Work/NeuralNetwork/CPP/BasicNeural/sources/
//
// Made by Sousa Victor
// Login   <sousa_v@epitech.eu>
//
// Started on  Sun Apr 23 19:03:38 2017 Sousa Victor
// Last update Sun Jun  4 18:49:17 2017 Sousa Victor
//

#include "NetworkTrainer.hpp"

Neural::NetworkTrainer::NetworkTrainer(const std::string filename) {
    this->_debug = false;
    std::ifstream file;
    file.open(filename.c_str());
    if (file) {
        this->_topology = readTopology(file);
        while (!file.eof()) {
            Neural::INetworkTrainer::TrainingData data;
            data.input = readNextInputs(file);
            if (data.input.size() == 0)
                break;
            if (file.eof())
                throw Neural::InvalidTrainingFile("You training file is giving an input sample without specifying an output corresponding");
            data.output = readTargetOutputs(file);
            if (data.output.size() == 0)
                throw Neural::InvalidTrainingFile("You training file is giving an input sample without specifying an output corresponding");
            this->_trainingData.push_back(data);
        }
        file.close();
    } else {
        throw Neural::InvalidTrainingFile("Your training file " + filename + " could not be found");
    }
}

Neural::NetworkTrainer::~NetworkTrainer() {

}

Neural::NetworkTrainer::NetworkTrainer(const NetworkTrainer &trainer) {
    this->_topology = trainer._topology;
    this->_trainingData = trainer._trainingData;
}

Neural::NetworkTrainer &Neural::NetworkTrainer::operator =(const NetworkTrainer &trainer) {
    this->_topology = trainer._topology;
    this->_trainingData = trainer._trainingData;
    return *this;
}


std::vector<unsigned> const &Neural::NetworkTrainer::getTopology() const {
    return this->_topology;
}

std::vector<Neural::INetworkTrainer::TrainingData> const &Neural::NetworkTrainer::getTrainingData() const {
    return this->_trainingData;
}

void Neural::NetworkTrainer::setDebugFLag(bool mode) {
    this->_debug = mode;
}

bool Neural::NetworkTrainer::getDebugFLag() const {
    return this->_debug;
}


std::vector<unsigned> Neural::NetworkTrainer::readTopology(std::ifstream &file) const {
    std::vector<unsigned> topology;
    std::string line;
    std::string label;

    getline(file, line);
    std::stringstream ss(line);
    ss >> label;
    if (file.eof() || label.compare("topology:") != 0) {
        throw Neural::InvalidTrainingFile("You training file does not contain a topology brief");
    }

    while (!ss.eof()) {
        unsigned n;
        ss >> n;
        topology.push_back(n);
    }
    return topology;
}

std::vector<double> Neural::NetworkTrainer::readNextInputs(std::ifstream &file) const {
    std::vector<double> inputVals;

    std::string line;
    getline(file, line);
    std::stringstream ss(line);

    std::string label;
    ss>> label;
    if (label.compare("in:") == 0) {
        double oneValue;
        while (ss >> oneValue) {
            inputVals.push_back(oneValue);
        }
    }

    return inputVals;
}

std::vector<double> Neural::NetworkTrainer::readTargetOutputs(std::ifstream &file) const {
    std::vector<double> targetOutputVals;

    std::string line;
    getline(file, line);
    std::stringstream ss(line);

    std::string label;
    ss>> label;
    if (label.compare("out:") == 0) {
        double oneValue;
        while (ss >> oneValue) {
            targetOutputVals.push_back(oneValue);
        }
    }

    return targetOutputVals;
}

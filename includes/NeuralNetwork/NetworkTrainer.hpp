//
// TrainingData.hpp for  in /Users/vicostudio/Documents/Shared Folder/Work/NeuralNetwork/CPP/BasicNeural/includes/
//
// Made by Sousa Victor
// Login   <sousa_v@epitech.eu>
//
// Started on  Sun Apr 23 18:58:05 2017 Sousa Victor
// Last update Mon May  1 23:27:37 2017 Sousa Victor
//

#ifndef TRAININGDATA_HPP_
#define TRAININGDATA_HPP_

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "NetworkException.hpp"

namespace Neural {

class INetworkTrainer {

public: struct TrainingData {
        std::vector<double> input;
        std::vector<double> output;
    };

public:
    ~INetworkTrainer() {};

    virtual std::vector<unsigned> const &getTopology() const = 0;
    virtual std::vector<Neural::INetworkTrainer::TrainingData> const &getTrainingData() const = 0;
    virtual void setDebugFLag(bool mode) = 0;
    virtual bool getDebugFLag() const = 0;

};

class NetworkTrainer : public INetworkTrainer {

public:
    NetworkTrainer(const std::string filename);
    ~NetworkTrainer();
    NetworkTrainer(const NetworkTrainer &trainer);
    NetworkTrainer &operator =(const NetworkTrainer &trainer);

    std::vector<unsigned> const &getTopology() const;
    std::vector<Neural::INetworkTrainer::TrainingData> const &getTrainingData() const;
    void setDebugFLag(bool mode);
    bool getDebugFLag() const;

private:
    bool _debug;
    std::vector<unsigned> _topology;
    std::vector<Neural::INetworkTrainer::TrainingData> _trainingData;

    std::vector<unsigned> readTopology(std::ifstream &file) const;
    std::vector<double> readNextInputs(std::ifstream &file) const;
    std::vector<double> readTargetOutputs(std::ifstream &file) const;

};

}

#endif /*TRAININGDATA_HPP_*/

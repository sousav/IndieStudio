//
// Network.hpp for  in /Users/vicostudio/Documents/Shared Folder/Work/NeuralNetwork/CPP/BasicNeural/includes/
//
// Made by Sousa Victor
// Login   <sousa_v@epitech.eu>
//
// Started on  Sun Apr 23 19:19:17 2017 Sousa Victor
// Last update Tue May 30 16:04:15 2017 Sousa Victor
//

#ifndef NETWORK_HPP_
#define NETWORK_HPP_

#include <iostream>
#include <vector>
#include <cmath>

#include "NetworkException.hpp"
#include "NetworkTrainer.hpp"
#include "ANetworkData.hpp"
#include "Layer.hpp"
#include "Genome.hpp"

namespace Neural {

    class INetwork {

    public:
        virtual ~INetwork() {};

        virtual void train(INetworkTrainer const &trainer) = 0;
        virtual void feedForward(const std::vector<double> &inputVals) = 0;
        virtual std::vector<double> const getResults() const = 0;
        virtual void backProp(const std::vector<double> &targetVals) = 0;

        virtual Neural::Genome toGenome() const = 0;
        virtual void fromGenome(Genome const &genome) = 0;

    };

    class Network : public INetwork, public ANetworkData {

    public:
        Network(const std::vector<unsigned> &topology, double recentAverageSmoothingFactor = 100);
        ~Network();
        Network(const Network &network);
        Network &operator =(const Network &network);

        void train(INetworkTrainer const &trainer);
        void feedForward(const std::vector<double> &inputVals);
        std::vector<double> const getResults() const;
        void backProp(const std::vector<double> &targetVals);

        Neural::Genome toGenome() const;
        void fromGenome(Genome const &genome);

    private:
        double _error;
        void showVectorVals(std::string const &label, std::vector<double> const &v) const;

    };

}

std::ostream &operator<<(std::ostream& os, const Neural::Network &network);

#else

namespace Neural {

    class INetwork;
    class Network : public INetwork;

}

#endif /*NETWORK_HPP_*/

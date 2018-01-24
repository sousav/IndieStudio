//
// ANetworkData.cpp for  in /Users/vicostudio/Documents/Shared Folder/Work/NeuralNetwork/CPP_NeuralNetwork/sources/
//
// Made by Sousa Victor
// Login   <sousa_v@epitech.eu>
//
// Started on  Tue May  2 01:03:08 2017 Sousa Victor
// Last update Tue May  2 02:39:13 2017 Sousa Victor
//

#include "ANetworkData.hpp"

Neural::ANetworkData::ANetworkData(const std::vector<unsigned> &topology, double recentAverageSmoothingFactor) {
    this->_recentAverageSmoothingFactor = recentAverageSmoothingFactor;
    unsigned numLayers = topology.size();
    for (unsigned layerNum = 0; layerNum < numLayers; ++layerNum) {
        this->_layers.push_back(Layer());
        unsigned numOutputs = layerNum == topology.size() - 1 ? 0 : topology[layerNum + 1];

        // We have a new layer, now fill it with neurons
        for (unsigned neuronNum = 0; neuronNum <= topology[layerNum]; ++neuronNum) {
            this->_layers.back().push_back(Neuron(numOutputs, neuronNum));
        }
        this->_layers.back().back().setOutputVal(1.0); //bias neuron
    }
}

Neural::ANetworkData::~ANetworkData() {

}

Neural::ANetworkData::ANetworkData(const ANetworkData &data) {
    loadFrom(data);
}

Neural::ANetworkData &Neural::ANetworkData::operator =(const ANetworkData &data) {
    loadFrom(data);
    return *this;
}

void Neural::ANetworkData::loadFrom(const ANetworkData &data) {
    this->_layers = data._layers;
    this->_error = data._error;
    this->_recentAverageError = data._recentAverageError;
    this->_recentAverageSmoothingFactor = data._recentAverageSmoothingFactor;
}

void Neural::ANetworkData::loadFrom(const std::string &filepath) {
    std::ifstream file;
    file.open(filepath.c_str());
    if (file) {
        std::vector<unsigned>topology = readTopology(file);
        std::vector<double>error = readError(file);
        if (error.size() != 3)
            throw Neural::InvalidSavingFile("Your saving file " + filepath + " contains incorrect error information");
        ANetworkData newData(topology, error[2]);
        newData._error = error[0];
        newData._recentAverageError = error[1];
        *this = newData;
        while (!file.eof()) {
            std::vector<unsigned> coord;
            Neural::INeuron::Connection data;
            readNextNeuron(file, coord, data);
            if (coord.size() == 0)
                break;
            this->_layers[coord[0]][coord[1]].setConnection(coord[2], data);
        }

        file.close();
    } else {
        throw Neural::InvalidSavingFile("Your saving file " + filepath + " could not be found");
    }
}

void Neural::ANetworkData::saveTo(const std::string &filepath) const {
    std::ofstream       file;
    file.open(filepath.c_str());
    if (!file)
        throw Neural::InvalidSavingFile("The file in which you are trying to save could not be created..");
    file << "topology:";
    for (auto const layer: this->_layers) {
        file << " " << layer.size() - 1;
    }
    file << std::endl;
    file << "error: " << this->_error << " " << this->_recentAverageError << " " << this->_recentAverageSmoothingFactor << std::endl;

    unsigned i = 0;
    for (auto const layer: this->_layers) {
        if (i == this->_layers.size() - 1)
            break;
        int j = 0;
        for (auto const neuron: layer) {
            std::vector<Neural::INeuron::Connection> connections = neuron.getConnection();
            unsigned k = 0;
            for (auto const &connection: connections) {
                file << i << " " << j << " " << k << " " << connection.weight << " " << connection.deltaWeight << std::endl;
                k++;
            }
            j++;
        }
        i++;
    }
    file.close();
}

std::vector<unsigned> Neural::ANetworkData::readTopology(std::ifstream &file) const {
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

std::vector<double> Neural::ANetworkData::readError(std::ifstream &file) const {
    std::vector<double> error;
    std::string line;
    std::string label;

    getline(file, line);
    std::stringstream ss(line);
    ss >> label;
    if (file.eof() || label.compare("error:") != 0) {
        throw Neural::InvalidTrainingFile("You training file does not contain an error brief");
    }

    while (!ss.eof()) {
        double n;
        ss >> n;
        error.push_back(n);
    }
    return error;
}

void Neural::ANetworkData::readNextNeuron(std::ifstream &file, std::vector<unsigned> &coord, Neural::INeuron::Connection &data) const {
    std::string line;

    getline(file, line);
    if (line.empty())
        return;
    std::stringstream ss(line);

    for (int i = 0; i < 3; i++) {
        if (ss.eof())
            throw Neural::InvalidTrainingFile("You training file does not contain enough informati for one of its neuron");
        unsigned n;
        ss >> n;
        coord.push_back(n);
    }
    if (ss.eof())
        throw Neural::InvalidTrainingFile("You training file does not contain enough informati for one of its neuron");
    ss >> data.weight;
    if (ss.eof())
        throw Neural::InvalidTrainingFile("You training file does not contain enough informati for one of its neuron");
    ss >> data.deltaWeight;
}

double Neural::ANetworkData::getRecentAverageError(void) const {
    return this->_recentAverageError;
}

std::vector<Neural::Layer> const & Neural::ANetworkData::getLayer() const {
    return this->_layers;
}

unsigned Neural::ANetworkData::getLayerCount() const {
    return this->_layers.size();
}

unsigned Neural::ANetworkData::getInputCount() const {
    return (this->_layers.size() == 0 ? 0 : this->_layers.front().size() - 1);
}

unsigned Neural::ANetworkData::getOutputCount() const {
    return (this->_layers.size() == 0 ? 0 : this->_layers.back().size() - 1);
}

unsigned Neural::ANetworkData::getNeuronCount() const {
    unsigned total = 0;

    for (auto const &layer: this->_layers) {
        total += layer.size();
    }
    return total;
}

unsigned Neural::ANetworkData::getConnectionCount() const {
    unsigned total = 0;

    for (auto const &layer: this->_layers) {
        for (auto const &neuron: layer) {
            total += neuron.getConnectionCount();
        }
    }
    return total;
}

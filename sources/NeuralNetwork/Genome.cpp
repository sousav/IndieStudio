//
// Genome.cpp for  in /Users/vicostudio/Documents/Shared/TEK2/CPP/IndieStudio/sources/NeuralNetwork/
//
// Made by Sousa Victor
// Login   <sousa_v@epitech.eu>
//
// Started on  Tue May 30 15:39:39 2017 Sousa Victor
// Last update Thu Jun  1 22:46:26 2017 Sousa Victor
//

#include "Genome.hpp"

Neural::Genome::Genome() {

}

Neural::Genome::Genome(const Neural::Genome &gen) {
    this->_fitness = gen._fitness;
    this->_id = gen._id;
    this->_weights = gen._weights;
}

Neural::Genome::~Genome() {

}

Neural::Genome &Neural::Genome::operator =(const Neural::Genome &gen) {
    this->_fitness = gen._fitness;
    this->_id = gen._id;
    this->_weights = gen._weights;
    return *this;
}

float Neural::Genome::getFitness() const {
    return this->_fitness;
}

void Neural::Genome::setFitness(float fitness) {
    this->_fitness = fitness;
}


int Neural::Genome::getId() const {
    return this->_id;
}

void Neural::Genome::setId(int id) {
    this->_id = id;
}

std::vector<float> const &Neural::Genome::getWeights() const {
    return this->_weights;
}

void Neural::Genome::setWeights(std::vector<float> const &weight) {
    this->_weights = weight;
}

void Neural::Genome::push_back(float f) {
    this->_weights.push_back(f);
}

float& Neural::Genome::operator[](size_t index) {
    return this->_weights[index];
}

const float& Neural::Genome::operator[](size_t index) const {
    return this->_weights[index];
}

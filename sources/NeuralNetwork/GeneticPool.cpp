//
// GeneticPool.cpp for  in /Users/vicostudio/Documents/Shared/TEK2/CPP/IndieStudio/sources/NeuralNetwork/
//
// Made by Sousa Victor
// Login   <sousa_v@epitech.eu>
//
// Started on  Tue May 30 16:57:16 2017 Sousa Victor
// Last update Thu Jun  1 22:45:05 2017 Sousa Victor
//

#include "GeneticPool.hpp"

Neural::GeneticPool::GeneticPool() {
    this->_currentGenome = -1;
    this->_totalPopulation = 0;
    this->_genomeID = 0;
    this->_generation = 1;

    this->_MUTATION_RATE = 0.15f;
    this->_MAX_PERBETUATION = 0.3f;
}

Neural::GeneticPool::~GeneticPool() {

}

Neural::Genome *Neural::GeneticPool::GetNextGenome(){
    this->_currentGenome++;
    if (this->_currentGenome >= this->_population.size())
        return NULL;
    return this->_population[this->_currentGenome];
}

Neural::Genome *Neural::GeneticPool::GetBestGenome() {
    int bestGenome = -1;
    float fitness = 0;
    for (int i = 0; i < this->_population.size(); i++) {
        fitness = this->_population[i]->getFitness();
        bestGenome = i;
    }
    return this->_population[bestGenome];
}

Neural::Genome *Neural::GeneticPool::GetWorstGenome(){
    int worstGenome = -1;
    float fitness = 1000000.0f;
    for (int i = 0; i < this->_population.size(); i++) {
        if(this->_population[i]->getFitness() < fitness){
            fitness = this->_population[i]->getFitness();
            worstGenome = i;
        }
    }
    return this->_population[worstGenome];
}

Neural::Genome *Neural::GeneticPool::GetGenome(int index){
    if(index >= this->_totalPopulation)
        return NULL;
    return this->_population[index];
}

int Neural::GeneticPool::GetCurrentGenomeIndex(){
    return this->_currentGenome;
}

int Neural::GeneticPool::GetCurrentGenomeID(){
    return this->_population[this->_currentGenome]->getId();
}

int Neural::GeneticPool::GetCurrentGeneration(){
    return this->_generation;
}

int Neural::GeneticPool::GetTotalPopulation() {
    return this->_totalPopulation;
}

void Neural::GeneticPool::GetBestCases(int totalGenomes, std::vector<Genome *> &output){
    int genomeCount = 0;
    int runCount = 0;

    while (genomeCount < totalGenomes) {
        if (runCount>10)
            return;

        runCount++;

        //Find the best cases for cross breeding based on fitness score
        float bestFitness = 0;
        int bestIndex = -1;
        for (int i = 0; i < this->_totalPopulation; i++){
            if (this->_population[i]->getFitness() > bestFitness){
                bool isUsed = false;

                for (int j = 0; j < output.size(); j++){
                    if (output[j]->getId() == this->_population[i]->getId()){
                        isUsed = true;
                    }
                }

                if (isUsed == false){
                    bestIndex = i;
                    bestFitness = this->_population[bestIndex]->getFitness();
                }
            }
        }

        if (bestIndex!=-1){
            genomeCount++;
            output.push_back(this->_population[bestIndex]);
        }
    }
}

void Neural::GeneticPool::CrossBreed(const Genome &g1, const Genome &g2, Genome &baby1, Genome &baby2){
    int totalWeights = g1.getWeights().size();

    int crossover =  std::rand() % totalWeights;

    baby1.setId(this->_genomeID);
    for(int i = 0; i < totalWeights; i++){
        baby1.push_back(0.0f);
    }
    this->_genomeID++;

    baby2.setId(this->_genomeID);
    for (int i=0; i<totalWeights; i++) {
        baby2.push_back(0.0f);
    }
    this->_genomeID++;

    //Go from start to crossover point, copying the weights from g1
    for(int i = 0; i < crossover; i++){
        baby1[i] = g1[i];
        baby2[i] = g2[i];
    }

    for(int i = crossover; i < totalWeights; i++){
        baby1[i] = g2[i];
        baby2[i] = g1[i];
    }

}

Neural::Genome *Neural::GeneticPool::CreateNewGenome(int totalWeights){
    Neural::Genome *genome = new Genome();
    genome->setId(this->_genomeID);
    genome->setFitness(0.0f);
    for (int i = 0; i < totalWeights; i++) {
        genome->push_back(0.0f);
    }

    for (int j = 0; j < totalWeights; j++){
        (*genome)[j] = RandomClamped();
    }

    this->_genomeID++;
    return genome;
}

void Neural::GeneticPool::GenerateNewPopulation (int totalPop, int totalWeights){
    this->_generation = 1;
    ClearPopulation();
    this->_currentGenome = -1;
    this->_totalPopulation = totalPop;
    //resize
    if (this->_population.size() < totalPop) {
        for (int i = this->_population.size(); i < totalPop; i++){
            this->_population.push_back(NULL);
        }
    }

    for(int i = 0; i < this->_population.size(); i++){
        Neural::Genome *genome = new Genome();
        genome->setId(this->_genomeID);
        genome->setFitness(0.0f);
        //resize
        for (int k = 0; k < totalWeights; k++){
            genome->push_back(RandomClamped());
        }

        this->_genomeID++;
        this->_population[i] = genome;
    }
}

void Neural::GeneticPool::GenerateNewPopulation (int totalPop, Neural::Genome const &gen){
    this->_generation = 1;
    ClearPopulation();
    this->_currentGenome = -1;
    this->_totalPopulation = totalPop;
    //resize
    if (this->_population.size() < totalPop) {
        for (int i = this->_population.size(); i < totalPop; i++){
            this->_population.push_back(NULL);
        }
    }

    for(int i = 0; i < this->_population.size(); i++){
        Neural::Genome *genome = new Genome(gen);
        genome->setId(this->_genomeID);
        genome->setFitness(0.0f);
        this->_genomeID++;
        this->_population[i] = genome;
    }
}

void Neural::GeneticPool::BreedPopulation() {
    std::vector<Genome*> bestGenomes;
    this->GetBestCases (4, bestGenomes);

    //Breed them with each other twice to form 3*2 + 2*2 + 1*2 = 12 children
    std::vector<Genome*> children;

    //Carry on the best
    Genome *best = new Genome ();
    best->setFitness(0.0f);
    best->setId(bestGenomes[0]->getId());
    best->setWeights(bestGenomes[0]->getWeights());
    //Mutate(best);
    children.push_back(best);

    // Breed with genome 0.
    Genome *baby1;
    Genome *baby2;

    baby1 = new Genome();
    baby2 = new Genome();
    CrossBreed(*bestGenomes[0], *bestGenomes[1], *baby1, *baby2);
    Mutate(*baby1);
    Mutate(*baby2);
    children.push_back(baby1);
    children.push_back(baby2);

    baby1 = new Genome();
    baby2 = new Genome();
    CrossBreed(*bestGenomes[0], *bestGenomes[2], *baby1, *baby2);
    Mutate(*baby1);
    Mutate(*baby2);
    children.push_back(baby1);
    children.push_back(baby2);

    baby1 = new Genome();
    baby2 = new Genome();
    CrossBreed(*bestGenomes[0], *bestGenomes[3], *baby1, *baby2);
    Mutate(*baby1);
    Mutate(*baby2);
    children.push_back(baby1);
    children.push_back(baby2);

    // Breed with genome 1.
    baby1 = new Genome();
    baby2 = new Genome();
    CrossBreed(*bestGenomes[1], *bestGenomes[2], *baby1, *baby2);
    Mutate(*baby1);
    Mutate(*baby2);
    children.push_back(baby1);
    children.push_back(baby2);

    baby1 = new Genome();
    baby2 = new Genome();
    CrossBreed(*bestGenomes[1], *bestGenomes[3], *baby1, *baby2);
    Mutate(*baby1);
    Mutate(*baby2);
    children.push_back(baby1);
    children.push_back(baby2);

    //For the remainding n population, add some random
    int remainingChildren = (this->_totalPopulation - children.size());
    for (int i = 0; i < remainingChildren; i++) {
        children.push_back(this->CreateNewGenome(bestGenomes[0]->getWeights().size()));
    }

    ClearPopulation ();
    this->_population = children;

    this->_currentGenome = 0;
    this->_generation++;
}

void Neural::GeneticPool::ClearPopulation() {
    for (int i = 0; i < this->_population.size(); i++){
        if (this->_population[i] != NULL){
            delete this->_population[i];
            this->_population[i] = NULL;
        }
    }
    this->_population.clear ();
}

void Neural::GeneticPool::Mutate(Genome &genome){
    for (int i = 0; i < genome.getWeights().size(); i++) {
        if (RandomClamped() < this->_MUTATION_RATE){
            genome[i] += (RandomClamped() * this->_MAX_PERBETUATION);
        }
    }
}

void Neural::GeneticPool::SetGenomeFitness(float fitness, int index){
    if (index >= this->_population.size()) {
        return;
    } else {
        this->_population[index]->setFitness(fitness);
    }
}

float Neural::GeneticPool::RandomClamped() const {
    return (static_cast <float> (std::rand()) / static_cast <float> (RAND_MAX)) - (static_cast <float> (std::rand()) / static_cast <float> (RAND_MAX));
}

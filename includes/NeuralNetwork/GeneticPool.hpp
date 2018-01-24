//
// GeneticPool.hpp for  in /Users/vicostudio/Documents/Shared/TEK2/CPP/IndieStudio/includes/NeuralNetwork/
//
// Made by Sousa Victor
// Login   <sousa_v@epitech.eu>
//
// Started on  Tue May 30 16:54:47 2017 Sousa Victor
// Last update Thu Jun  1 22:43:26 2017 Sousa Victor
//

#ifndef GENETICPOOL_HPP_
#define GENETICPOOL_HPP_

#include <iostream>
#include "Genome.hpp"

namespace Neural {

    class GeneticPool {

    public:
        GeneticPool();
        ~GeneticPool();

        Genome *GetNextGenome();
        Genome *GetBestGenome();
        Genome *GetWorstGenome();
        Genome *GetGenome(int index);

        int GetCurrentGenomeIndex();
        int GetCurrentGenomeID();
        int GetCurrentGeneration();
        int GetTotalPopulation();

        void GetBestCases(int totalGenomes, std::vector<Genome *> &output);
        void CrossBreed(const Genome &g1, const Genome &g2, Genome &baby1, Genome &baby2);
        Neural::Genome *CreateNewGenome(int totalWeights);
        void GenerateNewPopulation (int totalPop, int totalWeights);
        void GenerateNewPopulation (int totalPop, Neural::Genome const &genome);
        void BreedPopulation();
        void ClearPopulation();
        void Mutate(Genome &genome);
        void SetGenomeFitness(float fitness, int index);

    private:
        int _currentGenome;
        int _totalPopulation;
        int _genomeID;
        int _generation;
        int _totalGenomeWeights;

        float _MUTATION_RATE;
        float _MAX_PERBETUATION;

        std::vector<Genome*> _population;
        std::vector<int> _crossoverSplits;

        float RandomClamped() const;

    };

}

#endif /*GENETICPOOL_HPP_*/

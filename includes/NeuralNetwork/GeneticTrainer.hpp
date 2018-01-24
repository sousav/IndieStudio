//
// GeneticTrainer.hpp for  in /Users/vicostudio/Documents/Shared/TEK2/CPP/IndieStudio/includes/NeuralNetwork/
//
// Made by Sousa Victor
// Login   <sousa_v@epitech.eu>
//
// Started on  Thu Jun  1 04:23:48 2017 Sousa Victor
// Last update Sat Jun  3 21:44:54 2017 Sousa Victor
//

#ifndef GENETICTRAINER_HPP_
#define GENETICTRAINER_HPP_

#include "LearningCar.hpp"
#include "GeneticPool.hpp"

namespace indie {

    class GeneticTrainer : public IGameObject {

    public:
        GeneticTrainer(irr::scene::ISceneManager *sceneManager, irr::gui::IGUIEnvironment* guiManager, EventReceiver *eventReceiver, physics::CBulletPhysics *bulletPhysicsSystem);
        ~GeneticTrainer();

        virtual void OnFrame();

        Car *getCar() const;

    private:
        irr::scene::ISceneManager *_smgr;
        irr::gui::IGUIEnvironment* _gui;
        EventReceiver *_eventReceiver;
        physics::CBulletPhysics *_bulletPhysicsSystem;

        LearningCar *_aiCar;
        Circuit _circuit;

        Neural::GeneticPool _genPool;
        float _currentAgentFitness;
        float _bestFitness;

        void NextTestSubject();
        void EvolveGenomes();

        irr::gui::IGUIStaticText *_infoFit;
        irr::gui::IGUIStaticText *_infoBestFit;
        irr::gui::IGUIStaticText *_infoGenome;
        irr::gui::IGUIStaticText *_infoGeneration;

    };

}

#endif /*GENETICTRAINER_HPP_*/

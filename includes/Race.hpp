/*
** Race.hpp for IndieStudio in /Users/Vacca_J/Epitech/Tek2/Projet/IndieStudio/includes
**
** Made by Vacca_J
** Login   <Vacca_J@epitech.net>
**
** Started on  Thu Jun 01 01:30:32 2017 Vacca_J
** Last update Thu Jun 15 01:15:18 2017 Lucas Gambini
*/

#ifndef RACE_HPP_
#define RACE_HPP_

#include <random>
#include "AGameObject.hpp"
#include "GameCheckpoint.hpp"
#include "Circuit.hpp"
#include "Car.hpp"
#include "AICar.hpp"

namespace indie {

    class Race : public AGameObject, public EventReceiver {

    public:
        Race(irr::scene::ISceneManager *sceneManager, irr::gui::IGUIEnvironment* guiManager, EventReceiver *eventReceiver, physics::CBulletPhysics *bulletPhysicsSystem);
        ~Race();

        void OnFrame();

        void InitCircuit();
        void setPlayer(Car *player);
        void push_ennemy(Car *ennemy);
        void addAICar(std::string const &short_id);
        int getCurrentPlayerAmount() const;
        void FreezePlayers();
        void UnFreezePlayers();

        void OnEnterInCourseChPt(GameCheckpoint const &ch);

    private:
        int _currentPlayerAmount;
        Circuit _circuit;

        Car *_player;
        carWatcher _carWatcher;
        unsigned _cCheck;
        int _n1Check;
        int _n2Check;
        int _n3Check;

        std::vector<Car *>_ennemies;
        std::vector<AICar *>_aiCars;

        irr::gui::IGUIEnvironment* _gui;
        EventReceiver *_eventReceiver;
        physics::CBulletPhysics *_bulletPhysSys;

    };

}

#endif /* !RACE_HPP_ */

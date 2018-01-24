//
// NetworkCar.hpp for  in /Users/vicostudio/Documents/Shared/TEK2/CPP/IndieStudio/includes/CarSystem/
//
// Made by Sousa Victor
// Login   <sousa_v@epitech.eu>
//
// Started on  Sat Jun 10 16:38:37 2017 Sousa Victor
// Last update Sat Jun 10 16:41:46 2017 Sousa Victor
//

#ifndef NETWORKCAR_HPP_
#define NETWORKCAR_HPP_

#include "Car.hpp"
#include "Utils.hpp"
#include <irrlicht.h>

namespace indie {

    class NetworkCar : public Car {

    public:
        NetworkCar(irr::scene::ISceneManager *sceneManager, irr::gui::IGUIEnvironment* guiManager, EventReceiver *eventReceiver, physics::CBulletPhysics *bulletPhysicsSystem, Circuit const &circuit, int car_no = 0);
        ~NetworkCar();

        virtual void OnFrame();

        void setShortId(std::string const &id);

    private:
        irr::scene::IBillboardTextSceneNode *_name;

    };

}

#endif /*NETWORKCAR_HPP_*/

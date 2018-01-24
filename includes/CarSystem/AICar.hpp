//
// AICar.hpp for  in /Users/vicostudio/Documents/Shared/TEK2/CPP/IndieStudio/includes/CarSystem/
//
// Made by Sousa Victor
// Login   <sousa_v@epitech.eu>
//
// Started on  Wed May 24 20:30:32 2017 Sousa Victor
// Last update Tue Jun  6 17:27:50 2017 Sousa Victor
//

#ifndef AICAR_HPP_
#define AICAR_HPP_

#include <unordered_map>
#include <fstream>
#include <iostream>
#include <iomanip>
#include "IndieStudioConfig.h"
#include "carWatcher.hpp"
#include "EventReceiver.hpp"
#include "Network.hpp"
#include "Car.hpp"
#include "Utils.hpp"

namespace indie {

    class AICar : public Car, public EventReceiver{

    public:
        AICar(irr::scene::ISceneManager *sceneManager, irr::gui::IGUIEnvironment* guiManager, EventReceiver *eventReceiver, physics::CBulletPhysics *bulletPhysicsSystem, Circuit const &circuit, int car_no = 0);
        ~AICar();

        virtual void OnFrame();

        void OnEnterInCourseChPt(GameCheckpoint const &ch);

        void setShouldNetwork(bool b);

    protected:
        Neural::Network _steerBrain;
        Neural::Network _engineBrain;
        carWatcher _carWatcher;

        unsigned _cCheck;
        int _n1Check;
        int _n2Check;
        int _n3Check;

        virtual void KeyboardEvent();
        virtual void updateCamera();
        virtual void SendInfo();

        bool _shouldNetwork;

    };

}

#endif /*AICAR_HPP_*/

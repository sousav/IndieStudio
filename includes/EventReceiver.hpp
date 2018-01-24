//
// EventReceiver.hpp for  in /Users/vicostudio/Documents/Shared/TEK2/CPP/cpp_indie_studio/includes/
//
// Made by Sousa Victor
// Login   <sousa_v@epitech.eu>
//
// Started on  Mon May  8 19:54:43 2017 Sousa Victor
// Last update Sat Jun  3 21:13:04 2017 Sousa Victor
//

#ifndef EVENTRECEIVER_HPP_
#define EVENTRECEIVER_HPP_

#include <irrlicht.h>
#include "GameCheckpoint.hpp"

namespace indie {

    class EventReceiver : public irr::IEventReceiver {

    public:
        EventReceiver();
        EventReceiver(const EventReceiver &receiver);
        EventReceiver &operator=(const EventReceiver &receiver);
        ~EventReceiver();

        virtual bool OnEvent(const irr::SEvent& event);
        virtual bool IsKeyDown(irr::EKEY_CODE keyCode) const;

        virtual void OnEnterKey(irr::EKEY_CODE keyCode) { }
        virtual void OnReleaseKey(irr::EKEY_CODE keyCode) { }

        virtual void OnEnterGarage(void) { }
        virtual void OnLeavingGarage(void) { }

        virtual void OnOpenningMenu() { }
        virtual void OnLeavingMenu() { }

        virtual void OnEnterCourse(GameCheckpoint const &ch) { }
        virtual void OnLeavingCourse() { }

        virtual void OnEnterMoney() { }

        virtual void OnEnterInCourseChPt(GameCheckpoint const &ch) { }

        virtual void OnEnterOnline() { }
        virtual void OnLeavingOnline() { }

        virtual void OnEnterConcess() {};
        virtual void OnLeavingConcess() {};

    private:
        bool _keyIsDown[irr::KEY_KEY_CODES_COUNT];

    };

}

#else

namespace indie {
    class EventReceiver;
}

#endif /*EVENTRECEIVER_HPP_*/

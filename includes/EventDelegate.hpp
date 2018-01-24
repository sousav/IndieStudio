//
// EventDelegate.hpp for  in /Users/vicostudio/Documents/Shared/TEK2/CPP/cpp_indie_studio_/includes/
//
// Made by Sousa Victor
// Login   <sousa_v@epitech.eu>
//
// Started on  Fri May 12 00:15:18 2017 Sousa Victor
// Last update Fri May 12 00:18:56 2017 Sousa Victor
//

#ifndef EVENTDELEGATE_HPP_
#define EVENTDELEGATE_HPP_

namespace indie {

    class EventDelegate {

    public:
        virtual void OnEscape() {};
        virtual void OnEnter() {};
        virtual void OnSpace() {};

        virtual void OnUp() {};
        virtual void OnDown() {};
        virtual void OnLeft() {};
        virtual void OnRight() {};

    };

}

#endif /*EVENTDELEGATE_HPP_*/

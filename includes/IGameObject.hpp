//
// IGameObject.hpp for  in /Users/vicostudio/Documents/Shared/TEK2/CPP/cpp_indie_studio/includes/
//
// Made by Sousa Victor
// Login   <sousa_v@epitech.eu>
//
// Started on  Sun May  7 20:16:03 2017 Sousa Victor
// Last update Thu May 18 19:20:18 2017 Sousa Victor
//

#ifndef IGAMEOBJECT_HPP_
#define IGAMEOBJECT_HPP_

#include <irrlicht.h>

#include "IGame.hpp"

namespace indie {

    class IGameObject {

    public:
        virtual ~IGameObject() {};

        virtual void OnFrame() = 0;

    };

}

#else

namespace indie {
    class IGameObject;
}

#endif /*IGAMEOBJECT_HPP_*/

//
// DeltaTime.hpp for  in /Users/vicostudio/Documents/Shared/TEK2/CPP/cpp_indie_studio_/includes/
//
// Made by Sousa Victor
// Login   <sousa_v@epitech.eu>
//
// Started on  Sun May 14 23:43:34 2017 Sousa Victor
// Last update Sun May 14 23:47:45 2017 Sousa Victor
//

#ifndef DELTATIMER_HPP_
#define DELTATIMER_HPP_

#include <irrlicht.h>

namespace indie {

    class DeltaTimer {

    public:
        virtual ~DeltaTimer() {};

        static irr::f32 DeltaTime;

    };

}

#endif /*DELTATIMER_HPP_*/

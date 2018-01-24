//
// BasicCamera.hpp for  in /Users/vicostudio/Documents/Shared/TEK2/CPP/cpp_indie_studio_/includes/
//
// Made by Sousa Victor
// Login   <sousa_v@epitech.eu>
//
// Started on  Thu May 11 23:43:27 2017 Sousa Victor
// Last update Sat Jun 17 22:57:05 2017 Sousa Victor
//

#ifndef BASICCAMERA_HPP_
#define BASICCAMERA_HPP_

#include "AGameCamera.hpp"

namespace indie {

    class BasicCamera: public AGameCamera {

    public:
        BasicCamera(irr::scene::ISceneManager *sceneManager, const irr::core::rect<irr::s32>& viewPort, irr::scene::ISceneNode* parent = 0, irr::s32 id = -1,
                    irr::core::vector3df const &position = irr::core::vector3df(10, 35, 10), irr::core::vector3df const &lookat = irr::core::vector3df(0, 0, 0));
        BasicCamera(const BasicCamera &cam);
        BasicCamera &operator=(const BasicCamera &cam);
        ~BasicCamera();

        virtual void OnFrame();

    };

}

#endif /*BASICCAMERA_HPP_*/

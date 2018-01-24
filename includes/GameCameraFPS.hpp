//
// GameCameraFPS.hpp for  in /Users/vicostudio/Documents/Shared/TEK2/CPP/cpp_indie_studio/includes/
//
// Made by Sousa Victor
// Login   <sousa_v@epitech.eu>
//
// Started on  Mon May  8 05:44:38 2017 Sousa Victor
// Last update Sat Jun 17 22:57:30 2017 Sousa Victor
//

#ifndef GAMECAMERAFPS_HPP
#define GAMECAMERAFPS_HPP

#include "AGameCamera.hpp"

namespace indie {

    class GameCameraFPS: public AGameCamera {

    public:
        GameCameraFPS(irr::scene::ISceneManager *sceneManager, const irr::core::rect<irr::s32>& viewPort, irr::scene::ISceneNode* parent = 0,
			          irr::f32 rotateSpeed = 100.0f, irr::f32 moveSpeed = .5f, irr::s32 id = -1, irr::SKeyMap* keyMapArray=0, irr::s32 keyMapSize=0,
                      bool noVerticalMovement=false, irr::f32 jumpSpeed = 0.f, bool invertMouseY=false, bool makeActive=true);
        GameCameraFPS(const GameCameraFPS &cam);
        GameCameraFPS &operator=(const GameCameraFPS &cam);
        ~GameCameraFPS();

        void OnFrame();

    };

}

#else

namespace indie {
    class GameCameraFPS: public AGameCamera;
}

#endif /*GAMECAMERAFPS_HPP*/

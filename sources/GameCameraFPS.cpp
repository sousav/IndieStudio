//
// GameCameraFPS.cpp for  in /Users/vicostudio/Documents/Shared/TEK2/CPP/cpp_indie_studio/sources/
//
// Made by Sousa Victor
// Login   <sousa_v@epitech.eu>
//
// Started on  Mon May  8 05:46:16 2017 Sousa Victor
// Last update Sat Jun 17 22:57:42 2017 Sousa Victor
//

#include "GameCameraFPS.hpp"

using namespace indie;

GameCameraFPS::GameCameraFPS(irr::scene::ISceneManager *sceneManager, const irr::core::rect<irr::s32>& viewPort, irr::scene::ISceneNode* parent,
              irr::f32 rotateSpeed, irr::f32 moveSpeed, irr::s32 id, irr::SKeyMap* keyMapArray, irr::s32 keyMapSize,
              bool noVerticalMovement, irr::f32 jumpSpeed, bool invertMouseY, bool makeActive)
              : AGameCamera(sceneManager, parent, id, viewPort) {

    irr::SKeyMap keyMap[5];                    // re-assigne les commandes
    keyMap[0].Action = irr::EKA_MOVE_FORWARD;  // avancer
    keyMap[0].KeyCode = irr::KEY_KEY_W;        // w
    keyMap[1].Action = irr::EKA_MOVE_BACKWARD; // reculer
    keyMap[1].KeyCode = irr::KEY_KEY_S;        // s
    keyMap[2].Action = irr::EKA_STRAFE_LEFT;   // a gauche
    keyMap[2].KeyCode = irr::KEY_KEY_A;        // a
    keyMap[3].Action = irr::EKA_STRAFE_RIGHT;  // a droite
    keyMap[3].KeyCode = irr::KEY_KEY_D;        // d
    keyMap[4].Action = irr::EKA_JUMP_UP;       // saut
    keyMap[4].KeyCode = irr::KEY_SPACE;        // barre espace

    this->_camera = this->_smgr->addCameraSceneNodeFPS(parent, rotateSpeed, moveSpeed, id,
                                                                          (keyMapArray == NULL ? keyMap : keyMapArray), (keyMapArray == NULL ? 5 : keyMapSize),
                                                                          noVerticalMovement, jumpSpeed, invertMouseY, makeActive);

    this->_camera->setPosition(irr::core::vector3df(184, 125, 67));

}

GameCameraFPS::GameCameraFPS(const GameCameraFPS &cam) : AGameCamera(cam) {

}

GameCameraFPS &GameCameraFPS::operator=(const GameCameraFPS &cam) {
    AGameCamera::operator=(cam);
    return *this;
}

GameCameraFPS::~GameCameraFPS() {

}

void GameCameraFPS::OnFrame() {
}

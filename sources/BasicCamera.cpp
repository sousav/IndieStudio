//
// BasicCamera.cpp for  in /Users/vicostudio/Documents/Shared/TEK2/CPP/cpp_indie_studio_/sources/
//
// Made by Sousa Victor
// Login   <sousa_v@epitech.eu>
//
// Started on  Thu May 11 23:46:09 2017 Sousa Victor
// Last update Sat Jun 17 22:57:01 2017 Sousa Victor
//

#include "BasicCamera.hpp"

using namespace indie;

BasicCamera::BasicCamera(irr::scene::ISceneManager *sceneManager, const irr::core::rect<irr::s32>& viewPort, irr::scene::ISceneNode* parent, irr::s32 id,
                         irr::core::vector3df const &position, irr::core::vector3df const &lookat)
                         : AGameCamera(sceneManager, parent, id, viewPort) {

    this->_camera = this->_smgr->addCameraSceneNode (parent, position, lookat, id);

}

BasicCamera::BasicCamera(const BasicCamera &cam): AGameCamera(cam) {

}

BasicCamera &BasicCamera::operator=(const BasicCamera &cam) {
    AGameCamera::operator=(cam);
    return *this;
}

BasicCamera::~BasicCamera() {

}


void BasicCamera::OnFrame() {

}

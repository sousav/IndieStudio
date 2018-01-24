//
// AGameCamera.cpp for  in /Users/vicostudio/Documents/Shared/TEK2/CPP/cpp_indie_studio/sources/
//
// Made by Sousa Victor
// Login   <sousa_v@epitech.eu>
//
// Started on  Mon May  8 05:35:32 2017 Sousa Victor
// Last update Sat Jun 17 22:55:17 2017 Sousa Victor
//

#include "AGameCamera.hpp"

using namespace indie;

AGameCamera::AGameCamera(irr::scene::ISceneManager *sceneManager, irr::scene::ISceneNode* parent, irr::s32 id,
            const irr::core::rect<irr::s32>& viewPort,
            const irr::core::vector3df& position, const irr::core::vector3df& rotation, const irr::core::vector3df& scale)
            : AGameObject(sceneManager), ICameraSceneNode(parent, sceneManager, id, position, rotation, scale) {

    this->_viewport = viewPort;

}

AGameCamera::AGameCamera(const AGameCamera &cam) : AGameObject(cam), ICameraSceneNode(cam._camera->getParent(), cam._camera->getSceneManager(), cam._camera->getID(), cam._camera->getPosition(), cam._camera->getRotation(), cam._camera->getScale()) {

}

AGameCamera &AGameCamera::operator=(const AGameCamera &cam) {
    AGameObject::operator=(cam);
    return *this;
}

AGameCamera::~AGameCamera() {

}

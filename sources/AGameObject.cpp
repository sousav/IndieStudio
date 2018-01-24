//
// IGameObject.cpp for  in /Users/vicostudio/Documents/Shared/TEK2/CPP/cpp_indie_studio/sources/
//
// Made by Sousa Victor
// Login   <sousa_v@epitech.eu>
//
// Started on  Sun May  7 20:11:06 2017 Sousa Victor
// Last update Sun May  7 20:16:42 2017 Sousa Victor
//

#include "AGameObject.hpp"

using namespace indie;

AGameObject::AGameObject() {
    
}

AGameObject::AGameObject(irr::scene::ISceneManager *sceneManager) {
    this->_smgr = sceneManager;
}

AGameObject::AGameObject(const AGameObject &obj) {
    this->_smgr = obj._smgr;
}

AGameObject &AGameObject::operator=(const AGameObject &obj) {
    this->_smgr = obj._smgr;
    return *this;
}

AGameObject::~AGameObject() {

}

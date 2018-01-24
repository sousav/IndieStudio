//
// APhysicObject.cpp for  in /Users/vicostudio/Documents/Shared/TEK2/CPP/cpp_indie_studio_github/sources/
//
// Made by Sousa Victor
// Login   <sousa_v@epitech.eu>
//
// Started on  Thu May 11 00:54:49 2017 Sousa Victor
// Last update Fri May 19 21:27:11 2017 Sousa Victor
//

#include "APhysicObject.hpp"

using namespace indie;

APhysicObject::APhysicObject() {

}

APhysicObject::APhysicObject(irr::scene::ISceneManager *sceneManager, std::string const &path,
         irr::scene::ISceneNode *parent, irr::s32 id, irr::f32 mass,
         const irr::core::vector3df &position, const irr::core::vector3df &rotation, const irr::core::vector3df &scale)
         : AModelObject(sceneManager, path, parent, id, position, rotation, scale) {

}

APhysicObject::APhysicObject(const APhysicObject &obj) : AModelObject(obj._smgr, obj._path, obj.getParent(), obj.getID(), obj.getPosition(), obj.getRotation(), obj.getScale()){

}

APhysicObject &APhysicObject::operator=(const APhysicObject &obj) {
    AModelObject::operator=(obj);
    return *this;
}

APhysicObject::~APhysicObject() {

}

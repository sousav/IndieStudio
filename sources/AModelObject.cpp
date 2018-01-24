//
// AModelObject.cpp for  in /Users/vicostudio/Documents/Shared/TEK2/CPP/cpp_indie_studio_github/sources/
//
// Made by Sousa Victor
// Login   <sousa_v@epitech.eu>
//
// Started on  Thu May 11 00:37:40 2017 Sousa Victor
// Last update Thu May 18 16:57:12 2017 Sousa Victor
//

#include "AModelObject.hpp"

using namespace indie;

AModelObject::AModelObject() {

}

AModelObject::AModelObject(irr::scene::ISceneManager *sceneManager, std::string const &path, irr::scene::ISceneNode *parent, irr::s32 id,
         const irr::core::vector3df &position, const irr::core::vector3df &rotation, const irr::core::vector3df &scale)
         : AGameObject(sceneManager) {

    this->_path = path;
    this->_mesh = this->_smgr->getMesh(path.c_str());
    this->_node = this->_smgr->addOctreeSceneNode(this->_mesh, parent, id, 1024);
    this->_node->setPosition(position);
    this->_node->setRotation(rotation);
    this->_node->setScale(scale);
    this->_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    this->_node->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
    this->_node->addShadowVolumeSceneNode();

}

 AModelObject::AModelObject(const AModelObject &obj): AGameObject(obj) {
     this->_mesh = obj._mesh;
 }

 AModelObject &AModelObject::operator=(const AModelObject &obj) {
     AGameObject::operator=(obj);
     return *this;
 }

 AModelObject::~AModelObject() {

 }

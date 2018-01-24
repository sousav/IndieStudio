/*
** Checkpoint.cpp for Shared in /Users/gmblucas/Desktop/Shared/IndieStudio/sources
**
** Made by Lucas Gambini
** Login   <gmblucas@epitech.net>
**
** Started on  Tue May 16 12:44:22 2017 Lucas Gambini
** Last update Wed Jun 14 19:41:44 2017 Lucas Gambini
*/

#include "GameCheckpoint.hpp"

using namespace indie;

GameCheckpoint::GameCheckpoint(irr::scene::ISceneManager *sceneManager, irr::f32 size, irr::f32 mass, irr::scene::ISceneNode *parent, irr::s32 id,
                   Type type, const irr::f32 radius, const irr::core::vector3df &position, const irr::core::vector3df &rotation, const irr::core::vector3df &scale)
                   : AGameObject (sceneManager), IMeshSceneNode(parent, sceneManager, id, position, rotation, scale) {

    this->_type = type;
    this->_isBusy = false;
    this->_pos = position;
    this->_cylindre = NULL;
    this->_radius = radius;
    this->_scale = scale;
    this->_rotation = rotation;
    this->_id = id;

    reCreate();
}

// GameCheckpoint &GameCheckpoint::operator=(const GameCheckpoint &obj) {
//     AGameObject::operator=(obj);
//     this->_cylindre = obj._cylindre;
//     this->_type = obj._type;
//     this->_isBusy = obj._isBusy;
//     return *this;
// }


GameCheckpoint::~GameCheckpoint() {

}

void GameCheckpoint::reCreate() {
    if (this->_type == GARAGE)
        this->_color = irr::video::SColor(150, 255, 0, 0);
    else if (this->_type == COURSE)
        this->_color = irr::video::SColor(150, 0, 0, 255);
    else if (this->_type == CONCESSIONNAIRE)
        this->_color = irr::video::SColor(150, 255, 255, 0);
    else if (this->_type == MONEY)
        this->_color = irr::video::SColor(150, 0, 255, 0);
    else if (this->_type == IN_COURSE)
        this->_color = irr::video::SColor(150, 0, 255, 255);
    else
        this->_color = irr::video::SColor(150, 100, 100, 100);
    irr::scene::IMesh *_mesh = this->_smgr->getGeometryCreator()->createCylinderMesh(this->_radius, 5000, 50, this->_color, true, 0.f);
    _mesh->setMaterialFlag(irr::video::EMF_WIREFRAME, 10);
    this->_cylindre = this->_smgr->addMeshSceneNode(_mesh, 0, this->_id, this->_pos, this->_rotation, this->_scale);
    this->_cylindre->getMaterial(0).AmbientColor.set(255,this->_color.getRed(),this->_color.getGreen(),this->_color.getBlue());
    this->_cylindre->getMaterial(0).DiffuseColor.set(255,this->_color.getRed(),this->_color.getGreen(),this->_color.getBlue());
    this->_cylindre->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
}

void GameCheckpoint::OnFrame() {

}

GameCheckpoint::Type GameCheckpoint::getChType() const {
    return _type;
}

bool GameCheckpoint::isBusy() const {
    return this->_isBusy;
}

void GameCheckpoint::setBusy(bool value) {
    this->_isBusy = value;
}

irr::core::vector3df GameCheckpoint::getChPosition() const {
    return this->_pos;
}

//CCubeSceneNode
void GameCheckpoint::render() {
    return this->_cylindre->render();
}

const irr::core::aabbox3d<irr::f32> &GameCheckpoint::getBoundingBox() const {
    return this->_cylindre->getBoundingBox();
}

void GameCheckpoint::setChVisible(bool value) {
    this->_cylindre->setVisible(value);
}

//IMeshSceneNode
void GameCheckpoint::setMesh(irr::scene::IMesh *mesh) {
    this->_cylindre->setMesh(mesh);
}

irr::scene::IMesh *GameCheckpoint::getMesh(void) {
    return this->_cylindre->getMesh();
}

irr::scene::IShadowVolumeSceneNode *GameCheckpoint::addShadowVolumeSceneNode(const irr::scene::IMesh *shadowMesh, irr::s32 id, bool zfailmethod, irr::f32 infinity) {
    return this->_cylindre->addShadowVolumeSceneNode(shadowMesh, id, zfailmethod, infinity);
}

void GameCheckpoint::setReadOnlyMaterials(bool readonly) {
    this->_cylindre->setReadOnlyMaterials(readonly);
}

bool GameCheckpoint::isReadOnlyMaterials() const {
    return this->_cylindre->isReadOnlyMaterials();
}

void GameCheckpoint::setLaserVisible(bool visible) {
    this->_cylindre->setVisible(visible);
}

bool GameCheckpoint::isLaserVisible() const {
    return this->_cylindre->isVisible();
}

float GameCheckpoint::getRadius() const {
    return this->_radius;
}

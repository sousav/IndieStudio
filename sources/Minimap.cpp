//
// Minimap.cpp for  in /Users/ethankerdelhue/Documents/shared/IndieStudio/sources/
//
// Made by Ethan Kerdelhue
// Login   <ethan.kerdelhue@epitech.eu@epitech.eu>
//
// Started on  Sat May 13 22:28:14 2017 Ethan Kerdelhue
// Last update Tue Jun 13 15:00:43 2017 Sousa Victor
//

#include "Minimap.hpp"

using namespace indie;

Minimap::Minimap(irr::scene::ISceneManager *sceneManager, irr::scene::ISceneNode* parent, irr::s32 id, Car *car, carWatcher *carWatcher, irr::video::IVideoDriver* driver, irr::IrrlichtDevice *device, irr::gui::IGUIEnvironment *gui, irr::core::dimension2du const &screenDim)
      : AGameObject(sceneManager) {
      this->_camera = sceneManager->getActiveCamera();
      this->_driver = driver;
      this->_car = car;
      this->_gui = gui;
      this->_carWatcher = carWatcher;
      this->_screenDim = screenDim;

      this->_textureMap[GameCheckpoint::Type::GARAGE] = this->_driver->getTexture("icon-garage.png");
      this->_textureMap[GameCheckpoint::Type::CONCESSIONNAIRE] = this->_driver->getTexture("icon-concess.png");
      this->_textureMap[GameCheckpoint::Type::COURSE] = this->_driver->getTexture("icon-race.png");
      this->_textureMap[GameCheckpoint::Type::IN_COURSE] = this->_driver->getTexture("icon-target.png");
      this->_textureMap[GameCheckpoint::Type::MONEY] = this->_driver->getTexture("icon-money.png");
      this->_textureMap[GameCheckpoint::Type::ONLINE] = this->_driver->getTexture("icon-multi.png");
}

Minimap::~Minimap()
{

}

void Minimap::OnFrame() {
  std::vector<GameCheckpoint> checkpoints = this->_carWatcher->getCheckpoints();
  for (auto img : this->_imgVector) {
    img->remove();
  }
  while (!this->_imgVector.empty()) {
     this->_imgVector.pop_back();
  }
   for (auto const &checkpoint : checkpoints) {
    irr::core::vector3df camDir = (this->_car->getRealRotation().rotationToDirection()).normalize();
    irr::core::vector2df camDir2d(camDir.X, camDir.Z);

    irr::core::vector3df checkDir = (checkpoint.getChPosition() - this->_car->getPosition()).normalize();
    irr::core::vector2df checkDir2d(checkDir.X, checkDir.Z);

    float angle = atan2(camDir2d.X * checkDir2d.Y - camDir2d.Y * checkDir2d.X, camDir2d.X * checkDir2d.X + camDir2d.Y * checkDir2d.Y);

    irr::core::vector2df center(this->_screenDim.Width / 2, this->_screenDim.Height / 2);
    irr::gui::IGUIImage * img = this->_gui->addImage(this->_textureMap[checkpoint.getChType()], irr::core::position2d<int>(center.X - this->_textureMap[checkpoint.getChType()]->getSize().Width / 2 - sin(angle) * 500, center.Y - this->_textureMap[checkpoint.getChType()]->getSize().Height / 2 - cos(angle) * 500));
    this->_imgVector.push_back(img);
    }
}

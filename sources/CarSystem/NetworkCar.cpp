//
// NetworkCar.cpp for  in /Users/vicostudio/Documents/Shared/TEK2/CPP/IndieStudio/sources/CarSystem/
//
// Made by Sousa Victor
// Login   <sousa_v@epitech.eu>
//
// Started on  Sat Jun 10 16:38:11 2017 Sousa Victor
// Last update Fri Jun 16 17:52:08 2017 Sousa Victor
//

#include "NetworkCar.hpp"

using namespace indie;

NetworkCar::NetworkCar(irr::scene::ISceneManager *sceneManager, irr::gui::IGUIEnvironment* guiManager, EventReceiver *eventReceiver, physics::CBulletPhysics *bulletPhysicsSystem, Circuit const &circuit, int car_no):
    Car(sceneManager, guiManager, eventReceiver, bulletPhysicsSystem, circuit, car_no, irr::core::vector3df(2, 36.5, 0), true) {
        this->_name = sceneManager->addBillboardTextSceneNode(guiManager->getSkin()->getFont(), L"", 0, irr::core::dimension2d<irr::f32>(2, 1));
}

NetworkCar::~NetworkCar() {
    this->_name->remove();
}

void NetworkCar::OnFrame() {
    this->_carLoader.Update(drive_tipe, false);
    auto pos = this->getPosition();
    pos.Y += 3;
    this->_name->setPosition(pos);
}

void NetworkCar::setShortId(std::string const &id) {
    irr::core::stringw str(L"");
    str += id.c_str();
    str.replace(' ', ' ');
    this->_name->setText(str.c_str());
}

/*
** Garage.cpp for Shared in /Users/gmblucas/Desktop/Shared/IndieStudio/sources/GUI
**
** Made by Lucas Gambini
** Login   <gmblucas@epitech.net>
**
** Started on  Thu May 18 01:01:26 2017 Lucas Gambini
** Last update Sat May 20 01:41:04 2017 Lucas Gambini
*/

#include "Garage.hpp"

using namespace indie;

Garage::Garage(irr::gui::IGUIEnvironment *gui, irr::video::IVideoDriver *driver, irr::core::dimension2du windowSize)
{
    this->_gui = gui;
    this->_driver = driver;
    this->_windowSize = windowSize;
    this->_isVisible = false;
}

Garage::~Garage()
{

}

void Garage::SetupGUI() {
    this->_repair = this->_gui->addButton(irr::core::rect<irr::s32>(this->_windowSize.Width / 2 - 80, this->_windowSize.Height / 2 - 120, this->_windowSize.Width / 2 + 80, this->_windowSize.Height / 2 - 40), 0, REPAIR,
            L"Repair car", L"");
    this->_leave_ = this->_gui->addButton(irr::core::rect<irr::s32>(this->_windowSize.Width / 2 - 80, this->_windowSize.Height / 2 + 40, this->_windowSize.Width / 2 + 80, this->_windowSize.Height / 2 + 120), 0, LEAVE,
            L"Leave", L"");

    this->_title = this->_gui->addStaticText(L"Garage", irr::core::rect<irr::s32>(this->_windowSize.Width / 2 - 140, this->_windowSize.Height / 2 - 180, this->_windowSize.Width / 2 + 140, this->_windowSize.Height / 2 - 120), false, false, 0, -1, false);
    this->_title->setTextAlignment(irr::gui::EGUIA_CENTER, irr::gui::EGUIA_SCALE);

}

void Garage::setVisible(bool visible) {
    this->_isVisible = visible;
}

bool Garage::isVisible(void) const {
    return this->_isVisible;
}

void Garage::OnFrame(void) {
    if (this->_isVisible == true) {
        this->_driver->draw2DRectangle(irr::video::SColor(200,75,75,75), irr::core::rect<irr::s32>(this->_windowSize.Width / 2 - 140, this->_windowSize.Height / 2 - 200, this->_windowSize.Width / 2 + 140, this->_windowSize.Height / 2 + 200));
        this->_title->setVisible(true);
        this->_repair->setVisible(true);
        this->_leave_->setVisible(true);
    }
    else {
        this->_title->setVisible(false);
        this->_repair->setVisible(false);
        this->_leave_->setVisible(false);
    }
}

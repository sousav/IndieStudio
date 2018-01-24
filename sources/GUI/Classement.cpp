/*
** Classement.cpp for IndieStudio
**
** Made by	Full Name
** Login	Full Name
**
** Started on	Mon Jun 05 16:08:24 2017 Full Name
** Last update	Mon Jun 05 18:12:23 2017 Full Name
*/

#include "Classement.hpp"

using namespace indie;

Classement::Classement(irr::gui::IGUIEnvironment *gui, irr::video::IVideoDriver *driver, irr::core::dimension2du windowSize, std::vector<std::string> result)
{
    _gui = gui;
    _driver = driver;
    _windowSize = windowSize;
    _result = result;
}

Classement::~Classement()
{

}

#include "Utils.hpp"
void Classement::SetupGUI()
{
    this->_exit = this->_gui->addButton(irr::core::rect<irr::s32>(this->_windowSize.Width / 2 - 80, this->_windowSize.Height / 2 + 80, this->_windowSize.Width / 2 + 80, this->_windowSize.Height / 2 + 140), NULL, -1,
            L"Exit", L"");
     this->_title = this->_gui->addStaticText(L"Classement final", irr::core::rect<irr::s32>(this->_windowSize.Width / 2 - 140, this->_windowSize.Height / 2 - 180, this->_windowSize.Width / 2 + 140, this->_windowSize.Height / 2 - 140));
     this->_title->setTextAlignment(irr::gui::EGUIA_CENTER, irr::gui::EGUIA_SCALE);

     this->_first = this->_gui->addStaticText(irr::core::stringw(_result[0].c_str()).c_str(), irr::core::rect<irr::s32>(this->_windowSize.Width / 2 - 140, this->_windowSize.Height / 2 - 140, this->_windowSize.Width / 2 + 140, this->_windowSize.Height / 2 - 90));
     this->_first->setTextAlignment(irr::gui::EGUIA_CENTER, irr::gui::EGUIA_SCALE);

     this->_second = this->_gui->addStaticText(irr::core::stringw(_result[1].c_str()).c_str(), irr::core::rect<irr::s32>(this->_windowSize.Width / 2 - 140, this->_windowSize.Height / 2 - 100, this->_windowSize.Width / 2 + 140, this->_windowSize.Height / 2 - 60));
     this->_second->setTextAlignment(irr::gui::EGUIA_CENTER, irr::gui::EGUIA_SCALE);

     this->_third = this->_gui->addStaticText(irr::core::stringw(_result[2].c_str()).c_str(), irr::core::rect<irr::s32>(this->_windowSize.Width / 2 - 140, this->_windowSize.Height / 2 - 60, this->_windowSize.Width / 2 + 140, this->_windowSize.Height / 2 - 30));
     this->_third->setTextAlignment(irr::gui::EGUIA_CENTER, irr::gui::EGUIA_SCALE);

     this->_forth = this->_gui->addStaticText(irr::core::stringw(_result[3].c_str()).c_str(), irr::core::rect<irr::s32>(this->_windowSize.Width / 2 - 140, this->_windowSize.Height / 2 - 10, this->_windowSize.Width / 2 + 140, this->_windowSize.Height / 2 + 10));
     this->_forth->setTextAlignment(irr::gui::EGUIA_CENTER, irr::gui::EGUIA_SCALE);
}

void Classement::OnFrame()
{
    this->_driver->draw2DRectangle(irr::video::SColor(200,75,75,75), irr::core::rect<irr::s32>(this->_windowSize.Width / 2 - 140, this->_windowSize.Height / 2 - 200, this->_windowSize.Width / 2 + 140, this->_windowSize.Height / 2 + 200));
}

void Classement::setVisible(bool visible)
{
    (void)visible;
}

bool Classement::isVisible() const
{
    return true;
}

/*
** Menu.cpp for IndieStudio
**
** Made by	Full Name
** Login	Full Name
**
** Started on	Thu May 18 15:46:39 2017 Full Name
** Last update Sat Jun 17 17:12:10 2017 Lucas Gambini
*/

#include "Menu.hpp"

using namespace indie;

Menu::Menu(irr::gui::IGUIEnvironment *gui, irr::video::IVideoDriver *driver, irr::core::dimension2du windowSize)
{
    this->_gui = gui;
    this->_driver = driver;
    this->_windowSize = windowSize;
    this->_isVisible = false;
    this->_options = NULL;
}

Menu::~Menu(){

}

void Menu::SetupGUI() {
    this->_setting = this->_gui->addButton(irr::core::rect<irr::s32>(this->_windowSize.Width / 2 - 80, this->_windowSize.Height / 2 - 140, this->_windowSize.Width / 2 + 80, this->_windowSize.Height / 2 - 60), NULL, RESUME,
            L"Resume", L"");
    this->_resume = this->_gui->addButton(irr::core::rect<irr::s32>(this->_windowSize.Width / 2 - 80, this->_windowSize.Height / 2 - 40, this->_windowSize.Width / 2 + 80, this->_windowSize.Height / 2 + 40), NULL, SETTING,
            L"Settings", L"");
    this->_quit = this->_gui->addButton(irr::core::rect<irr::s32>(this->_windowSize.Width / 2 - 80, this->_windowSize.Height / 2 + 60, this->_windowSize.Width / 2 + 80, this->_windowSize.Height / 2 + 140), NULL, QUIT,
            L"Quit", L"");
     this->_title = this->_gui->addStaticText(L"Menu", irr::core::rect<irr::s32>(this->_windowSize.Width / 2 - 140, this->_windowSize.Height / 2 - 180, this->_windowSize.Width / 2 + 140, this->_windowSize.Height / 2 - 140));
     this->_title->setTextAlignment(irr::gui::EGUIA_CENTER, irr::gui::EGUIA_SCALE);
}

void Menu::setVisible(bool visible) {
    this->_isVisible = visible;
}

bool Menu::isVisible(void) const {
    return this->_isVisible;
}

void Menu::OnEnterSetting()
{
    if (!_options)
    {
        this->_options = new Settings(this->_gui, this->_driver, this->_windowSize);
        this->_options->SetupGUI();
        this->_isVisible = false;
    }
    else
    {
        this->_options->setVisible(true);
    }
}

Settings *Menu::getSettings()
{
    return _options;
}

void Menu::OnFrame()
{
    if (_isVisible == true)
    {
        this->_driver->draw2DRectangle(irr::video::SColor(200,75,75,75), irr::core::rect<irr::s32>(this->_windowSize.Width / 2 - 140, this->_windowSize.Height / 2 - 200, this->_windowSize.Width / 2 + 140, this->_windowSize.Height / 2 + 200));
        this->_setting->setVisible(true);
        this->_resume->setVisible(true);
        this->_quit->setVisible(true);
        this->_title->setVisible(true);

        this->_setting->setEnabled(true);
        this->_resume->setEnabled(true);
        this->_quit->setEnabled(true);
        this->_title->setEnabled(true);
    }
    else
    {
        this->_setting->setVisible(false);
        this->_resume->setVisible(false);
        this->_quit->setVisible(false);
        this->_title->setVisible(false);

        this->_setting->setEnabled(false);
        this->_resume->setEnabled(false);
        this->_quit->setEnabled(false);
        this->_title->setEnabled(false);
    }
}

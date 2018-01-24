/*
** MainMenu.cpp for IndieStudio
**
** Made by	Full Name
** Login	Full Name
**
** Started on	Tue Jun 06 15:36:49 2017 Full Name
** Last update Fri Jun 16 15:14:43 2017 Lucas Gambini
*/

#include "MainMenu.hpp"

using namespace indie;

MainMenu::MainMenu(irr::gui::IGUIEnvironment *gui, irr::video::IVideoDriver *driver, irr::core::dimension2du windowSize)
{
    _gui = gui;
    _driver = driver;
    _windowSize = windowSize;
    _play = false;
}



MainMenu::~MainMenu()
{
    this->_start->remove();
    this->_multijoueur->remove();
    this->_quit->remove();
    this->_back->remove();
    this->_title->remove();
}

bool MainMenu::getPlay() const
{
    return _play;
}

void MainMenu::setPlay(bool play)
{
    _play = play;
}

void MainMenu::SetupGUI()
{

    this->_texture = this->_driver->getTexture("menu.jpg");
    this->_back = this->_gui->addImage(this->_texture, irr::core::position2d<irr::s32>(0, 0));

    this->_title = this->_gui->addStaticText(L"I Don't Car", irr::core::rect<irr::s32>(160, 160, this->_windowSize.Width, this->_windowSize.Height));
    this->_title->setOverrideColor(irr::video::SColor(255, 180, 180, 180));
    this->_title->setOverrideFont(this->_gui->getFont("misc/menu.xml"));

    this->_start = this->_gui->addButton(irr::core::rect<irr::s32>(this->_windowSize.Width / 6 - 100, this->_windowSize.Height / 2 - 160, this->_windowSize.Width / 6 + 100, this->_windowSize.Height / 2 - 80), NULL, PLAY,
            L"PLAY", L"");
    this->_multijoueur = this->_gui->addButton(irr::core::rect<irr::s32>(this->_windowSize.Width / 6 - 100, this->_windowSize.Height / 2 - 60, this->_windowSize.Width / 6 + 100, this->_windowSize.Height / 2 + 20), NULL, MULTIJOUEUR,
            L"MULTIJOUEUR", L"");
    this->_quit = this->_gui->addButton(irr::core::rect<irr::s32>(this->_windowSize.Width / 6 - 100, this->_windowSize.Height / 2 + 40, this->_windowSize.Width / 6 + 100, this->_windowSize.Height / 2 + 120), NULL, QUIT,
            L"QUIT", L"");
}

void MainMenu::setVisible(bool visible)
{
    _isVisible = visible;
}

bool MainMenu::isVisible() const
{
    return _isVisible;
}

void MainMenu::OnFrame()
{
}

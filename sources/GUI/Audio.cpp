/*
** Audio.cpp for IndieStudio in /Users/Vacca_J/Epitech/Tek2/Projet/IndieStudio/sources/GUI
**
** Made by Vacca_J
** Login   <Vacca_J@epitech.net>
**
** Started on  Sat May 20 14:35:05 2017 Vacca_J
** Last update Sat Jun 17 17:13:24 2017 Lucas Gambini
*/

#include "Audio.hpp"

using namespace indie;

Audio::Audio(irr::gui::IGUIEnvironment *gui, irr::video::IVideoDriver *driver, irr::core::dimension2du windowSize)
{
  this->_gui = gui;
  this->_driver = driver;
  this->_windowSize = windowSize;
  this->_isVisible = true;
  this->_red = this->_driver->getTexture("../../Assets/gui/red.jpg");
  this->_green = this->_driver->getTexture("../../Assets/gui/green.jpg");
}

Audio::~Audio()
{
}

void Audio::SetupGUI()
{
  this->_moin = this->_gui->addButton(irr::core::rect<irr::s32>(this->_windowSize.Width / 2 - 200, this->_windowSize.Height / 2 - 25, this->_windowSize.Width / 2 - 150, this->_windowSize.Height / 2 + 25), NULL, 2002,
          L"-", L"-");
  this->_plus = this->_gui->addButton(irr::core::rect<irr::s32>(this->_windowSize.Width / 2 + 150, this->_windowSize.Height / 2 - 25, this->_windowSize.Width / 2 + 200, this->_windowSize.Height / 2 + 23), NULL, 2001,
          L"+", L"+");
  this->_exit = this->_gui->addButton(irr::core::rect<irr::s32>(this->_windowSize.Width / 2 - 50, this->_windowSize.Height / 2 + 80, this->_windowSize.Width / 2 + 50, this->_windowSize.Height / 2 + 163), NULL, 2003,
    L"QUIT", L"Quit");
  this->_bar1 = this->_gui->addImage(irr::core::rect<irr::s32>(this->_windowSize.Width / 2 - 125, this->_windowSize.Height / 2 - 25, this->_windowSize.Width / 2 - 100, this->_windowSize.Height / 2 + 25), NULL, -1, NULL, true);
  this->_bar1->setImage(this->_red);
  this->_volume.push_back(this->_bar1);

  this->_bar2 = this->_gui->addImage(irr::core::rect<irr::s32>(this->_windowSize.Width / 2 - 100, this->_windowSize.Height / 2 - 25, this->_windowSize.Width / 2 - 75, this->_windowSize.Height / 2 + 25), NULL, -1, NULL, true);
  this->_bar2->setImage(this->_red);
  this->_volume.push_back(this->_bar2);


  this->_bar3 = this->_gui->addImage(irr::core::rect<irr::s32>(this->_windowSize.Width / 2 - 75, this->_windowSize.Height / 2 - 25, this->_windowSize.Width / 2 - 50, this->_windowSize.Height / 2 + 25), NULL, -1, NULL, true);
  this->_bar3->setImage(this->_red);
  this->_volume.push_back(this->_bar3);

  this->_bar4 = this->_gui->addImage(irr::core::rect<irr::s32>(this->_windowSize.Width / 2 - 50, this->_windowSize.Height / 2 - 25, this->_windowSize.Width / 2  - 25, this->_windowSize.Height / 2 + 25), NULL, -1, NULL, true);
  this->_bar4->setImage(this->_red);
  this->_volume.push_back(this->_bar4);

  this->_bar5 = this->_gui->addImage(irr::core::rect<irr::s32>(this->_windowSize.Width / 2 - 25, this->_windowSize.Height / 2 - 25, this->_windowSize.Width / 2, this->_windowSize.Height / 2 + 25), NULL, -1, NULL, true);
  this->_bar5->setImage(this->_red);
  this->_volume.push_back(this->_bar5);

  this->_bar6 = this->_gui->addImage(irr::core::rect<irr::s32>(this->_windowSize.Width / 2, this->_windowSize.Height / 2 - 25, this->_windowSize.Width / 2 + 25, this->_windowSize.Height / 2 + 25), NULL, -1, NULL, true);
  this->_bar6->setImage(this->_red);
  this->_volume.push_back(this->_bar6);

  this->_bar7 = this->_gui->addImage(irr::core::rect<irr::s32>(this->_windowSize.Width / 2 + 25, this->_windowSize.Height / 2 - 25, this->_windowSize.Width / 2 + 50, this->_windowSize.Height / 2 + 25), NULL, -1, NULL, true);
  this->_bar7->setImage(this->_red);
  this->_volume.push_back(this->_bar7);

  this->_bar8 = this->_gui->addImage(irr::core::rect<irr::s32>(this->_windowSize.Width / 2 + 50, this->_windowSize.Height / 2 - 25, this->_windowSize.Width / 2 + 75, this->_windowSize.Height / 2 + 25), NULL, -1, NULL, true);
  this->_bar8->setImage(this->_red);
  this->_volume.push_back(this->_bar8);

  this->_bar9 = this->_gui->addImage(irr::core::rect<irr::s32>(this->_windowSize.Width / 2 + 75, this->_windowSize.Height / 2 - 25, this->_windowSize.Width / 2 + 100, this->_windowSize.Height / 2 + 25), NULL, -1, NULL, true);
  this->_bar9->setImage(this->_red);
  this->_volume.push_back(this->_bar9);

  this->_bar10 = this->_gui->addImage(irr::core::rect<irr::s32>(this->_windowSize.Width / 2 + 100, this->_windowSize.Height / 2 - 25, this->_windowSize.Width / 2 + 125, this->_windowSize.Height / 2 + 25), NULL, -1, NULL, true);
  this->_bar10->setImage(this->_red);
  this->_volume.push_back(this->_bar10);

  this->_title = this->_gui->addStaticText(L"Audio", irr::core::rect<irr::s32>(this->_windowSize.Width / 2 - 140, this->_windowSize.Height / 2 - 120, this->_windowSize.Width / 2 + 140, this->_windowSize.Height / 2 - 80));
  this->_title->setTextAlignment(irr::gui::EGUIA_CENTER, irr::gui::EGUIA_SCALE);
}

void Audio::setVisible(bool visible)
{
  this->_isVisible = visible;
}

bool Audio::isVisible(void) const
{
    return this->_isVisible;
}

void Audio::plus()
{
  if (SoundManager::Instance().getEngine()->getSoundVolume() < 1)
    SoundManager::Instance().getEngine()->setSoundVolume(SoundManager::Instance().getEngine()->getSoundVolume() + 0.1f);
}

void Audio::moin()
{
  if (SoundManager::Instance().getEngine()->getSoundVolume() > 0)
    SoundManager::Instance().getEngine()->setSoundVolume(SoundManager::Instance().getEngine()->getSoundVolume() - 0.1f);
}

void Audio::OnFrame()
{
    if (_isVisible == true)
    {
        float i = 0.0f;
        for (auto& x : this->_volume)
        {
            x->setVisible(true);
            if (i < SoundManager::Instance().getEngine()->getSoundVolume()) {
                x->setImage(this->_green);
            } else {
                x->setImage(this->_red);
            }
            i += 0.1f;
        }
        this->_driver->draw2DRectangle(irr::video::SColor(200,75,75,75), irr::core::rect<irr::s32>(this->_windowSize.Width / 2 - 250, this->_windowSize.Height / 2 - 140, this->_windowSize.Width / 2 + 250, this->_windowSize.Height / 2 + 180));
        this->_plus->setVisible(true);
        this->_moin->setVisible(true);
        this->_exit->setVisible(true);
        this->_title->setVisible(true);

        this->_plus->setEnabled(true);
        this->_moin->setEnabled(true);
        this->_exit->setEnabled(true);
    }
    else
    {
        for (auto& x : this->_volume)
        {
          x->setVisible(false);
        }
        this->_plus->setVisible(false);
        this->_moin->setVisible(false);
        this->_exit->setVisible(false);
        this->_title->setVisible(false);

        this->_plus->setEnabled(false);
        this->_moin->setEnabled(false);
        this->_exit->setEnabled(false);
    }
}

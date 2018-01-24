/*
** Keyboard.cpp for IndieStudio in /Users/Vacca_J/Epitech/Tek2/Projet/IndieStudio/sources/GUI
**
** Made by Vacca_J
** Login   <Vacca_J@epitech.net>
**
** Started on  Sat May 20 17:38:44 2017 Vacca_J
** Last update Sat Jun 17 17:13:39 2017 Lucas Gambini
*/

#include "Keyboard.hpp"

using namespace indie;

Keyboard::Keyboard(irr::gui::IGUIEnvironment *gui, irr::video::IVideoDriver *driver, irr::core::dimension2du windowSize)
{
  this->_gui = gui;
  this->_driver = driver;
  this->_windowSize = windowSize;
  this->_isVisible = true;
  this->_mymap[KEYCODE_TYPE::UP] = irr::KEY_UP;
  this->_mymap[KEYCODE_TYPE::DOWN] = irr::KEY_DOWN;
  this->_mymap[KEYCODE_TYPE::LEFT] = irr::KEY_LEFT;
  this->_mymap[KEYCODE_TYPE::RIGHT] = irr::KEY_RIGHT;
  this->_mymap[KEYCODE_TYPE::FORWARD] = irr::KEY_KEY_D;
  this->_mymap[KEYCODE_TYPE::BACKWARD] = irr::KEY_KEY_R;
  this->_id = 0;
}

Keyboard::~Keyboard()
{
}

void Keyboard::SetupGUI()
{
  this->_exit = this->_gui->addButton(irr::core::rect<irr::s32>(this->_windowSize.Width / 2 - 45, this->_windowSize.Height / 2 + 110, this->_windowSize.Width / 2 + 45, this->_windowSize.Height / 2 + 160), NULL, 1008,
    L"EXIT", L"");
  this->_left = this->_gui->addButton(irr::core::rect<irr::s32>(this->_windowSize.Width / 2 - 340, this->_windowSize.Height / 2 - 25, this->_windowSize.Width / 2 - 260, this->_windowSize.Height / 2 + 25), NULL, 1003,
    L"LEFT", L"");
  this->_right = this->_gui->addButton(irr::core::rect<irr::s32>(this->_windowSize.Width / 2 - 180, this->_windowSize.Height / 2 - 25, this->_windowSize.Width / 2 - 100, this->_windowSize.Height / 2 + 25), NULL, 1004,
    L"RIGHT", L"");
  this->_down = this->_gui->addButton(irr::core::rect<irr::s32>(this->_windowSize.Width / 2 - 260, this->_windowSize.Height / 2 + 35, this->_windowSize.Width / 2 - 180, this->_windowSize.Height / 2 + 85), NULL, 1002,
    L"DOWN", L"");
  this->_up = this->_gui->addButton(irr::core::rect<irr::s32>(this->_windowSize.Width / 2 - 260, this->_windowSize.Height / 2 - 75, this->_windowSize.Width / 2 - 180, this->_windowSize.Height / 2 - 25), NULL, 1001,
    L"UP", L"");
  this->_forward = this->_gui->addButton(irr::core::rect<irr::s32>(this->_windowSize.Width / 2 + 150, this->_windowSize.Height / 2 - 85, this->_windowSize.Width / 2 + 310, this->_windowSize.Height / 2 - 35), NULL, 1005,
    L"FORWARD", L"");
  this->_backward = this->_gui->addButton(irr::core::rect<irr::s32>(this->_windowSize.Width / 2 + 150, this->_windowSize.Height / 2 + 35, this->_windowSize.Width / 2 + 310, this->_windowSize.Height / 2 + 85), NULL, 1006,
    L"BACKWARD", L"");
  this->_space = this->_gui->addButton(irr::core::rect<irr::s32>(this->_windowSize.Width / 2 - 85, this->_windowSize.Height / 2 + 55, this->_windowSize.Width / 2 + 85, this->_windowSize.Height / 2 + 85), NULL, 1007,
    L"FREIN", L"");

  this->_title2 = this->_gui->addStaticText(L"Click a Button and Press new KEY", irr::core::rect<irr::s32>(this->_windowSize.Width / 2 - 210, this->_windowSize.Height / 2 - 150, this->_windowSize.Width / 2 + 210, this->_windowSize.Height / 2 - 50));
  this->_title2->setTextAlignment(irr::gui::EGUIA_CENTER, irr::gui::EGUIA_SCALE);
  this->_title = this->_gui->addStaticText(L"Keyboard", irr::core::rect<irr::s32>(this->_windowSize.Width / 2 - 100, this->_windowSize.Height / 2 - 190, this->_windowSize.Width / 2 + 100, this->_windowSize.Height / 2 - 160));
  this->_title->setTextAlignment(irr::gui::EGUIA_CENTER, irr::gui::EGUIA_SCALE);
}

void Keyboard::setVisible(bool visible)
{
  this->_isVisible = visible;
}

bool Keyboard::isVisible(void) const
{
    return this->_isVisible;
}

void Keyboard::resetUp(void)
{
  this->_id = KEYCODE_TYPE::UP;

}

void Keyboard::resetDown(void)
{
  this->_id = KEYCODE_TYPE::DOWN;
}

void Keyboard::resetLeft(void)
{
  this->_id = KEYCODE_TYPE::LEFT;
}

void Keyboard::resetRight(void)
{
  this->_id = KEYCODE_TYPE::RIGHT;
}

void Keyboard::resetForward(void)
{
  this->_id = KEYCODE_TYPE::FORWARD;
}

void Keyboard::resetBackward(void)
{
  this->_id = KEYCODE_TYPE::BACKWARD;
}

void Keyboard::resetBrake(void)
{
  this->_id = KEYCODE_TYPE::SPACE;
}

void Keyboard::OnEnterKey(irr::EKEY_CODE keycode)
{
  if (this->_id == 0)
    return;
  this->_mymap[static_cast<KEYCODE_TYPE>(this->_id)] = keycode;
  this->_id = 0;
}

void Keyboard::OnFrame()
{
    if (_isVisible == true)
    {
        this->_driver->draw2DRectangle(irr::video::SColor(200,75,75,75), irr::core::rect<irr::s32>(this->_windowSize.Width / 2 - 350, this->_windowSize.Height / 2 - 200, this->_windowSize.Width / 2 + 350, this->_windowSize.Height / 2 + 180));
        this->_exit->setVisible(true);
        this->_up->setVisible(true);
        this->_down->setVisible(true);
        this->_right->setVisible(true);
        this->_left->setVisible(true);
        this->_forward->setVisible(true);
        this->_backward->setVisible(true);
        this->_space->setVisible(true);
        this->_title->setVisible(true);
        this->_title2->setVisible(true);

        this->_exit->setEnabled(true);
        this->_up->setEnabled(true);
        this->_down->setEnabled(true);
        this->_right->setEnabled(true);
        this->_left->setEnabled(true);
        this->_forward->setEnabled(true);
        this->_backward->setEnabled(true);
        this->_space->setEnabled(true);
    }
    else
    {
      this->_up->setVisible(false);
      this->_down->setVisible(false);
      this->_right->setVisible(false);
      this->_left->setVisible(false);
      this->_forward->setVisible(false);
      this->_backward->setVisible(false);
      this->_exit->setVisible(false);
      this->_space->setVisible(false);
      this->_title->setVisible(false);
      this->_title2->setVisible(false);

      this->_exit->setEnabled(false);
      this->_up->setEnabled(false);
      this->_down->setEnabled(false);
      this->_right->setEnabled(false);
      this->_left->setEnabled(false);
      this->_forward->setEnabled(false);
      this->_backward->setEnabled(false);
      this->_space->setEnabled(false);
    }
}

const std::map<Keyboard::KEYCODE_TYPE, irr::EKEY_CODE> &Keyboard::getMap() const {
    return this->_mymap;
}

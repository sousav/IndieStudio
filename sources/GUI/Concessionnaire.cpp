/*
** Concessionnaire.cpp for IndieStudio in /Users/Vacca_J/Epitech/Tek2/Projet/IndieStudio/sources/GUI
**
** Made by Vacca_J
** Login   <Vacca_J@epitech.net>
**
** Started on  Sat May 20 23:55:02 2017 Vacca_J
** Last update Sun Jun 18 22:33:04 2017 Lucas Gambini
*/

#include "Concessionnaire.hpp"

using namespace indie;

Concessionnaire::Concessionnaire(irr::gui::IGUIEnvironment *gui, irr::video::IVideoDriver *driver, irr::core::dimension2du windowSize)
{
  this->_gui = gui;
  this->_driver = driver;
  this->_windowSize = windowSize;
  this->_isVisible = true;
  this->_isVisible1 = false;
  this->_colorpng = this->_driver->getTexture("../../Assets/auto_color.png");

  this->_tred = this->_driver->getTexture("../../Assets/gui/ired.png");
  this->_tpink = this->_driver->getTexture("../../Assets/gui/pink.jpg");
  this->_tblue = this->_driver->getTexture("../../Assets/gui/blue.jpg");
  this->_tgreen = this->_driver->getTexture("../../Assets/gui/igreen.png");
  this->_tyellow = this->_driver->getTexture("../../Assets/gui/yellow.png");
  this->_torange = this->_driver->getTexture("../../Assets/gui/orange.png");
  this->_twhite = this->_driver->getTexture("../../Assets/gui/white.png");

  this->_mycolor.push_back(this->_tred);
  this->_mycolor.push_back(this->_tblue);
  this->_mycolor.push_back(this->_tgreen);
  this->_mycolor.push_back(this->_torange);
  this->_mycolor.push_back(this->_tpink);
  this->_mycolor.push_back(this->_twhite);
  this->_mycolor.push_back(this->_tyellow);

  this->_prevPressed = false;
  this->_nextPressed = false;
  this->_compt = 0;
}

Concessionnaire::~Concessionnaire()
{

}

void Concessionnaire::colorManager(int flag)
{
  if (flag == 1)
    {
      this->_compt++;
      if (this->_compt > this->_mycolor.size() - 1)
        this->_compt = 0;
      this->_color->setImage(this->_mycolor[this->_compt]);
    }
  else if (flag == 0)
    {
      this->_compt--;
      if (this->_compt < 0)
        this->_compt = this->_mycolor.size() - 1;
      this->_color->setImage(this->_mycolor[this->_compt]);
    }
}

void Concessionnaire::SetupCOLOR()
{
  this->_isVisible = false;
  this->_carcolor->setVisible(false);
  this->_leave->setVisible(false);
  this->_title->setVisible(false);
  this->_isVisible1 = true;
  this->_color->setVisible(true);
  this->_next1->setVisible(true);
  this->_enter1->setVisible(true);
  this->_previous1->setVisible(true);
  this->_exit1->setVisible(true);
  this->_title1->setVisible(true);
}

void Concessionnaire::colorMenu()
{
  if (this->_previous1->isPressed() && this->_prevPressed == false) {
      this->_prevPressed = true;
      this->colorManager(0);
  } else if (this->_next1->isPressed() && this->_nextPressed == false) {
      this->_nextPressed = true;
      this->colorManager(1);
  }
  if (this->_previous1->isPressed() == false)
    this->_prevPressed = false;
if (this->_next1->isPressed() == false)
    this->_nextPressed = false;
}


void Concessionnaire::SetupGUI()
{
// CONCESSIONNAIRE
  this->_carcolor = this->_gui->addButton(irr::core::rect<irr::s32>(this->_windowSize.Width / 2 - 65, this->_windowSize.Height / 2 - 70, this->_windowSize.Width / 2 + 65, this->_windowSize.Height / 2 + 60), NULL, -1,
           L"", L"");
  this->_carcolor->setImage(this->_colorpng, irr::core::rect<irr::s32>(this->_windowSize.Width / 2 - 200, this->_windowSize.Height / 2 - 100, this->_windowSize.Width / 2 - 70, this->_windowSize.Height / 2 + 50));
  this->_leave = this->_gui->addButton(irr::core::rect<irr::s32>(this->_windowSize.Width / 2 - 50, this->_windowSize.Height / 2 + 100, this->_windowSize.Width / 2 + 50, this->_windowSize.Height / 2 + 150), NULL, 20001,
     L"QUIT", L"Quit");
  this->_title = this->_gui->addStaticText(L"Concessionnaire", irr::core::rect<irr::s32>(this->_windowSize.Width / 2 - 140, this->_windowSize.Height / 2 - 120, this->_windowSize.Width / 2 + 140, this->_windowSize.Height / 2 - 80));
  this->_title->setTextAlignment(irr::gui::EGUIA_CENTER, irr::gui::EGUIA_SCALE);

// COLOR
    this->_title1 = this->_gui->addStaticText(L"Color Shop", irr::core::rect<irr::s32>(this->_windowSize.Width / 2 - 140, this->_windowSize.Height / 2 - 130, this->_windowSize.Width / 2 + 140, this->_windowSize.Height / 2 - 90));
    this->_title1->setTextAlignment(irr::gui::EGUIA_CENTER, irr::gui::EGUIA_SCALE);
    this->_previous1 = this->_gui->addButton(irr::core::rect<irr::s32>(this->_windowSize.Width / 2 - 200, this->_windowSize.Height / 2 - 25, this->_windowSize.Width / 2 - 150, this->_windowSize.Height / 2 + 25), NULL, 20003,
           L"<", L"<");
    this->_next1 = this->_gui->addButton(irr::core::rect<irr::s32>(this->_windowSize.Width / 2 + 150, this->_windowSize.Height / 2 - 25, this->_windowSize.Width / 2 + 200, this->_windowSize.Height / 2 + 23), NULL, 20002,
           L">", L">");
    this->_exit1 = this->_gui->addButton(irr::core::rect<irr::s32>(this->_windowSize.Width / 2 + 25, this->_windowSize.Height / 2 + 125, this->_windowSize.Width / 2 + 240, this->_windowSize.Height / 2 + 175), NULL, 20005,
             L"QUIT", L"");
    this->_enter1 = this->_gui->addButton(irr::core::rect<irr::s32>(this->_windowSize.Width / 2 - 240, this->_windowSize.Height / 2 + 125, this->_windowSize.Width / 2 - 25, this->_windowSize.Height / 2 + 175), NULL, 20004,
             L"CHANGE (200$)", L"");
    this->_color = this->_gui->addImage(irr::core::rect<irr::s32>(this->_windowSize.Width / 2 - 125, this->_windowSize.Height / 2 + -50, this->_windowSize.Width / 2 + 125, this->_windowSize.Height / 2 + 50), NULL, -1,
               L"", L"");

}

void Concessionnaire::setVisible(bool visible)
{
    this->_isVisible = visible;
    this->_isVisible1 = visible;
}

bool Concessionnaire::isVisible(void) const
{
    return (this->_isVisible || this->_isVisible1);
}


void Concessionnaire::OnFrame()
{
    if (_isVisible == true)
    {
      this->_driver->draw2DRectangle(irr::video::SColor(200,75,75,75), irr::core::rect<irr::s32>(this->_windowSize.Width / 2 - 250, this->_windowSize.Height / 2 - 140, this->_windowSize.Width / 2 + 250, this->_windowSize.Height / 2 + 180));
        this->_carcolor->setVisible(true);
        this->_leave->setVisible(true);
        this->_title->setVisible(true);
      //COLOR
        this->_isVisible1 = false;
        this->_color->setVisible(false);
        this->_next1->setVisible(false);
        this->_previous1->setVisible(false);
        this->_exit1->setVisible(false);
        this->_title1->setVisible(false);
        this->_enter1->setVisible(false);
        this->_enter1->setEnabled(true);
        if (this->_carcolor->isPressed() == true)
          SetupCOLOR();
    }
  else if (_isVisible1 == true)
    {
      this->_driver->draw2DRectangle(irr::video::SColor(200,75,75,75), irr::core::rect<irr::s32>(this->_windowSize.Width / 2 - 250, this->_windowSize.Height / 2 - 140, this->_windowSize.Width / 2 + 250, this->_windowSize.Height / 2 + 180));
      colorMenu();
    }
    else
    {
      this->_carcolor->setVisible(false);
      this->_leave->setVisible(false);
      this->_title->setVisible(false);
      this->_isVisible1 = false;
      this->_color->setVisible(false);
      this->_next1->setVisible(false);
      this->_previous1->setVisible(false);
      this->_exit1->setVisible(false);
      this->_title1->setVisible(false);
      this->_enter1->setVisible(false);
      this->_enter1->setEnabled(false);
    }
}

int Concessionnaire::getColorIndex() const {
    return this->_compt;
}

/*
** Graphic.cpp for IndieStudio in /Users/Vacca_J/Epitech/Tek2/Projet/IndieStudio/sources/GUI
**
** Made by Vacca_J
** Login   <Vacca_J@epitech.net>
**
** Started on  Sat May 20 22:17:17 2017 Vacca_J
** Last update Sun Jun 18 18:46:51 2017 Lucas Gambini
*/

#include "Graphic.hpp"

using namespace indie;

Graphic::Graphic(irr::gui::IGUIEnvironment *gui, irr::video::IVideoDriver *driver, irr::core::dimension2du windowSize)
{
  this->_gui = gui;
  this->_driver = driver;
  this->_windowSize = windowSize;
  this->_isVisible = true;
}

Graphic::~Graphic()
{
}

void Graphic::SetupGUI()
{
    this->_resol1 = this->_gui->addButton(irr::core::rect<irr::s32>(this->_windowSize.Width / 2 - 80, this->_windowSize.Height / 2 - 140, this->_windowSize.Width / 2 + 80, this->_windowSize.Height / 2 - 60), NULL, RESOL1,
            L"640x480", L"");
    this->_resol2 = this->_gui->addButton(irr::core::rect<irr::s32>(this->_windowSize.Width / 2 - 80, this->_windowSize.Height / 2 - 40, this->_windowSize.Width / 2 + 80, this->_windowSize.Height / 2 + 40), NULL, RESOL2,
            L"1280x720", L"");
    this->_resol3 = this->_gui->addButton(irr::core::rect<irr::s32>(this->_windowSize.Width / 2 - 80, this->_windowSize.Height / 2 + 60, this->_windowSize.Width / 2 + 80, this->_windowSize.Height / 2 + 140), NULL, RESOL3,
            L"1920x1080", L"");
    this->_editBox = this->_gui->addEditBox(L"1000", irr::core::rect<irr::s32>(this->_windowSize.Width / 2 - 80, this->_windowSize.Height / 2 + 160, this->_windowSize.Width / 2 + 80, this->_windowSize.Height / 2 + 210), true, 0, -1);
    this->_exit = this->_gui->addButton(irr::core::rect<irr::s32>(this->_windowSize.Width / 2 - 80, this->_windowSize.Height / 2 + 260, this->_windowSize.Width / 2 + 80, this->_windowSize.Height / 2 + 310), NULL, EXIT,
            L"Exit", L"");
    this->_title = this->_gui->addStaticText(L"Graphics", irr::core::rect<irr::s32>(this->_windowSize.Width / 2 - 140, this->_windowSize.Height / 2 - 180, this->_windowSize.Width / 2 + 140, this->_windowSize.Height / 2 - 140));
    this->_title->setTextAlignment(irr::gui::EGUIA_CENTER, irr::gui::EGUIA_SCALE);
}

void Graphic::setVisible(bool visible)
{
  this->_isVisible = visible;
}

bool Graphic::isVisible(void) const
{
    return this->_isVisible;
}


void Graphic::OnFrame()
{
    if (_isVisible == true)
    {
        this->_driver->draw2DRectangle(irr::video::SColor(200,75,75,75), irr::core::rect<irr::s32>(this->_windowSize.Width / 2 - 140, this->_windowSize.Height / 2 - 200, this->_windowSize.Width / 2 + 140, this->_windowSize.Height / 2 + 330));
        this->_title->setVisible(true);
        this->_resol1->setVisible(true);
        this->_resol2->setVisible(true);
        this->_resol3->setVisible(true);
        this->_exit->setVisible(true);
        this->_editBox->setVisible(true);

        this->_resol1->setEnabled(true);
        this->_resol2->setEnabled(true);
        this->_resol3->setEnabled(true);
        this->_exit->setEnabled(true);

    }
    else
    {
        this->_title->setVisible(false);
        this->_resol1->setVisible(false);
        this->_resol2->setVisible(false);
        this->_resol3->setVisible(false);
        this->_exit->setVisible(false);
        this->_editBox->setVisible(false);

        this->_resol1->setEnabled(false);
        this->_resol2->setEnabled(false);
        this->_resol3->setEnabled(false);
        this->_exit->setEnabled(false);

    }
}

int Graphic::getText() const {
    int v = 1000;
    std::wstring ws(this->_editBox->getText());
    std::string str(ws.begin(), ws.end());
    if (str.size() < 6 && str.size() >= 2) {
        v  = atoi(str.c_str());
    }
    return v;
}

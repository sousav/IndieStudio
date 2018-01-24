/*
** JoinServer.cpp for Shared in /Users/gmblucas/Desktop/Shared/IndieStudio/sources/GUI
**
** Made by Lucas Gambini
** Login   <gmblucas@epitech.net>
**
** Started on  Wed May 31 00:47:53 2017 Lucas Gambini
** Last update Fri Jun 16 13:10:59 2017 Lucas Gambini
*/

#include "JoinServer.hpp"

using namespace indie;

JoinServer::JoinServer(irr::gui::IGUIEnvironment *gui, irr::video::IVideoDriver *driver, irr::core::dimension2du windowSize)
{
    this->_gui = gui;
    this->_driver = driver;
    this->_windowSize = windowSize;
    this->_isVisible = false;
}

JoinServer::~JoinServer()
{

}

void JoinServer::SetupGUI() {
    this->_leave_ = this->_gui->addButton(irr::core::rect<irr::s32>(this->_windowSize.Width / 2 - 80, this->_windowSize.Height / 2 + 60, this->_windowSize.Width / 2 + 80, this->_windowSize.Height / 2 + 140), 0, LEAVE,
            L"Leave", L"");

    this->_join = this->_gui->addButton(irr::core::rect<irr::s32>(this->_windowSize.Width / 2 - 80, this->_windowSize.Height / 2 - 40, this->_windowSize.Width / 2 + 80, this->_windowSize.Height / 2 + 40), 0, JOIN,
            L"Join", L"");

    this->_editBox = this->_gui->addEditBox(L"", irr::core::rect<irr::s32>(this->_windowSize.Width / 2 - 100, this->_windowSize.Height / 2 - 140, this->_windowSize.Width / 2 + 100, this->_windowSize.Height / 2 - 100), true, 0, -1);

    this->_title = this->_gui->addStaticText(L"Join a server", irr::core::rect<irr::s32>(this->_windowSize.Width / 2 - 140, this->_windowSize.Height / 2 - 180, this->_windowSize.Width / 2 + 140, this->_windowSize.Height / 2 - 120), false, false, 0, -1, false);
    this->_title->setTextAlignment(irr::gui::EGUIA_CENTER, irr::gui::EGUIA_SCALE);

}

void JoinServer::setVisible(bool visible) {
    this->_isVisible = visible;
}

bool JoinServer::isVisible(void) const {
    return this->_isVisible;
}

void JoinServer::OnFrame(void) {
    if (this->_isVisible == true) {
        this->_driver->draw2DRectangle(irr::video::SColor(200,75,75,75), irr::core::rect<irr::s32>(this->_windowSize.Width / 2 - 140, this->_windowSize.Height / 2 - 200, this->_windowSize.Width / 2 + 140, this->_windowSize.Height / 2 + 200));
        this->_title->setVisible(true);
        this->_leave_->setVisible(true);
        this->_leave_->setEnabled(true);
        this->_join->setVisible(true);
        this->_join->setEnabled(true);
        this->_editBox->setVisible(true);
    }
    else {
        this->_title->setVisible(false);
        this->_leave_->setVisible(false);
        this->_leave_->setEnabled(false);
        this->_join->setVisible(false);
        this->_join->setEnabled(false);
        this->_editBox->setVisible(false);
    }
}

const wchar_t* JoinServer::getText() const {
    return this->_editBox->getText();
}

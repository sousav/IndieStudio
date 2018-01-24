/*
** Course.cpp for Shared in /Users/gmblucas/Desktop/Shared/IndieStudio/sources/GUI
**
** Made by Lucas Gambini
** Login   <gmblucas@epitech.net>
**
** Started on  Sat May 20 00:40:58 2017 Lucas Gambini
** Last update Fri Jun 16 13:02:47 2017 Lucas Gambini
*/


#include "Course.hpp"

using namespace indie;

Course::Course(irr::gui::IGUIEnvironment *gui, irr::video::IVideoDriver *driver, irr::core::dimension2du windowSize)
{
    this->_gui = gui;
    this->_driver = driver;
    this->_windowSize = windowSize;
    this->_isVisible = false;
}

Course::~Course()
{

}

void Course::SetupGUI() {
    this->_run = this->_gui->addButton(irr::core::rect<irr::s32>(this->_windowSize.Width / 2 - 200, this->_windowSize.Height / 2 + 140, this->_windowSize.Width / 2 - 40, this->_windowSize.Height / 2 + 220), 0, RUN,
            L"Launch", L"");
    this->_cancel = this->_gui->addButton(irr::core::rect<irr::s32>(this->_windowSize.Width / 2 + 40, this->_windowSize.Height / 2 + 140, this->_windowSize.Width / 2 + 200, this->_windowSize.Height / 2 + 220), 0, CANCEL,
            L"Cancel", L"");

    this->_title = this->_gui->addStaticText(L"Run", irr::core::rect<irr::s32>(this->_windowSize.Width / 2 - 140, this->_windowSize.Height / 2 - 220, this->_windowSize.Width / 2 + 140, this->_windowSize.Height / 2 - 200), false, false, 0, -1, false);
    this->_title->setTextAlignment(irr::gui::EGUIA_CENTER, irr::gui::EGUIA_SCALE);

}

void Course::setVisible(bool visible) {
    this->_isVisible = visible;
}

bool Course::isVisible(void) const {
    return this->_isVisible;
}

void Course::OnFrame(void) {
    if (this->_isVisible == true) {
        this->_driver->draw2DRectangle(irr::video::SColor(200,75,75,75), irr::core::rect<irr::s32>(this->_windowSize.Width / 2 - 220, this->_windowSize.Height / 2 - 240, this->_windowSize.Width / 2 + 220, this->_windowSize.Height / 2 + 240));
        this->_title->setVisible(true);
        this->_run->setVisible(true);
        this->_cancel->setVisible(true);
        this->_run->setEnabled(true);
        this->_cancel->setEnabled(true);
    }
    else {
        this->_title->setVisible(false);
        this->_run->setVisible(false);
        this->_cancel->setVisible(false);
        this->_run->setEnabled(false);
        this->_cancel->setEnabled(false);
        this->ripPlayers();
    }
}

void Course::addPlayer(std::string const & player_id) {
    if (this->_players.size() > 5)
        return;
    int player_nb = this->_players.size() + 1;
    int ratio = player_nb * 40;
    irr::gui::IGUIStaticText *_newp = this->_gui->addStaticText(Utils::StrToWstr(player_id), irr::core::rect<irr::s32>(this->_windowSize.Width / 2 - 140, this->_windowSize.Height / 2 - 180 + ratio, this->_windowSize.Width / 2 + 140, this->_windowSize.Height / 2 - 160 + ratio), true, false, 0, -1, false);
    _newp->setTextAlignment(irr::gui::EGUIA_CENTER, irr::gui::EGUIA_SCALE);
    this->_players.push_back(_newp);
}

void Course::ripPlayers() {
    for (auto &x: this->_players) {
        if (x)
            x->remove();
    }
    this->_players.clear();
}

void Course::ripPlayer(std::string const &player) {
    int i = 0;
    for (auto &x: this->_players) {
        std::wstring ws(x->getText());
        std::string txt(ws.begin(), ws.end());
        if (txt == player) {
            x->remove();
            x = NULL;
            this->_players.erase(this->_players.begin() + i);
            return;
        }
        i++;
    }
}

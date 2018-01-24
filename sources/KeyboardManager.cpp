/*
** KeyboardManager.cpp for IndieStudio in /Users/gmblucas/Desktop/Shared/IndieStudio/sources
**
** Made by Lucas Gambini
** Login   <gmblucas@epitech.net>
**
** Started on  Fri Jun 16 20:47:31 2017 Lucas Gambini
** Last update Sun Jun 18 04:41:15 2017 Sousa Victor
*/

#include "KeyboardManager.hpp"

using namespace indie;

KeyboardManager KeyboardManager::_instance = KeyboardManager();

KeyboardManager::KeyboardManager() {
    this->_map[Keyboard::KEYCODE_TYPE::UP] = irr::KEY_UP;
    this->_map[Keyboard::KEYCODE_TYPE::DOWN] = irr::KEY_DOWN;
    this->_map[Keyboard::KEYCODE_TYPE::LEFT] = irr::KEY_LEFT;
    this->_map[Keyboard::KEYCODE_TYPE::RIGHT] = irr::KEY_RIGHT;
    this->_map[Keyboard::KEYCODE_TYPE::FORWARD] = irr::KEY_KEY_P;
    this->_map[Keyboard::KEYCODE_TYPE::BACKWARD] = irr::KEY_KEY_L;
    this->_map[Keyboard::KEYCODE_TYPE::SPACE] = irr::KEY_SPACE;

    this->_map2[Keyboard::KEYCODE_TYPE::UP] = irr::KEY_KEY_W;
    this->_map2[Keyboard::KEYCODE_TYPE::DOWN] = irr::KEY_KEY_S;
    this->_map2[Keyboard::KEYCODE_TYPE::LEFT] = irr::KEY_KEY_A;
    this->_map2[Keyboard::KEYCODE_TYPE::RIGHT] = irr::KEY_KEY_D;
    this->_map2[Keyboard::KEYCODE_TYPE::FORWARD] = irr::KEY_KEY_T;
    this->_map2[Keyboard::KEYCODE_TYPE::BACKWARD] = irr::KEY_KEY_F;
    this->_map2[Keyboard::KEYCODE_TYPE::SPACE] = irr::KEY_KEY_X;

}

KeyboardManager::~KeyboardManager() {
}

KeyboardManager &KeyboardManager::Instance() {
    return _instance;
}

void KeyboardManager::setMap(std::map<Keyboard::KEYCODE_TYPE, irr::EKEY_CODE> const &map) {
    this->_map = map;
}

std::map<Keyboard::KEYCODE_TYPE, irr::EKEY_CODE> &KeyboardManager::getMap() {
    return this->_map;
}

std::map<Keyboard::KEYCODE_TYPE, irr::EKEY_CODE> &KeyboardManager::getMap2() {
    return this->_map2;
}

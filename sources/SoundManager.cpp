/*
** SoundManager.cpp for IndieStudio in /Users/gmblucas/Desktop/Shared/IndieStudio/sources
**
** Made by Lucas Gambini
** Login   <gmblucas@epitech.net>
**
** Started on  Fri Jun 16 18:17:19 2017 Lucas Gambini
** Last update Sun Jun 18 18:20:09 2017 Lucas Gambini
*/

#include "SoundManager.hpp"

using namespace indie;

SoundManager SoundManager::_instance = SoundManager();

SoundManager::SoundManager() {
    this->_engine = irrklang::createIrrKlangDevice();
    this->_engine->setSoundVolume(0.5f);
}

SoundManager::~SoundManager() {
    if (this->_engine)
        this->_engine->drop();
}

SoundManager &SoundManager::Instance() {
    return _instance;
}

irrklang::ISoundEngine* SoundManager::getEngine() {
    return this->_engine;
}

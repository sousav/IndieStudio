//
// EventReceiver.cpp for  in /Users/vicostudio/Documents/Shared/TEK2/CPP/cpp_indie_studio/sources/
//
// Made by Sousa Victor
// Login   <sousa_v@epitech.eu>
//
// Started on  Mon May  8 19:57:10 2017 Sousa Victor
// Last update Mon May  8 22:26:28 2017 Sousa Victor
//

#include "EventReceiver.hpp"

using namespace indie;

EventReceiver::EventReceiver() {
    for (irr::u32 i=0; i < irr::KEY_KEY_CODES_COUNT; ++i)
        this->_keyIsDown[i] = false;
}

EventReceiver::EventReceiver(const EventReceiver &receiver) {
    for (irr::u32 i=0; i < irr::KEY_KEY_CODES_COUNT; ++i)
        this->_keyIsDown[i] = receiver._keyIsDown[i];
}

EventReceiver &EventReceiver::operator=(const EventReceiver &receiver) {
    for (irr::u32 i=0; i < irr::KEY_KEY_CODES_COUNT; ++i)
        this->_keyIsDown[i] = receiver._keyIsDown[i];
    return *this;
}

EventReceiver::~EventReceiver() {

}

bool EventReceiver::OnEvent(const irr::SEvent& event) {
    if (event.EventType == irr::EET_KEY_INPUT_EVENT){
        if (this->_keyIsDown[event.KeyInput.Key] && !event.KeyInput.PressedDown) {
            this->OnReleaseKey(event.KeyInput.Key);
        } else if (!this->_keyIsDown[event.KeyInput.Key] && event.KeyInput.PressedDown){
            this->OnEnterKey(event.KeyInput.Key);
        }
        this->_keyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
    }
    return false;
}

bool EventReceiver::IsKeyDown(irr::EKEY_CODE keyCode) const {
    return this->_keyIsDown[keyCode];
}

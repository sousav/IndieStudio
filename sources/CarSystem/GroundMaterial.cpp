//
// GroundMaterial.cpp for  in /Users/vicostudio/Documents/Shared/TEK2/CPP/cpp_indie_studio_/sources/CarSystem/
//
// Made by Sousa Victor
// Login   <sousa_v@epitech.eu>
//
// Started on  Tue May 16 12:21:16 2017 Sousa Victor
// Last update Tue May 16 12:26:00 2017 Sousa Victor
//

#include "GroundMaterial.hpp"

using namespace indie;

GroundMaterial::GroundMaterial() {
    this->_grip = 1.0f;
    this->_drag = 0.1f;
    this->_surfaceType = SurfaceType::Hard;
}

GroundMaterial::~GroundMaterial() {

}


float GroundMaterial::getGrip() const {
    return this->_grip;
}

void GroundMaterial::setGrip(float grip) {
    this->_grip = grip;
}


float GroundMaterial::getDrag() const {
    return this->_drag;
}

void GroundMaterial::setDrag(float drag) {
    this->_drag = drag;
}

/*
** SizeS.cpp for IndieStudio in /Users/gmblucas/Desktop/Shared/IndieStudio/sources
**
** Made by Lucas Gambini
** Login   <gmblucas@epitech.net>
**
** Started on  Fri Jun 16 18:17:19 2017 Lucas Gambini
** Last update Sat Jun 17 23:21:25 2017 Lucas Gambini
*/

#include "SizeS.hpp"

using namespace indie;

SizeS SizeS::_instance = SizeS();

SizeS::SizeS() {
}

SizeS::~SizeS() {
}

SizeS &SizeS::Instance() {
    return _instance;
}

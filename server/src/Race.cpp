//
// Race.cpp for race in /Users/leandr_g/Documents/Shared folder/IndieStudio/server/src/
//
// Made by Gaëtan Léandre
// Login   <gaetan.leandre@epitech.eu>
//
// Started on  Fri May 26 03:56:26 2017 Gaëtan Léandre
// Last update Fri May 26 04:03:24 2017 Gaëtan Léandre
//

#include        "Race.hh"

Race::Race(int id)
{
    this->_id = id;
}

Race::~Race()
{
}

Race::Race(const Race &obj)
{
    this->_id = obj._id;
    this->_clients = obj._clients;
}

Race    &Race::operator=(const Race &obj)
{
    this->_id = obj._id;
    this->_clients = obj._clients;
    return (*this);
}

int Race::getId() const
{
    return (this->_id);
}

void Race::setId(int id)
{
    this->_id = id;
}

int Race::getLeader() const {
    return this->_clients.begin()->first;
}

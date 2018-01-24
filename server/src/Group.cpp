//
// Group.cpp for group in /Users/leandr_g/Documents/Shared folder/IndieStudio/Group/src/
//
// Made by Gaëtan Léandre
// Login   <gaetan.leandre@epitech.eu>
//
// Started on  Fri May 26 03:53:13 2017 Gaëtan Léandre
// Last update Fri May 26 04:09:45 2017 Gaëtan Léandre
//

#include            "Group.hh"

Group::Group()
{
}

Group::~Group()
{
    for (auto &client : this->_clients) {
        deleteClientByFd(client.first);
    }
}

Group::Group(const Group &obj)
{
    this->_clients = obj._clients;
}

Group    &Group::operator=(const Group &obj)
{
    this->_clients = obj._clients;
    return (*this);
}

void Group::writeAll(std::string const &str)
{
    for (auto &x: this->_clients)
    {
        x.second->write(str);
    }
}

void Group::writeAllExeptById(std::string const &str, int id)
{
    for (auto &x: this->_clients)
    {
        if (x.second->getId() != id)
            x.second->write(str);
    }
}

void Group::writeAllExeptByFd(std::string const &str, int fd)
{
    for (auto &x: this->_clients)
    {
        if (x.second->getSocket().getFd() != fd)
            x.second->write(str);
    }
}

bool Group::foundClientById(int id)
{
    for (auto &x: this->_clients)
    {
        if (x.second->getId() == id)
            return (true);
    }
    return (false);
}

bool Group::foundClientByFd(int fd)
{
    if (this->_clients.count(fd) > 0)
        return (true);
    return (false);
}

void Group::addClient(Client *client)
{
    this->_clients[client->getSocket().getFd()] = client;
}

bool Group::deleteClientById(int id)
{
    for (auto &x: this->_clients)
    {
        if (x.second->getId() == id)
        {
            this->_clients.erase(x.second->getSocket().getFd());
            return (true);
        }
    }
    return (false);
}

bool Group::deleteClientByFd(int fd)
{
    if (this->_clients.count(fd) > 0)
    {
        this->_clients.erase(fd);
        return (true);
    }
    return (false);
}

int Group::getClientNumber() const {
    return this->_clients.size();
}

//
// Client.cpp for client in /Users/leandr_g/Documents/Shared folder/IndieStudio/server/src/
//
// Made by Gaëtan Léandre
// Login   <gaetan.leandre@epitech.eu>
//
// Started on  Thu May 25 23:47:52 2017 Gaëtan Léandre
// Last update Fri May 26 02:09:19 2017 Gaëtan Léandre
//

#include            "Client.hh"

Client::Client()
{
    this->_money = 0;
    this->_id = 0;
}

Client::~Client()
{
}

Client::Client(Client const &obj)
{
    this->_sock = (const_cast<Client &>(obj))._sock;
    this->_money = obj._money;
    this->_id = obj._id;
}

Client    &Client::operator=(Client const &obj)
{
    this->_sock = (const_cast<Client &>(obj))._sock;
    this->_money = obj._money;
    this->_id = obj._id;
    return (*this);
}

ClientSocket const &Client::getSocket() const
{
    return (this->_sock);
}

void Client::setSocket(ClientSocket &socket)
{
    this->_sock = socket;
}

int Client::getMoney() const
{
    return (this->_money);
}

void Client::setMoney(int money)
{
    this->_money = money;
}

int Client::getId() const
{
    return (this->_id);
}

void Client::setId(int id)
{
    this->_id = id;
}

int Client::getCarNo() const {
    return this->_car_no;
}

void Client::setCarNo(int no) {
    this->_car_no = no;
}

bool Client::accept(SOCKET fd)
{
    return (this->_sock.accept(fd));
}

std::string Client::read()
{
    return (this->_sock.read());
}

#include <iostream>
#include "Message.hh"
void Client::write(std::string const &str)
{
    Message lol("no");
    lol.parseJSON(str);
    if (lol.getTitle() != "cardata")
        std::cout << "SENDING: " << str << std::endl;
    this->_sock.write(str);
}

//
// Socket.cpp for socket in /Users/leandr_g/Documents/Shared folder/IndieStudio/server/src/
//
// Made by Gaëtan Léandre
// Login   <gaetan.leandre@epitech.eu>
//
// Started on  Thu May 25 01:50:32 2017 Gaëtan Léandre
// Last update Wed Jun  7 00:38:46 2017 Gaëtan Léandre
//

#include        "Socket.hh"

Socket::Socket()
{
    this->_fd = -1;
    this->_ip = "";
    this->_started = false;
    this->_detach = false;
}

Socket::~Socket()
{
    if (this->_started == true && this->_detach == false)
        ::close(this->_fd);
}

Socket::Socket(Socket &obj)
{
    this->_fd = obj._fd;
    this->_ip = obj._ip;
    this->_started = obj._started;
    this->_detach = false;
    obj._detach = true;
}

Socket    &Socket::operator=(Socket &obj)
{
    this->_fd = obj._fd;
    this->_ip = obj._ip;
    this->_started = obj._started;
    this->_detach = false;
    obj._detach = true;
    return (*this);
}

std::string const &Socket::getIp() const
{
    return (this->_ip);
}

void Socket::write(std::string const &str)
{
    if (this->_started == true)
        ::write(this->_fd, str.c_str(), str.size() > MAX_BUFF_SIZE - 1 ? MAX_BUFF_SIZE - 1 : str.size());
}

std::string Socket::read()
{
    char buffer[MAX_BUFF_SIZE];
    int save;

    bzero(buffer, MAX_BUFF_SIZE);
    if (this->_started == true)
        save = ::read(this->_fd, buffer, MAX_BUFF_SIZE);
    if (save > 0)
        return (std::string(buffer));
    return (std::string("-"));
}

SOCKET Socket::getFd() const
{
    return (this->_fd);
}

void Socket::setFd(SOCKET fd)
{
    if (this->_started == true && this->_detach == false)
        ::close(this->_fd);
    this->_fd = fd;
    this->_started = true;
    this->_detach = false;
}

bool Socket::isStarted() const
{
    return (this->_started);
}

bool Socket::isDetach() const
{
    return (this->_detach);
}

void Socket::detach()
{
    this->_detach = true;
}

void Socket::join()
{
    this->_detach = false;
}

void Socket::setListener(fd_set *fdset, int &max) const
{
    if (this->_started == true)
    {
        FD_SET(this->_fd, fdset);
        max = this->_fd > max ? this->_fd : max;
    }
}

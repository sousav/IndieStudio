//
// ClientSocket.hh for clientSocket in /Users/leandr_g/Documents/Shared folder/IndieStudio/server/src/
//
// Made by Gaëtan Léandre
// Login   <gaetan.leandre@epitech.eu>
//
// Started on  Thu May 25 02:27:04 2017 Gaëtan Léandre
// Last update Fri May 26 00:31:17 2017 Gaëtan Léandre
//

#include            "ClientSocket.hh"

ClientSocket::ClientSocket()
{
}

ClientSocket::~ClientSocket()
{
}

ClientSocket::ClientSocket(ClientSocket &obj)
{
    this->_fd = obj._fd;
    this->_ip = obj._ip;
    this->_started = obj._started;
    this->_detach = false;
    obj._detach = true;
}

ClientSocket    &ClientSocket::operator=(ClientSocket &obj)
{
    this->_fd = obj._fd;
    this->_ip = obj._ip;
    this->_started = obj._started;
    this->_detach = false;
    obj._detach = true;
    return (*this);
}

bool ClientSocket::accept(SOCKET fd)
{
    SOCKADDR_IN		s_in;
    socklen_t      size;

    size = sizeof(s_in);
    if (this->_started == true && this->_detach == false)
        ::close(this->_fd);
    this->_fd = ::accept(fd, (SOCKADDR *)&s_in, &size);
    if (this->_fd != -1)
    {
        this->_ip = inet_ntoa(s_in.sin_addr);
        this->_started = true;
        this->_detach = false;
        return (true);
    }
    else
        return (false);
}

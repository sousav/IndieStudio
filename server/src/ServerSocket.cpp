//
// ServerSocket.cpp for serverSocket in /Users/leandr_g/Documents/Shared folder/IndieStudio/server/src/
//
// Made by Gaëtan Léandre
// Login   <gaetan.leandre@epitech.eu>
//
// Started on  Thu May 25 02:38:39 2017 Gaëtan Léandre
// Last update Wed Jun  7 00:39:27 2017 Gaëtan Léandre
//

#include                "ServerSocket.hh"

ServerSocket::ServerSocket(int port, int maxConnection)
{
    this->_port = port;
    this->_maxConnection = maxConnection;
}

ServerSocket::ServerSocket(ServerSocket &obj)
{
    this->_fd = obj._fd;
    this->_ip = obj._ip;
    this->_started = obj._started;
    this->_detach = false;
    obj._detach = true;
    this->_port = obj._port;
    this->_maxConnection = obj._maxConnection;
}

ServerSocket    &ServerSocket::operator=(ServerSocket &obj)
{
    this->_fd = obj._fd;
    this->_ip = obj._ip;
    this->_started = obj._started;
    this->_detach = false;
    obj._detach = true;
    this->_port = obj._port;
    this->_maxConnection = obj._maxConnection;
    return (*this);
}

ServerSocket::~ServerSocket()
{
}

bool ServerSocket::init()
{
    SOCKADDR_IN             s_in;

    stop();
    #if defined (WIN32)
        WSADATA WSAData;
        WSAStartup(MAKEWORD(2,2), &WSAData);
    #endif
    s_in.sin_addr.s_addr = htonl(INADDR_ANY);
    s_in.sin_port = htons(this->_port);
    s_in.sin_family = AF_INET;
    if ((this->_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        return (false);
    if (bind(this->_fd, (SOCKADDR*)&s_in, sizeof(s_in)) == -1)
    {
        ::close(this->_fd);
        return (false);
    }
    else if (listen(this->_fd, this->_maxConnection) == -1)
    {
        ::close(this->_fd);
        return (false);
    }
    this->_started = true;
    this->_detach = false;
    return (true);
}

void ServerSocket::launchLoop()
{
    fd_set              fdset;
    int                 max;

    for (;;)
    {
        max = this->_fd;
        FD_ZERO(&fdset);
        setListener(&fdset, max);
        this->_game.setListener(&fdset, max);
        if (select(max + 1, &fdset, NULL, NULL, NULL) == -1)
            return;
        if (FD_ISSET(this->_fd, &fdset))
            this->_game.addClient(this->_fd);
        else
            this->_game.readClientByFdSet(&fdset);
    }
}

int ServerSocket::getPort() const
{
    return (this->_port);
}

void ServerSocket::setPort(int port)
{
    if (this->_started == false)
        this->_port = port;
}

int ServerSocket::getMaxConnection() const
{
    return (this->_maxConnection);
}

void ServerSocket::setMaxConnection(int maxConnection)
{
    if (this->_started == false)
        this->_maxConnection = maxConnection;
}

void ServerSocket::stop()
{
    if (this->_started == true && this->_detach == false)
    {
        this->_game.stop();
        ::close(this->_fd);
        this->_started = false;
    }
}

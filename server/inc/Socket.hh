//
// Socket.hh for socket in /Users/leandr_g/Documents/Shared folder/IndieStudio/server/inc/
//
// Made by Gaëtan Léandre
// Login   <gaetan.leandre@epitech.eu>
//
// Started on  Thu May 25 01:37:33 2017 Gaëtan Léandre
// Last update Tue Jun  6 21:53:35 2017 Gaëtan Léandre
//

#ifndef         SOCKET_HH_
#define         SOCKET_HH_

#include        <string>
#include        "SocketInclude.hh"

#define         MAX_BUFF_SIZE       4096

class Socket {
protected:
    SOCKET _fd;
    std::string _ip;
    bool _started;
    bool _detach;

public:
    Socket ();
    virtual ~Socket ();
    Socket(Socket &obj);
    Socket    &operator=(Socket &obj);
    std::string const &getIp() const;
    void write(std::string const &str);
    std::string read();
    void close();
    SOCKET getFd() const;
    void setFd(SOCKET fd);
    bool isStarted() const;
    bool isDetach() const;
    void detach();
    void join();
    void setListener(fd_set *fdset, int &max) const;
};

#endif /* !SOCKET_HH_ */

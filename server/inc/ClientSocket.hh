//
// ClientSocket.hh for client socket in /Users/leandr_g/Documents/Shared folder/IndieStudio/server/inc/
//
// Made by Gaëtan Léandre
// Login   <gaetan.leandre@epitech.eu>
//
// Started on  Wed May 24 12:38:53 2017 Gaëtan Léandre
// Last update Fri May 26 00:31:27 2017 Gaëtan Léandre
//

#ifndef             CLIENTSOCKET_HH__
#define             CLIENTSOCKET_HH__

#include            "Socket.hh"

class ClientSocket : public Socket{
public:
    ClientSocket ();
    virtual ~ClientSocket ();
    ClientSocket(ClientSocket &obj);
    ClientSocket    &operator=(ClientSocket &obj);
    bool accept(SOCKET fd);
};

#endif /* !CLIENTSOCKET_HH__ */

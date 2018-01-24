//
// ServerSocket.hh for serverSocket in /Users/leandr_g/Documents/Shared folder/IndieStudio/server/inc/
//
// Made by Gaëtan Léandre
// Login   <gaetan.leandre@epitech.eu>
//
// Started on  Thu May 25 02:33:34 2017 Gaëtan Léandre
// Last update Fri May 26 02:50:34 2017 Gaëtan Léandre
//

#ifndef         SERVERSOCKET_HH_
#define         SERVERSOCKET_HH_

#include        "GameManager.hh"

class ServerSocket : public Socket {
private:
    int _port;
    int _maxConnection;
    GameManager _game;

public:
    ServerSocket (int port = 1234, int maxConnection = 100);
    virtual ~ServerSocket ();
    ServerSocket(ServerSocket &obj);
    ServerSocket    &operator=(ServerSocket &obj);
    bool init();
    void launchLoop();
    int getPort() const;
    void setPort(int port);
    int getMaxConnection() const;
    void setMaxConnection(int maxConnection);
    void stop();
};

#endif /* !SERVERSOCKET_HH_ */

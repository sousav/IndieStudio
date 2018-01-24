//
// Client.hh for client in /Users/leandr_g/Documents/Shared folder/IndieStudio/server/inc/
//
// Made by Gaëtan Léandre
// Login   <gaetan.leandre@epitech.eu>
//
// Started on  Wed May 24 15:49:09 2017 Gaëtan Léandre
// Last update Fri May 26 02:09:36 2017 Gaëtan Léandre
//

#ifndef         CLIENT_HH_
#define         CLIENT_HH_

#include        "ClientSocket.hh"

class Client {
private:
    ClientSocket _sock;
    int _money;
    int _id;
    int _car_no;

public:
    Client ();
    virtual ~Client ();
    Client(Client const &obj);
    Client    &operator=(Client const &obj);
    ClientSocket const &getSocket() const;
    void setSocket(ClientSocket &socket);
    int getMoney() const;
    void setMoney(int money);
    int getId() const;
    void setId(int id);
    int getCarNo() const;
    void setCarNo(int no);
    bool accept(SOCKET fd);
    std::string read();
    void write(std::string const &str);
};

#endif /* !Client */

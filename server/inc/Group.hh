//
// Group.hh for group in /Users/leandr_g/Documents/Shared folder/IndieStudio/server/inc/
//
// Made by Gaëtan Léandre
// Login   <gaetan.leandre@epitech.eu>
//
// Started on  Fri May 26 03:51:20 2017 Gaëtan Léandre
// Last update Fri May 26 04:10:04 2017 Gaëtan Léandre
//

#ifndef                 GROUP
#define                 GROUP

#include                <unordered_map>
#include                "Client.hh"

class Group {
protected:
    std::unordered_map<int, Client *> _clients;

public:
    Group();
    virtual ~Group();
    Group(const Group &obj);
    Group    &operator=(const Group &obj);
    virtual void writeAll(std::string const &str);
    virtual void writeAllExeptById(std::string const &str, int id);
    virtual void writeAllExeptByFd(std::string const &str, int fd);
    virtual bool foundClientById(int id);
    virtual bool foundClientByFd(int fd);
    virtual void addClient(Client *client);
    virtual int getClientNumber() const;
    virtual bool deleteClientById(int id);
    virtual bool deleteClientByFd(int fd);
};

#endif /* !GROUP */

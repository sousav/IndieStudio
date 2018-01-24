//
// Message.hh for message in /Users/leandr_g/Documents/Shared folder/IndieStudio/server/inc/
//
// Made by Gaëtan Léandre
// Login   <gaetan.leandre@epitech.eu>
//
// Started on  Wed May 24 12:45:26 2017 Gaëtan Léandre
// Last update Wed Jun  7 11:57:53 2017 Gaëtan Léandre
//

#ifndef             MESSAGE_HH_
#define             MESSAGE_HH_

#include            <string>
#include            <vector>
#include            <iostream>
#include            <unordered_map>

class Message {
private:
    std::string _title;
    std::vector<Message> _subSession;
    std::unordered_map<std::string, std::string> _content;
    std::string getFirstComment(std::string &str) const;
    std::string getFirstParam(std::string &str) const;
    bool isObject(std::string const &str) const;
    void parseContent(std::string str);

public:
    explicit Message (std::string const &title);
    virtual ~Message ();
    Message(const Message &obj);
    Message     &operator=(const Message &obj);
    Message     &operator[](std::string const &pos);
    std::string &operator()(std::string const &pos);
    std::vector<std::string> getSubSessions();
    std::vector<std::string> getContents();
    void deleteContent(std::string const &pos);
    void deleteSubSession(std::string const &pos);
    std::string const &getTitle() const;
    void setTitle(std::string const &title);
    Message &addSubSession(Message const &subSession);
    std::string &addContent(std::string const &title, std::string const &content);
    std::string getJSON() const;
    std::string _getJSON() const;
    void parseJSON(std::string const &str);
    bool empty() const;
};

#endif /* !MESSAGE_HH_ */

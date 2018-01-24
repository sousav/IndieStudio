//
// Message.cpp for message in /Users/leandr_g/Documents/Shared folder/IndieStudio/server/src/
//
// Made by Gaëtan Léandre
// Login   <gaetan.leandre@epitech.eu>
//
// Started on  Wed May 24 13:00:34 2017 Gaëtan Léandre
// Last update Wed Jun  7 11:57:16 2017 Gaëtan Léandre
//

#include                "Message.hh"

Message::Message(std::string const &title)
{
    this->_title = title;
}

Message::~Message()
{
}

Message::Message(const Message &obj)
{
    this->_title = obj._title;
    this->_subSession = obj._subSession;
    this->_content = obj._content;
}

Message     &Message::operator=(const Message &obj)
{
    this->_title = obj._title;
    this->_subSession = obj._subSession;
    this->_content = obj._content;
    return (*this);
}

Message     &Message::operator[](std::string const &pos)
{
    for (auto &x: this->_subSession)
    {
        if (x.getTitle() == pos)
            return (x);
    }
    return (this->addSubSession(Message(pos)));
}

std::string &Message::operator()(std::string const &pos)
{
    if (this->_content.count(pos) <= 0)
        this->_content[pos] = "";
    return (this->_content[pos]);
}

std::vector<std::string> Message::getSubSessions()
{
    std::vector<std::string> sub;
    for (auto &x: this->_subSession)
    {
        sub.push_back(x.getTitle());
    }
    return (sub);
}

std::vector<std::string> Message::getContents()
{
    std::vector<std::string> cont;
    for (auto &x: this->_content)
    {
        cont.push_back(x.first);
    }
    return (cont);
}

std::string const &Message::getTitle() const
{
    return (this->_title);
}

void Message::setTitle(std::string const &title)
{
    this->_title = title;
}

Message &Message::addSubSession(Message const &subSession)
{
    this->_subSession.push_back(subSession);
    return (this->_subSession[this->_subSession.size() - 1]);
}

std::string &Message::addContent(std::string const &title, std::string const &content)
{
    this->_content[title] = content;
    return (this->_content[title]);
}

std::string Message::_getJSON() const
{
    std::string result;
    int i;

    i = 0;
    result += "{\"";
    result += this->_title;
    result += "\":";
    for (auto x: this->_subSession)
    {
        if (i != 0)
            result += ",";
        result += x._getJSON();
        i++;
    }
    for (auto y: this->_content)
    {
        if (i != 0)
            result += ",";
        result += "{\"";
        result += y.first;
        result += "\":\"";
        result += y.second;
        result += "\"}";
        i++;
    }
    result += "}";
    return (result);
}

std::string Message::getJSON() const
{
    return (_getJSON() + "|");
}

std::string Message::getFirstComment(std::string &str) const
{
    std::size_t foundStart;
    std::size_t foundEnd;
    std::string phrase;
    std::string tmp;

    foundStart = str.find("\"");
    if (foundStart != std::string::npos)
        foundEnd = str.find("\"", foundStart + 1);
    if (foundStart != std::string::npos && foundEnd != std::string::npos)
    {
        phrase = str.substr(foundStart + 1, foundEnd - foundStart - 1);
        tmp = str.substr(0, foundStart);
        tmp += str.substr(foundEnd + 1, str.size() - foundEnd);
        str = tmp;
    }
    else
        phrase = std::string("");
    return (phrase);
}

std::string Message::getFirstParam(std::string &str) const
{
    std::size_t foundStart;
    std::string phrase("");
    std::string tmp;
    int pos = 0;
    int i = 0;
    bool tild = false;

    foundStart = str.find("{");
    if (foundStart != std::string::npos)
    {
        for (i = foundStart; i < str.size(); i++)
        {
            if (str[i] == '{' && tild == false)
                pos++;
            else if (str[i] == '}' && tild == false)
                pos--;
            else if (str[i] == '\"')
                tild = !tild;
            if (pos == 0)
                break;
        }
        if (pos == 0)
        {
            phrase = str.substr(foundStart, i - foundStart + 1);
            tmp = str.substr(0, foundStart);
            tmp += str.substr(i + 1, str.size() - i);
            str = tmp;
        }
    }
    return (phrase);
}

bool Message::isObject(std::string const &str) const
{
    for (int i = 1; i < str.size() - 1; i++)
    {
        if (str[i] == '{' || str[i] == '}')
            return (true);
    }
    return (false);
}

void Message::parseContent(std::string str)
{
    std::string first = getFirstComment(str);
    std::string second = getFirstComment(str);

    addContent(first, second);
}

void Message::parseJSON(std::string const &str)
{
    std::string phrase;
    std::string tmp;
    std::size_t foundStart;
    std::size_t foundEnd;

    foundStart = str.find("{");
    foundEnd = str.find_last_of("}");
    if (foundStart != std::string::npos && foundEnd != std::string::npos)
    {
        phrase = str.substr(foundStart + 1, foundEnd - foundStart - 1);
        this->_title = getFirstComment(phrase);
        while ((tmp = getFirstParam(phrase)).size() != 0)
        {
            if (isObject(tmp))
                addSubSession(Message("")).parseJSON(tmp);
            else
                parseContent(tmp);
        }
    }
}

bool Message::empty() const
{
    for (auto &x: this->_subSession)
    {
        if (x.empty() == false)
            return (false);
    }

    for (auto &y: this->_content)
    {
        if (y.second.size() != 0)
            return (false);
    }
    return (true);
}

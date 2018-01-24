//
// Client.cpp for Client in /Users/leandr_g/Documents/Shared folder/IndieStudio/sources/
//
// Made by Gaëtan Léandre
// Login   <gaetan.leandre@epitech.eu>
//
// Started on  Tue Jun  6 21:50:28 2017 Gaëtan Léandre
// Last update Thu Jun 15 23:18:36 2017 Sousa Victor
//

#include                "Client.hpp"

using namespace indie;

Client Client::_instance = Client();

Client::Client(std::string const &ip, int port)
{
    this->_ip = ip;
    this->_port = port;
    this->_id = "-1";
}

Client::~Client()
{

}

Client::Client(const Client &obj)
{
    //this->_client = obj._client;
}

Client &Client::operator=(const Client &obj)
{
    //this->_client = obj._client;
    return (*this);
}

Client &Client::Instance() {
    return _instance;
}

void Client::init(NetworkEventBridge *bridge) {
    this->_bridge = bridge;
    this->_client.connect("http://" + this->_ip + ":" + std::to_string(this->_port));
    this->parseID();
    this->SetupCallback();
    this->requestMoney();
}

void Client::SetupCallback() {
    this->_client.socket()->on("give your id", sio::socket::event_listener_aux([&](std::string const& name, sio::message::ptr const& data, bool isAck, sio::message::list &ack_resp)
    {
        this->_client.socket()->emit("id client is", "{\"id\": \"" + this->_id + "\"}");
    }));

    this->_client.socket()->on("change id", sio::socket::event_listener_aux([&](std::string const& name, sio::message::ptr const& data, bool isAck, sio::message::list &ack_resp)
    {
        this->setId(data->get_map()["new_id"]->get_string());
        this->_shortId = data->get_map()["short_id"]->get_string();
        this->requestMoney();
    }));

    this->_client.socket()->on("connected_to", sio::socket::event_listener_aux([&](std::string const& name, sio::message::ptr const& data, bool isAck, sio::message::list &ack_resp)
    {
        this->_bridge->addEvent(name, data);
    }));

    this->_client.socket()->on("send pos", sio::socket::event_listener_aux([&](std::string const& name, sio::message::ptr const& data, bool isAck, sio::message::list &ack_resp)
    {
        this->_bridge->addEvent(name, data);
    }));

    this->_client.socket()->on("send engine", sio::socket::event_listener_aux([&](std::string const& name, sio::message::ptr const& data, bool isAck, sio::message::list &ack_resp)
    {
        this->_bridge->addEvent(name, data);
    }));

    this->_client.socket()->on("add car", sio::socket::event_listener_aux([&](std::string const& name, sio::message::ptr const& data, bool isAck, sio::message::list &ack_resp)
    {
        this->_bridge->addEvent(name, data);
    }));

    this->_client.socket()->on("delete car", sio::socket::event_listener_aux([&](std::string const& name, sio::message::ptr const& data, bool isAck, sio::message::list &ack_resp)
    {
        this->_bridge->addEvent(name, data);
    }));

    this->_client.socket()->on("join race", sio::socket::event_listener_aux([&](std::string const& name, sio::message::ptr const& data, bool isAck, sio::message::list &ack_resp)
    {
        this->_bridge->addEvent(name, data);
    }));

    this->_client.socket()->on("leave race", sio::socket::event_listener_aux([&](std::string const& name, sio::message::ptr const& data, bool isAck, sio::message::list &ack_resp)
    {
        this->_bridge->addEvent(name, data);
    }));

    this->_client.socket()->on("error message", sio::socket::event_listener_aux([&](std::string const& name, sio::message::ptr const& data, bool isAck, sio::message::list &ack_resp)
    {
        this->_bridge->addEvent(name, data);
    }));

    this->_client.socket()->on("get money", sio::socket::event_listener_aux([&](std::string const& name, sio::message::ptr const& data, bool isAck, sio::message::list &ack_resp)
    {
        this->_money = data->get_map()["money"]->get_int();
    }));

    this->_client.socket()->on("add checkpoint", sio::socket::event_listener_aux([&](std::string const& name, sio::message::ptr const& data, bool isAck, sio::message::list &ack_resp)
    {
        this->_bridge->addEvent(name, data);
    }));

    this->_client.socket()->on("start race", sio::socket::event_listener_aux([&](std::string const& name, sio::message::ptr const& data, bool isAck, sio::message::list &ack_resp)
    {
        this->_bridge->addEvent(name, data);
    }));

    this->_client.socket()->on("add race ai", sio::socket::event_listener_aux([&](std::string const& name, sio::message::ptr const& data, bool isAck, sio::message::list &ack_resp)
    {
        this->_bridge->addEvent(name, data);
    }));
}

void Client::stop() {
    this->_client.sync_close();
    this->_client.clear_con_listeners();
}

void Client::parseID() {
    std::string id = "-1";
    std::ifstream infile((std::string(SOURCES_PATH) + std::string("/Data/id.txt")).c_str());

    if (infile >> id) {
        if (id != "-1") {
            this->_id = id;
        }
    }
}

void Client::joinId(const wchar_t *dest_id) {
    rapidjson::Document d;
    d.SetObject();
    rapidjson::Value v(rapidjson::kObjectType);

    v.SetString(this->_id.c_str(), static_cast<rapidjson::SizeType>(this->_id.length()), d.GetAllocator());
    d.AddMember("id", v, d.GetAllocator());

    std::wstring ws(dest_id);
    std::string dest(ws.begin(), ws.end());
    v.SetString(dest.c_str(), static_cast<rapidjson::SizeType>(dest.length()), d.GetAllocator());
    d.AddMember("dest", v, d.GetAllocator());

    this->_client.socket()->emit("joining someone", this->getString(d));
}

void Client::sendPosAndRota(irr::core::vector3df const &pos, irr::core::vector3df const &rot, std::string const &short_id) {
    rapidjson::Document d;
    d.SetObject();
    rapidjson::Value v(rapidjson::kObjectType);

    std::string id = this->_shortId;
    if (short_id != "-1")
        id = short_id;

    v.SetString(id.c_str(), static_cast<rapidjson::SizeType>(id.length()), d.GetAllocator());
    d.AddMember("short_id", v, d.GetAllocator());

    v.SetString(this->_id.c_str(), static_cast<rapidjson::SizeType>(this->_id.length()), d.GetAllocator());
    d.AddMember("id", v, d.GetAllocator());

    rapidjson::Value v1(pos.X);

    d.AddMember("posX", v1, d.GetAllocator());
    v1 = rapidjson::Value(pos.Y);
    d.AddMember("posY", v1, d.GetAllocator());
    v1 = rapidjson::Value(pos.Z);
    d.AddMember("posZ", v1, d.GetAllocator());

    v1 = rapidjson::Value(rot.X);
    d.AddMember("rotX", v1, d.GetAllocator());
    v1 = rapidjson::Value(rot.Y);
    d.AddMember("rotY", v1, d.GetAllocator());
    v1 = rapidjson::Value(rot.Z);
    d.AddMember("rotZ", v1, d.GetAllocator());

    this->_client.socket()->emit("send pos", this->getString(d));
}

void Client::sendEngineData(irr::core::vector3df const &vel, irr::core::vector3df const &ang, float engine, float breaking, float steering, std::string const &short_id) {
    rapidjson::Document d;
    d.SetObject();
    rapidjson::Value v(rapidjson::kObjectType);
    rapidjson::Value v1(engine);
    std::string id = this->_shortId;
    if (short_id != "-1")
        id = short_id;
    v.SetString(id.c_str(), static_cast<rapidjson::SizeType>(id.length()), d.GetAllocator());
    d.AddMember("short_id", v, d.GetAllocator());
    v.SetString(this->_id.c_str(), static_cast<rapidjson::SizeType>(this->_id.length()), d.GetAllocator());
    d.AddMember("id", v, d.GetAllocator());
    v1 = rapidjson::Value(engine);
    d.AddMember("engine", v1, d.GetAllocator());
    v1 = rapidjson::Value(breaking);
    d.AddMember("breaking", v1, d.GetAllocator());
    v1 = rapidjson::Value(steering);
    d.AddMember("steering", v1, d.GetAllocator());
    v1 = rapidjson::Value(vel.X);
    d.AddMember("LinearX", v1, d.GetAllocator());
    v1 = rapidjson::Value(vel.Y);
    d.AddMember("LinearY", v1, d.GetAllocator());
    v1 = rapidjson::Value(vel.Z);
    d.AddMember("LinearZ", v1, d.GetAllocator());
    v1 = rapidjson::Value(ang.X);
    d.AddMember("AngularX", v1, d.GetAllocator());
    v1 = rapidjson::Value(ang.Y);
    d.AddMember("AngularY", v1, d.GetAllocator());
    v1 = rapidjson::Value(ang.Z);
    d.AddMember("AngularZ", v1, d.GetAllocator());

    this->_client.socket()->emit("send engine", this->getString(d));
}

void Client::creatingCourseLobby(irr::s32 const &id) {
    rapidjson::Document d;
    d.SetObject();
    rapidjson::Value v(rapidjson::kObjectType);
    rapidjson::Value v1(id);

    v.SetString(this->_id.c_str(), static_cast<rapidjson::SizeType>(this->_id.length()), d.GetAllocator());
    d.AddMember("id", v, d.GetAllocator());
    d.AddMember("race_id", v1, d.GetAllocator());
    this->_client.socket()->emit("create race", this->getString(d));

}

void Client::leavingCourseLobby() {
    rapidjson::Document d;
    d.SetObject();
    rapidjson::Value v(rapidjson::kObjectType);

    v.SetString(this->_id.c_str(), static_cast<rapidjson::SizeType>(this->_id.length()), d.GetAllocator());
    d.AddMember("id", v, d.GetAllocator());
    this->_client.socket()->emit("leave race", this->getString(d));
}

void Client::endRace(std::string const & id) {
    this->_client.socket()->emit("end race", "{\"short_id\": \"" + id + "\"}");
}

void Client::setId(std::string const & id) {
    std::ofstream infile((std::string(SOURCES_PATH) + std::string("/Data/id.txt")).c_str());

    infile << id;
    this->_id = id;
}

std::string const & Client::getId() const {
    return this->_id;
}

std::string const & Client::getShortId() const {
    return this->_shortId;
}

int Client::getMoney() const {
    return this->_money;
}

void Client::setCarNo(int no) {
    this->_client.socket()->emit("carNum changed", "{\"id\": \"" + this->_id + "\", \"nbr\": \"" + std::to_string(no) + "\"}");
}

void Client::addMoney(int nb) {
    this->_client.socket()->emit("add money", "{\"id\": \"" + this->_id + "\", \"nbr\": \"" + std::to_string(nb) + "\"}");
}

void Client::requestMoney() {
    this->_client.socket()->emit("get money", "{\"id\": \"" + this->_id + "\"}");
}

void Client::startingRace() {
    this->_client.socket()->emit("starting race", "{\"id\": \"" + this->_id + "\"}");
}

void Client::debug(std::string const &msg) {
    this->_client.socket()->emit("debug", "{\"msg\": \"" + msg + "\"}");
}

std::string const Client::getString(rapidjson::Document const &d) {
    rapidjson::StringBuffer buffer;
    buffer.Clear();
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    d.Accept(writer);
    std::string json = buffer.GetString();
    return json;
}

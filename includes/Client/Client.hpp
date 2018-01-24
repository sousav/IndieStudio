//
// Client.hpp for client in /Users/leandr_g/Documents/Shared folder/IndieStudio/includes/
//
// Made by Gaëtan Léandre
// Login   <gaetan.leandre@epitech.eu>
//
// Started on  Tue Jun  6 21:51:52 2017 Gaëtan Léandre
// Last update Thu Jun 15 23:18:28 2017 Sousa Victor
//

#ifndef             CLIENT_HPP
#define             CLIENT_HPP

#include <fstream>
#include <sstream>
#include "sio_socket.h"
#include "sio_client.h"
#include "rapidjson.h"
#include "document.h"
#include "stringbuffer.h"
#include "writer.h"

#include "NetworkEventBridge.hpp"
#include "EventReceiver.hpp"
#include "IndieStudioConfig.h"


namespace indie {

    class Client {
    private:
        static Client _instance;
        sio::client _client;
        std::string _ip;
        int _port;
        std::string _id;
        std::string _shortId;
        int _money;
        NetworkEventBridge *_bridge;


        void SetupCallback();
        void parseID();

    public:
        //37.187.8.132
        explicit Client (std::string const &ip = "37.187.8.132", int port = 3000);
        virtual ~Client ();
        Client(const Client &obj);
        Client &operator=(const Client &obj);
        static Client &Instance();
        void init(NetworkEventBridge *bridge);
        void stop();

        void setId(std::string const & id);
        std::string const & getId() const;
        std::string const & getShortId() const;
        int getMoney() const;

        void addMoney(int nb);
        void requestMoney();
        void joinId(const wchar_t *dest_id);
        void sendPosAndRota(irr::core::vector3df const &pos, irr::core::vector3df const &rot, std::string const &short_id = "-1");
        void sendEngineData(irr::core::vector3df const &vel, irr::core::vector3df const &ang, float engine, float breaking, float steering, std::string const &short_id = "-1");
        void creatingCourseLobby(irr::s32 const &id);
        void leavingCourseLobby();
        void setCarNo(int no);
        void startingRace();
        void endRace(std::string const & id);
        void debug(std::string const &msg);

        std::string const getString(rapidjson::Document const &d);

    };

}

#else

#endif /* !CLIENT_HPP */

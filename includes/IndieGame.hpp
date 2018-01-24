//
// IndieGame.hpp for  in /Users/vicostudio/Documents/Shared/TEK2/CPP/cpp_indie_studio/includes/
//
// Made by Sousa Victor
// Login   <sousa_v@epitech.eu>
//
// Started on  Sun May  7 05:42:36 2017 Sousa Victor
// Last update Sun Jun 18 21:23:37 2017 Sousa Victor
//

#ifndef INDIEGAME_HPP
#define INDIEGAME_HPP

#include <thread>
#include <sstream>
#include <iomanip>
#include <vector>
#include <unordered_map>
#include <random>
#include <irrKlang.h>
#include "AGame.hpp"
#include "GameCameraFPS.hpp"
#include "GameCheckpoint.hpp"
#include "Minimap.hpp"
#include "Car.hpp"
#include "Race.hpp"
#include "GeneticTrainer.hpp"
#include "carWatcher.hpp"
#include "Settings.hpp"
#include "Garage.hpp"
#include "Menu.hpp"
#include "Course.hpp"
#include "RandomEvent.hpp"
#include "Audio.hpp"
#include "Keyboard.hpp"
#include "Graphic.hpp"
#include "JoinServer.hpp"
#include "NetworkEventBridge.hpp"
#include "Classement.hpp"
#include "MainMenu.hpp"
#include "Concessionnaire.hpp"
#include "Client.hpp"
#include "NetworkCar.hpp"
#include "SoundManager.hpp"
#include "KeyboardManager.hpp"

namespace indie {

    class IndieGame: public AGame, public NetworkEventBridge {

    public:
        IndieGame(int width = 1920, int height = 1080);
        ~IndieGame();

        virtual void OnFrame();
        virtual bool OnEvent(const irr::SEvent& event);

    private:
        void addGameObject();
        void addEventReceiver();

        void loadMap();

        virtual void OnEnterKey(irr::EKEY_CODE keyCode);
        virtual void OnReleaseKey(irr::EKEY_CODE keyCode);
        virtual void OnEnterGarage(void);
        virtual void OnLeavingGarage(void);

        virtual void OnOpenningMenu();
        virtual void OnLeavingMenu();

        virtual void OnEnterCourse(GameCheckpoint const &ch);
        virtual void OnLeavingCourse();
        virtual void OnEnterMoney();
        virtual void OnEnterOnline();
        virtual void OnLeavingOnline();
        virtual void OnEnterConcess();
        virtual void OnLeavingConcess();

        virtual void guiVisible(IGUI*);
        virtual void launchMenu();
        virtual void launchSplash();

        void updateCarsData(sio::message::ptr const &msg);
        void updateCarsPosition(sio::message::ptr const &msg);
        void addNetworkCar(sio::message::ptr const &msg);
        void deleteNetworkCar(sio::message::ptr const &msg);
        void changeCarColor();

    private:

        void joinRace(sio::message::ptr const &msg);
        void leaveRace(sio::message::ptr const &msg);
        void addRaceAi(sio::message::ptr const &msg);
        void writeResolution(int x, int y);

        bool _multi;
        Car *_car;
        Car *_car2;
        std::unordered_map<std::string, NetworkCar *> _cars;
        Car *_aiCar;
        GeneticTrainer *_genTrainer;
        std::vector<GameCheckpoint> _checkpoints;
        carWatcher *_carWatch;
        Garage *_garage;
        Menu *_menu;
        Course *_course;
        Race *_race;
        RandomEvent *_events;
        Settings *_settings;
        JoinServer *_onlineUI;
        MainMenu *_mainmenu;
        Concessionnaire *_concessionnaire;

        irr::gui::IGUIImage *_splash;
        irr::f32 _splashCt;

        irr::f32 _getMoneyCt;

        physics::CBulletPhysics* bulletPhysSys;
        physics::SPhysicsParams physicsParams;

        std::vector<IGUI*> _guiVisible;

        std::string _connectedTo;

        irr::gui::IGUIStaticText *_error;
        irr::f32 _errorTimer;
    };

}

#else

namespace indie {
    class IGame;
    class IndieGame : public AGame;
}

#endif /*INDIEGAME_HPP*/

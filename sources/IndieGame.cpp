//
// IndieGame.cpp for  in /Users/vicostudio/Documents/Shared/TEK2/CPP/cpp_indie_studio/sources/
//
// Made by Sousa Victor
// Login   <sousa_v@epitech.eu>
//
// Started on  Sun May  7 05:48:01 2017 Sousa Victor
// Last update Sun Jun 18 21:39:57 2017 Sousa Victor
//

#include "IndieGame.hpp"

using namespace indie;

IndieGame::IndieGame(int width, int height) : AGame(width, height) {
    this->bulletPhysSys = NULL;
    this->_mainmenu = NULL;
    this->_error = NULL;
    this->_car = NULL;
    this->_connectedTo = "-1";
    this->_race = NULL;
    this->_splash = NULL;
    this->_menu = NULL;
    this->_errorTimer = 0;
    this->_splashCt = 0;
    this->_multi = false;
}

IndieGame::~IndieGame() {
}

void IndieGame::addGameObject() {
    bulletPhysSys = new physics::CBulletPhysics();
	if (bulletPhysSys->Create() == false) {
		printf("bullet init failed..");
	}

    irr::scene::ISceneNode* skydome = this->_smgr->addSkyDomeSceneNode(this->_driver->getTexture("skybox/Skydome1.png"),16,8,0.95f,2.0f);
    this->_driver->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, true);

    loadMap();

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0.0, 7.0);
    if (this->_multi) {
        this->_car = new Car(this->_smgr, this->_gui, this, bulletPhysSys, Circuit(), dist(mt), irr::core::vector3df(-5, 40, 0), false, 1);
        this->_objectList.push_back(this->_car);
        this->_cameraList.push_back(this->_car->getCamera());

        this->_car2 = new Car(this->_smgr, this->_gui, this, bulletPhysSys, Circuit(), dist(mt), irr::core::vector3df(-15, 40, 0), false, 2);
        this->_objectList.push_back(this->_car2);
        this->_cameraList.push_back(this->_car2->getCamera());

    } else {
        this->_car = new Car(this->_smgr, this->_gui, this, bulletPhysSys, Circuit(), dist(mt), irr::core::vector3df(-5, 40, 0), false, -1);
        this->_objectList.push_back(this->_car);
        this->_cameraList.push_back(this->_car->getCamera());
    }

    if (this->_multi == false) {
        int j = 1;
        this->_checkpoints.push_back(GameCheckpoint(this->_smgr, 3, 0, NULL, j++, GameCheckpoint::COURSE, 10, irr::core::vector3df(558.102905, 0, 1.411877)));
        this->_checkpoints.push_back(GameCheckpoint(this->_smgr, 3, 0, NULL, j++, GameCheckpoint::CONCESSIONNAIRE, 7, irr::core::vector3df(588.3, 0, -261.0)));
        this->_checkpoints.push_back(GameCheckpoint(this->_smgr, 3, 0, NULL, j++, GameCheckpoint::ONLINE, 10, irr::core::vector3df(313.75, 0, -215.9)));
        this->_checkpoints.push_back(GameCheckpoint(this->_smgr, 3, 0, NULL, j++, GameCheckpoint::GARAGE, 5, irr::core::vector3df(300.840912, 0, 270.575653)));

        this->_carWatch = new carWatcher(this->_car, this->_checkpoints, this, this->_smgr);
        this->_objectList.push_back(this->_carWatch);

        this->_events = new RandomEvent(this->_smgr, this->_carWatch);
        this->_objectList.push_back(this->_events);

        Minimap *map = new Minimap(this->_smgr, NULL, -1, this->_car, this->_carWatch, this->_driver, this->_device, this->_gui, this->getWindowSize());
        this->_objectList.push_back(map);
    }

    irr::scene::ILightSceneNode *sun_node;
    irr::video::SLight sun_data;
    sun_node = this->_smgr->addLightSceneNode();
    sun_data.Direction = irr::core::vector3df(0, 0, 0);
    sun_data.Type = irr::video::ELT_DIRECTIONAL;
    sun_data.AmbientColor = irr::video::SColorf(0.1f, 0.1f, 0.1f, 1);
    sun_data.SpecularColor = irr::video::SColorf(0.4f, 0.4f, 0.4f, 1);
    sun_data.DiffuseColor = irr::video::SColorf(1.0f, 1.0f, 1.0f, 1);
    sun_data.CastShadows = true;
    sun_node->setLightData(sun_data);
    sun_node->setPosition(irr::core::vector3df(0, 0, 0));
    sun_node->setRotation(irr::core::vector3df(0, 0, 0));
    this->_smgr->setAmbientLight(irr::video::SColorf(1.85, 1.85, 2, 2.5));

    this->_garage = NULL;
    this->_menu = NULL;
    this->_course = NULL;
    this->_onlineUI = NULL;
    this->_concessionnaire = NULL;

    this->_error = this->_gui->addStaticText(L"Error Message", irr::core::rect<irr::s32>(300, 300, this->getWindowSize().Width - 300, this->getWindowSize().Height / 2.5));
    irr::gui::IGUIFont* font = this->_gui->getFont("misc/error.xml");
    if (font)
        this->_error->setOverrideFont(font);
    this->_error->setOverrideColor(irr::video::SColor(255, 255, 0, 0));
    this->_error->setTextAlignment(irr::gui::EGUIA_CENTER, irr::gui::EGUIA_CENTER);
    this->_error->setVisible(false);
}

void IndieGame::loadMap() {
    irr::scene::IMesh* mesh_road = this->_smgr->getMesh(std::string("BigCity/BigCityRoad_1.obj").c_str());
    irr::scene::IMeshSceneNode *node_road = this->_smgr->addOctreeSceneNode(mesh_road, 0, -1);
    node_road->setMaterialFlag(irr::video::EMF_LIGHTING, true);
    bulletPhysSys->AddMeshSceneNode(node_road, node_road->getMesh(), true);


    irr::scene::IMesh* mesh_road2 = this->_smgr->getMesh(std::string("BigCity/BigCityRoad_2.obj").c_str());
    irr::scene::IMeshSceneNode *node_road2 = this->_smgr->addOctreeSceneNode(mesh_road2, 0, -1);
    node_road2->setMaterialFlag(irr::video::EMF_LIGHTING, true);
    bulletPhysSys->AddMeshSceneNode(node_road2, node_road2->getMesh(), true);

    #ifndef DEBUG
        irr::scene::IMesh* mesh1 = this->_smgr->getMesh(std::string("BigCity/BigCity_1.obj").c_str());
        irr::scene::IMeshSceneNode *node1 = this->_smgr->addOctreeSceneNode(mesh1, 0, -1);
        node1->setMaterialFlag(irr::video::EMF_LIGHTING, true);
        bulletPhysSys->AddMeshSceneNode(node1, node1->getMesh(), true);

        irr::scene::IMesh* mesh2 = this->_smgr->getMesh(std::string("BigCity/BigCity_2.obj").c_str());
        irr::scene::IMeshSceneNode *node2 = this->_smgr->addOctreeSceneNode(mesh2, 0, -1);
        node2->setMaterialFlag(irr::video::EMF_LIGHTING, true);
        bulletPhysSys->AddMeshSceneNode(node2, node2->getMesh(), true);
    #endif
}

void IndieGame::addEventReceiver() {
    int i = 0;
    this->_operation["connected_to"] = i++;
    this->_operation["send engine"] = i++;
    this->_operation["send pos"] = i++;
    this->_operation["add car"] = i++;
    this->_operation["delete car"] = i++;
    this->_operation["join race"] = i++; //5
    this->_operation["leave race"] = i++;
    this->_operation["error message"] = i++;
    this->_operation["add checkpoint"] = i++;
    this->_operation["start race"] = i++;
    this->_operation["add race ai"] = i++;
    Client::Instance().init(this);
}

void IndieGame::OnFrame() {

    this->lockEventBuffer();
    for (auto const &str: this->_cmdBuffer) {
        switch (this->_operation[str.first]) {
            case 0:
                this->_connectedTo = str.second->get_map()["connected_to"]->get_string();
                this->_car->mustSendData(true);
                break;
            case 1:
                this->updateCarsData(str.second);
                break;
            case 2:
                this->updateCarsPosition(str.second);
                break;
            case 3:
                this->addNetworkCar(str.second);
                break;
            case 4:
                this->deleteNetworkCar(str.second);
                break;
            case 5:
                this->joinRace(str.second);
                break;
            case 6:
                this->leaveRace(str.second);
                break;
            case 7:
                if (this->_error) {
                    irr::core::stringw _str(L"");
                    _str += str.second->get_map()["error"]->get_string().c_str();
                    _str.replace(' ', ' ');
                    this->_error->setText(_str.c_str());
                    this->_error->setVisible(true);
                    this->_errorTimer = 0;
                }
                break;
            case 8:
                //Add checkpoint
                break;
            case 9:
                this->_race->UnFreezePlayers();
                break;
            case 10:
                this->addRaceAi(str.second);
                break;
            default:
                std::cerr << "Command not found" << std::endl;
                break;
        }
    }
    this->_cmdBuffer.clear();
    this->unlockEventBuffer();

    if (this->_splash) {
        this->_splashCt += DeltaTimer::DeltaTime;
        if (this->_splashCt >= 4) {
            this->launchMenu();
            this->_splash->remove();
            this->_splash = NULL;
            this->_splashCt = 0;
        }
    }

    if (this->_car) {
        std::string str("Your id: #" + Client::Instance().getShortId() + "\nConnected to: " + (this->_connectedTo  == "-1" ? "Nobody" : "#" + this->_connectedTo));
        this->_gui->getSkin()->getFont()->draw(str.data(), core::rect<s32>(20, 20, 200, 75), irr::video::SColor(255, 180, 180, 180));
        if (this->_getMoneyCt >= 5) {
            Client::Instance().requestMoney();
            this->_getMoneyCt = 0;
        } else {
            this->_getMoneyCt += DeltaTimer::DeltaTime;
        }
        str = std::to_string(Client::Instance().getMoney()) + "$";
        this->_gui->getSkin()->getFont()->draw(str.data(), core::rect<s32>(this->getWindowSize().Width - 100, 20, this->getWindowSize().Width, 50), irr::video::SColor(255, 180, 180, 180) );
        std::stringstream s;
        s << std::fixed << std::setprecision(2) << std::abs(this->_car->getVel() - 0.6);
        s << "km/h   " << std::setprecision(0) << this->_car->getRPM() << "rpm   " << this->_car->getGear() << "gear";
        str = s.str();
        this->_gui->getSkin()->getFont()->draw(str.data(), irr::core::rect<irr::s32>(20, this->getWindowSize().Height - 50, 100, 50), irr::video::SColor(255, 180, 180, 180) );
    }



    if (bulletPhysSys)
        bulletPhysSys->OnUpdate(DeltaTimer::DeltaTime * 1000);

    if (this->_error) {
        if (this->_error->isVisible() == true) {
            this->_errorTimer += DeltaTimer::DeltaTime;
            if (this->_errorTimer >= 3) {
                this->_error->setVisible(false);
                this->_errorTimer = 0;
            }
        }
    }

    if (this->_menu && this->_menu->getSettings() && this->_menu->getSettings()->getGraphic() && this->_menu->getSettings()->getGraphic()->isVisible() == true) {
        this->_car->getCamera()->setFarValue(this->_menu->getSettings()->getGraphic()->getText());
    }

}

void IndieGame::updateCarsData(sio::message::ptr const &msg) {
    irr::core::vector3df pos(0, 0, 0);
    auto vec = msg->get_map()["ennemy_info"]->get_vector();
    for (auto const &x : vec) {
        if (this->_cars.count(x->get_map()["short_id"]->get_string()) == 0)
            continue;
        this->_cars[x->get_map()["short_id"]->get_string()]->setEngineForce(x->get_map()["engine"]->get_double());
        this->_cars[x->get_map()["short_id"]->get_string()]->setBreakingForce(x->get_map()["breaking"]->get_double());
        this->_cars[x->get_map()["short_id"]->get_string()]->setSteeringValue(x->get_map()["steering"]->get_double());
        pos.X = x->get_map()["LinearX"]->get_double();
        pos.Y = x->get_map()["LinearY"]->get_double();
        pos.Z = x->get_map()["LinearZ"]->get_double();
        this->_cars[x->get_map()["short_id"]->get_string()]->setLinearVelocity(pos);
        pos.X = x->get_map()["AngularX"]->get_double();
        pos.Y = x->get_map()["AngularY"]->get_double();
        pos.Z = x->get_map()["AngularZ"]->get_double();
        this->_cars[x->get_map()["short_id"]->get_string()]->setAngularVelocity(pos);
    }
}

void IndieGame::updateCarsPosition(sio::message::ptr const &msg) {
    irr::core::vector3df pos(0, 0, 0);
    auto vec = msg->get_map()["ennemy_pos"]->get_vector();
    for (auto const &x : vec) {
        if (this->_cars.count(x->get_map()["short_id"]->get_string()) == 0)
            return;
            pos.X = x->get_map()["posX"]->get_double();
            pos.Y = x->get_map()["posY"]->get_double();
            pos.Z = x->get_map()["posZ"]->get_double();
            this->_cars[x->get_map()["short_id"]->get_string()]->setPosition(pos);
            pos.X = x->get_map()["rotX"]->get_double();
            pos.Y = x->get_map()["rotY"]->get_double();
            pos.Z = x->get_map()["rotZ"]->get_double();
            this->_cars[x->get_map()["short_id"]->get_string()]->setRotation(pos);
        }
}

void IndieGame::addNetworkCar(sio::message::ptr const &msg) {
    if (this->_cars.count(msg->get_map()["car_id"]->get_string()) == 0) {
        NetworkCar *nc = new NetworkCar(this->_smgr, this->_gui, this, bulletPhysSys, Circuit(), msg->get_map()["car_no"]->get_int());
        nc->setShortId(msg->get_map()["car_id"]->get_string());
        this->_cars[msg->get_map()["car_id"]->get_string()] = nc;
        this->_objectList.push_back(nc);
    }
}

void IndieGame::deleteNetworkCar(sio::message::ptr const &msg) {
    for (std::unordered_map<std::string, NetworkCar *>::iterator it = this->_cars.begin(); it != this->_cars.end(); it++) {
        if ((it->first) == msg->get_map()["short_id"]->get_string()) {
            for (auto &obj : this->_objectList) {
                if (obj == it->second) {
                    this->_cars.erase(it);
                    delete obj;
                    obj = NULL;
        		    return;
                }
            }
        }
    }
}

void IndieGame::joinRace(sio::message::ptr const &msg) {
    if (this->_course) {
        if (msg->get_map()["short_id"]->get_string() != "null") {
            this->_course->addPlayer(msg->get_map()["short_id"]->get_string());
            this->_race->push_ennemy(this->_cars[msg->get_map()["short_id"]->get_string()]);
        }
        if (this->_race->getCurrentPlayerAmount() == msg->get_map()["nb_total"]->get_int()) {
            this->_race->setPlayer(this->_car);
            this->_course->addPlayer(Client::Instance().getShortId());
            this->_race->FreezePlayers();
        }
    }
}

void IndieGame::leaveRace(sio::message::ptr const &msg) {
    if (this->_course && msg->get_map()["is_leader"]->get_bool() == true) {
        this->_race->UnFreezePlayers();
        this->_course->setVisible(false);
        for (auto &race : this->_objectList) {
            if (this->_race == race) {
                race = NULL;
                break;
            }
        }
        delete this->_race;
    }
    else if (this->_course)
        this->_course->ripPlayer(msg->get_map()["short_id"]->get_string());
}

void IndieGame::addRaceAi(sio::message::ptr const &msg) {
    if (msg->get_map()["leader"]->get_bool() == false) {
        NetworkCar *nc = new NetworkCar(this->_smgr, this->_gui, this, bulletPhysSys, Circuit(), 0);
        this->_cars[msg->get_map()["short_id"]->get_string()] = nc;
        this->_cars[msg->get_map()["short_id"]->get_string()] = nc;
        this->_objectList.push_back(nc);
    } else {
        this->_race->addAICar(msg->get_map()["short_id"]->get_string());
        this->_race->FreezePlayers();
    }
}

void IndieGame::OnEnterCourse(GameCheckpoint const &ch) {
    if (!this->_course) {
        this->_course = new Course(this->_gui, this->_driver, this->_windowSize);
        this->_course->SetupGUI();
        this->_objectList.push_back(this->_course);
        this->_guiVisible.push_back(this->_course);
    }
    this->_course->setVisible(true);
    this->_device->getCursorControl()->setVisible(true);
    this->guiVisible(this->_course);
    this->_race = new Race(this->_smgr, this->_gui, this, this->bulletPhysSys);
    this->_race->InitCircuit();
    if (this->_connectedTo == "-1") {
        this->_course->addPlayer("You");
        this->_course->addPlayer("IA");
        this->_course->addPlayer("IA");
        this->_course->addPlayer("IA");
        this->_race->addAICar("ai#1");
        this->_race->addAICar("ai#2");
        this->_race->addAICar("ai#3");
        this->_race->setPlayer(this->_car);
        this->_race->FreezePlayers();
    }
    this->_objectList.push_back(this->_race);
    Client::Instance().creatingCourseLobby(ch.getID());
}

void IndieGame::OnLeavingCourse() {
    this->_course->setVisible(false);
    this->_device->getCursorControl()->setVisible(false);
    Client::Instance().leavingCourseLobby();
}

void IndieGame::changeCarColor() {
    this->_car->changeMesh(this->_concessionnaire->getColorIndex());
    Client::Instance().setCarNo(this->_concessionnaire->getColorIndex());
}

void IndieGame::OnEnterGarage(void) {
    if (!this->_garage) {
        this->_garage = new Garage(this->_gui, this->_driver, this->_windowSize);
        this->_garage->SetupGUI();
        this->_objectList.push_back(this->_garage);
        this->_guiVisible.push_back(this->_garage);
    }
    this->_garage->setVisible(true);
    this->_device->getCursorControl()->setVisible(true);
    this->guiVisible(_garage);
}

void IndieGame::OnLeavingGarage(void) {
    this->_garage->setVisible(false);
    this->_device->getCursorControl()->setVisible(false);
}

void IndieGame::OnLeavingMenu() {
    this->_menu->setVisible(false);
    this->_device->getCursorControl()->setVisible(false);
}

void IndieGame::OnOpenningMenu()
{
    if (!this->_menu)
    {
        this->_menu = new Menu(this->_gui, this->_driver, this->_windowSize);
        this->_menu->SetupGUI();
        this->_objectList.push_back(this->_menu);
        this->_guiVisible.push_back(this->_menu);
    }
    if (this->_menu->isVisible() == true) {
        this->_device->getCursorControl()->setVisible(false);
            this->_menu->setVisible(false);
    } else {
        this->_device->getCursorControl()->setVisible(true);
            this->_menu->setVisible(true);
    }
    this->guiVisible(_menu);
}

void IndieGame::launchMenu()
{
    this->_mainmenu = new MainMenu(this->_gui, this->_driver, this->_windowSize);
    this->_mainmenu->SetupGUI();
    irrklang::ISoundEngine* _engine = SoundManager::Instance().getEngine();
    if (_engine)
        _engine->play2D((std::string(SOURCES_PATH) + std::string("/Assets/music/NFSCarbonMenu.ogg")).c_str(), true);
}

void IndieGame::launchSplash()
{
    this->_splash = this->_gui->addImage(this->_driver->getTexture("splash.png"), irr::core::position2d<irr::s32>(0, 0));
}

void IndieGame::OnEnterMoney() {
    Client::Instance().addMoney(200);
    Client::Instance().requestMoney();
}

void IndieGame::OnEnterOnline() {
    if (!this->_onlineUI) {
        this->_onlineUI = new JoinServer(this->_gui, this->_driver, this->_windowSize);
        this->_onlineUI->SetupGUI();
        this->_objectList.push_back(this->_onlineUI);
        this->_guiVisible.push_back(this->_onlineUI);
    }
    this->_onlineUI->setVisible(true);
    this->_device->getCursorControl()->setVisible(true);
    this->guiVisible(_onlineUI);
}

void IndieGame::OnLeavingOnline() {
    this->_onlineUI->setVisible(false);
    this->_device->getCursorControl()->setVisible(false);
}

void IndieGame::OnEnterConcess(void) {
    if (!this->_concessionnaire) {
        this->_concessionnaire = new Concessionnaire(this->_gui, this->_driver, this->_windowSize);
        this->_concessionnaire->SetupGUI();
        this->_objectList.push_back(this->_concessionnaire);
        this->_guiVisible.push_back(this->_concessionnaire);
    }
    this->_concessionnaire->setVisible(true);
    this->_device->getCursorControl()->setVisible(true);
    this->guiVisible(_concessionnaire);
}

void IndieGame::OnLeavingConcess(void) {
    this->_concessionnaire->setVisible(false);
    this->_device->getCursorControl()->setVisible(false);
}

void IndieGame::guiVisible(IGUI *obj)
{
    for (auto & gui : _guiVisible)
    {
        if (gui->isVisible() == true && gui != obj && gui != this->_course) {
            gui->setVisible(false);
        }
    }
}

void IndieGame::OnEnterKey(irr::EKEY_CODE keyCode) {
    if (_mainmenu)
        return;
    switch (keyCode) {
        case irr::KEY_ESCAPE:
            OnOpenningMenu();
            break;
        case irr::KEY_SPACE:
            system(std::string("echo " + std::to_string(this->_smgr->getActiveCamera()->getPosition().X) + ", 0, " + std::to_string(this->_smgr->getActiveCamera()->getPosition().Z) + "    " + std::to_string(this->_car->getRotation().X) + ", " + std::to_string(this->_car->getRotation().Y) + ", " + std::to_string(this->_car->getRotation().Z) + " >> pos").c_str());
            break;
        default:
            break;
    }
    if (this->_menu && this->_menu->getSettings() && this->_menu->getSettings()->getKeyboard() && this->_menu->getSettings()->getKeyboard()->isVisible() == true) {
        this->_menu->getSettings()->getKeyboard()->OnEnterKey(keyCode);
        KeyboardManager::Instance().setMap(this->_menu->getSettings()->getKeyboard()->getMap());
    }
}

void IndieGame::OnReleaseKey(irr::EKEY_CODE keyCode) {
    (void)keyCode;
}

bool IndieGame::OnEvent(const irr::SEvent& event){
    if (event.EventType == irr::EET_GUI_EVENT) {
        irr::s32 id = event.GUIEvent.Caller->getID();
        switch(event.GUIEvent.EventType) {
            case irr::gui::EGET_BUTTON_CLICKED:
                switch(id) {
                    case Garage::REPAIR:
                        //this->_car->repair();
                        break;
                    case Garage::LEAVE:
                        OnLeavingGarage();
                        break;
                    case Menu::SETTING:
                        _menu->OnEnterSetting();
                        this->_objectList.push_back(this->_menu->getSettings());
                        this->_guiVisible.push_back(this->_menu->getSettings());
                        this->guiVisible(this->_menu->getSettings());
                        break;
                   case Settings::GRAPHIC:
                        _menu->getSettings()->OnEnterGraphic();
                        this->_objectList.push_back(this->_menu->getSettings()->getGraphic());
                        this->_guiVisible.push_back(this->_menu->getSettings()->getGraphic());
                        this->guiVisible(this->_menu->getSettings()->getGraphic());
                        break;
                   case Settings::AUDIO:
                        _menu->getSettings()->OnEnterAudio();
                        this->_objectList.push_back(this->_menu->getSettings()->getAudio());
                        this->_guiVisible.push_back(this->_menu->getSettings()->getAudio());
                        this->guiVisible(this->_menu->getSettings()->getAudio());
                        break;
                   case Settings::KEYBOARD:
                        _menu->getSettings()->OnEnterKeyboard();
                        this->_objectList.push_back(this->_menu->getSettings()->getKeyboard());
                        this->_guiVisible.push_back(this->_menu->getSettings()->getKeyboard());
                        this->guiVisible(this->_menu->getSettings()->getKeyboard());
                        break;
                   case Keyboard::KEYBOARD_BTNS::up:
                        _menu->getSettings()->getKeyboard()->resetUp();
                        break;
                   case Keyboard::KEYBOARD_BTNS::down:
                        _menu->getSettings()->getKeyboard()->resetDown();
                        break;
                   case Keyboard::KEYBOARD_BTNS::left:
                        _menu->getSettings()->getKeyboard()->resetLeft();
                        break;
                   case Keyboard::KEYBOARD_BTNS::right:
                        _menu->getSettings()->getKeyboard()->resetRight();
                        break;
                   case Keyboard::KEYBOARD_BTNS::forward:
                        _menu->getSettings()->getKeyboard()->resetForward();
                        break;
                   case Keyboard::KEYBOARD_BTNS::backward:
                        _menu->getSettings()->getKeyboard()->resetBackward();
                        break;
                   case Keyboard::KEYBOARD_BTNS::space:
                        _menu->getSettings()->getKeyboard()->resetBrake();
                        break;
                   case Keyboard::KEYBOARD_BTNS::quit:
                        _menu->getSettings()->getKeyboard()->setVisible(false);
                        break;
                   case Audio::PLUS:
                        _menu->getSettings()->getAudio()->plus();
                        break;
                    case Audio::MOIN:
                        _menu->getSettings()->getAudio()->moin();
                        break;
                    case Menu::RESUME:
                        this->OnLeavingMenu();
                        break;
                    case Menu::QUIT:
                        this->_device->closeDevice();
                        Client::Instance().stop();
                        break;
                    case Concessionnaire::LEAVE:
                        this->_concessionnaire->setVisible(false);
                        break;
                    case Concessionnaire::CHANGEC:
                        this->_concessionnaire->setVisible(false);
                        if (Client::Instance().getMoney() >= 200) {
                            this->changeCarColor();
                            Client::Instance().addMoney(-200);
                        } else {
                            if (this->_error) {
                                irr::core::stringw _str(L"Not enough money to buy this car.");
                                _str.replace(' ', ' ');
                                this->_error->setText(_str.c_str());
                                this->_error->setVisible(true);
                                this->_errorTimer = 0;
                            }
                        }
                        break;
                    case Concessionnaire::QUITC:
                        this->_concessionnaire->setVisible(false);
                        break;
                    case Course::RUN:
                        Client::Instance().startingRace();
                        this->_course->setVisible(false);
                        break;
                    case Course::CANCEL:
                        this->OnLeavingCourse();
                        if (this->_race != NULL) {
                            this->_race->UnFreezePlayers();
                            for (auto &race : this->_objectList) {
                                if (this->_race == race) {
                                    race = NULL;
                                    break;
                                }
                            }
                        }
                        delete this->_race;
                        this->_race = NULL;
                        break;
                    case Audio::Quit:
                        this->_menu->getSettings()->getAudio()->setVisible(false);
                        break;
                    case JoinServer::LEAVE:
                        this->OnLeavingOnline();
                        break;
                    case JoinServer::JOIN:
                        Client::Instance().joinId(this->_onlineUI->getText());
                        this->OnLeavingOnline();
                        break;
                    case MainMenu::PLAY:
                        delete _mainmenu;
                        this->_mainmenu = NULL;
                        addEventReceiver();
                        addGameObject();
                        this->_device->getCursorControl()->setVisible(false);
                        break;
                    case MainMenu::MULTIJOUEUR:
                        delete _mainmenu;
                        this->_mainmenu = NULL;
                        this->_multi = true;
                        addEventReceiver();
                        addGameObject();
                        this->_device->getCursorControl()->setVisible(false);
                        break;
                    case MainMenu::QUIT:
                        this->_device->closeDevice();
                        break;
                    case Graphic::EXIT:
                        this->_menu->getSettings()->getGraphic()->setVisible(false);
                        break;
                    case Graphic::RESOL1:
                        this->writeResolution(640, 480);
                        this->_device->closeDevice();
                        break;
                    case Graphic::RESOL2:
                        this->writeResolution(1280, 720);
                        this->_device->closeDevice();
                        break;
                    case Graphic::RESOL3:
                        this->writeResolution(1920, 1080);
                        this->_device->closeDevice();
                        break;
                    default:
                        break;
                }
            default:
                break;
         }
    }

    return EventReceiver::OnEvent(event);
}

void IndieGame::writeResolution(int x, int y) {
    std::ofstream infile((std::string(SOURCES_PATH) + std::string("/Data/resolution.txt")).c_str());
    infile << std::to_string(x);
    infile << "\n";
    infile << std::to_string(y);
}

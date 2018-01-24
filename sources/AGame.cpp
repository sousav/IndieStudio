//
// AGame.hpp for  in /Users/vicostudio/Documents/Shared/TEK2/CPP/cpp_indie_studio/sources/
//
// Made by Sousa Victor
// Login   <sousa_v@epitech.eu>
//
// Started on  Mon May  8 22:22:15 2017 Sousa Victor
// Last update Sun Jun 18 21:25:40 2017 Sousa Victor
//

#include "AGame.hpp"

using namespace indie;

irr::f32 DeltaTimer::DeltaTime;
AGame::AGame(int width, int height) {
    if (width == -1 || height == -1) {
        std::ifstream infile((std::string(SOURCES_PATH) + std::string("/Data/resolution.txt")).c_str());
        if (infile.is_open() && infile >> width && infile >> height)
            std::cout << "winSize loaded" << std::endl;
        else {
            width = 1920;
            height = 1080;
            std::cerr << "winSize not loaded" << std::endl;
        }

    }
    this->_windowSize = irr::core::dimension2du(width, height);
    SizeS::Instance().Width = width;
    SizeS::Instance().Height = height;

    std::srand(std::time(NULL));
}

AGame::~AGame() {
}


void AGame::Setup() {
    this->_device = irr::createDevice(irr::video::EDT_OPENGL, this->_windowSize, 32, false, false, false, this);
    if (this->_device == 0)
        throw std::exception();

    this->_driver = this->_device->getVideoDriver();
    this->_smgr = this->_device->getSceneManager();
    this->_gui = this->_device->getGUIEnvironment();
    this->_device->getCursorControl()->setVisible(true);

    this->_device->getFileSystem()->addFileArchive((std::string(SOURCES_PATH) + std::string("/Assets/")).c_str());
    irr::gui::IGUISkin* skin = this->_gui->getSkin();
    irr::gui::IGUIFont* font = this->_gui->getFont("misc/try.xml");
    if (font)
        skin->setFont(font);
    this->launchSplash();
}

void AGame::Start() {
    this->_isRunning = true;

    this->loop();

    this->_isRunning = false;
}

void AGame::Clean() {
    this->_device->drop();
}

void AGame::loop() {
    int lastFPS = -1;
    this->_oldTime = this->_device->getTimer()->getTime();
    while(this->_device->run()) {
        processDeltaTime();
        if (this->_device->isWindowActive()) {
            irr::scene::ICameraSceneNode *mainCam = this->_smgr->getActiveCamera();
            this->_driver->setViewPort(irr::core::rect<irr::s32>(0, 0, this->_windowSize.Width, this->_windowSize.Height));
            this->_driver->beginScene(true, true, irr::video::SColor(255,20,20,40));

            for (auto &cam: this->_cameraList) {
                this->_smgr->setActiveCamera(cam->getCamera());
                this->_driver->setViewPort(cam->getViewPort());
                this->_smgr->drawAll();
            }
            this->_driver->setViewPort(irr::core::rect<irr::s32>(0, 0, this->_windowSize.Width, this->_windowSize.Height));

            objectOnFrame();
            this->OnFrame();
            this->_gui->drawAll();
            this->_driver->endScene();
            int fps = this->_driver->getFPS();
            irr::core::stringw str = L"I Don't Car [";
            str += this->_driver->getName();
            str += "] FPS:";
            str += fps;
            this->_device->setWindowCaption(str.c_str());
            lastFPS = fps;
        }
    }
}

void AGame::objectOnFrame() {
    for (auto &obj: this->_objectList) {
        if (obj) {
            obj->OnFrame();
        }
    }
}

irr::core::dimension2du const &AGame::getWindowSize() const {
    return this->_windowSize;
}

bool AGame::isRunning() const {
    return this->_isRunning;
}

bool AGame::OnEvent(const irr::SEvent& event) {
    for (auto &receiver: this->_eventReceiverList) {
        (void)receiver;
    }
    return EventReceiver::OnEvent(event);
}

void AGame::processDeltaTime() {
    const irr::u32 now = this->_device->getTimer()->getTime();
    DeltaTimer::DeltaTime = (irr::f32)(now - this->_oldTime) / 1000.f;
    this->_oldTime = now;
}

/*
** Race.cpp for IndieStudio in /Users/Vacca_J/Epitech/Tek2/Projet/IndieStudio/sources
**
** Made by Vacca_J
** Login   <Vacca_J@epitech.net>
**
** Started on  Thu Jun 01 01:32:46 2017 Vacca_J
** Last update Sun Jun 18 23:07:22 2017 Sousa Victor
*/

#include "Race.hpp"

using namespace indie;

Race::Race(irr::scene::ISceneManager *sceneManager, irr::gui::IGUIEnvironment* guiManager, EventReceiver *eventReceiver, physics::CBulletPhysics *bulletPhysicsSystem):
    AGameObject(sceneManager), _carWatcher(NULL, Circuit().getCheckpoints(), this, sceneManager) {
    this->_gui = guiManager;
    this->_eventReceiver = eventReceiver;
    this->_bulletPhysSys = bulletPhysicsSystem;
    this->_player = NULL;
    this->_currentPlayerAmount = 0;
}

Race::~Race() {
    for (auto &ia : this->_aiCars) {
        delete ia;
    }
}

void Race::OnFrame() {
    this->_carWatcher.OnFrame();
    for (auto check : this->_circuit.getCheckpoints()) {
        if (check.getID() == this->_n1Check) {
            check.setChVisible(true);
        } else if (check.getID() == this->_n2Check) {
            check.setChVisible(true);
        } else if (check.getID() == this->_n3Check) {
            check.setChVisible(true);
        } else {
            check.setChVisible(false);
        }
    }
    for (auto &ai: this->_aiCars)
        ai->OnFrame();
}

void Race::InitCircuit() {
    this->_circuit << std::pair<irr::core::vector3df const&, irr::core::vector3df const &>(irr::core::vector3df(381.339844, 30.5, 42.452316), irr::core::vector3df(0, 0, 0));
    this->_circuit << std::pair<irr::core::vector3df const&, irr::core::vector3df const &>(irr::core::vector3df(380.485687, 30.5, 28.052046), irr::core::vector3df(0, 0, 0));
    this->_circuit << std::pair<irr::core::vector3df const&, irr::core::vector3df const &>(irr::core::vector3df(387.914948, 30.5, 31.650532), irr::core::vector3df(0, 0, 0));
    this->_circuit << std::pair<irr::core::vector3df const&, irr::core::vector3df const &>(irr::core::vector3df(387.008759, 30.5, 17.105320), irr::core::vector3df(0, 0, 0));
    this->_circuit.push(this->_smgr, irr::core::vector3df(388.425140, 0, 111.531960));
    this->_circuit.push(this->_smgr, irr::core::vector3df(387.802582, 0, 163.426422));
    this->_circuit.push(this->_smgr, irr::core::vector3df(386.224609, 0, 214.996719));
    this->_circuit.push(this->_smgr, irr::core::vector3df(391.161407, 0, 248.681015));
    this->_circuit.push(this->_smgr, irr::core::vector3df(403.839905, 0, 265.768738));
    this->_circuit.push(this->_smgr, irr::core::vector3df(442.130920, 0, 272.877075));
    this->_circuit.push(this->_smgr, irr::core::vector3df(486.089905, 0, 268.783600));
    this->_circuit.push(this->_smgr, irr::core::vector3df(540.417175, 0, 263.329468));
    this->_circuit.push(this->_smgr, irr::core::vector3df(581.361084, 0, 260.181213));
    this->_circuit.push(this->_smgr, irr::core::vector3df(618.789062, 0, 258.290070));
    this->_circuit.push(this->_smgr, irr::core::vector3df(652.610291, 0, 262.279785));
    this->_circuit.push(this->_smgr, irr::core::vector3df(671.355835, 0, 268.797760));
    this->_circuit.push(this->_smgr, irr::core::vector3df(691.959290, 0, 293.014008));
    this->_circuit.push(this->_smgr, irr::core::vector3df(715.185425, 0, 368.425323));
    this->_circuit.push(this->_smgr, irr::core::vector3df(732.583557, 0, 430.751770));
    this->_circuit.push(this->_smgr, irr::core::vector3df(744.152527, 0, 469.642517));
    this->_circuit.push(this->_smgr, irr::core::vector3df(741.839233, 0, 492.765839));
    this->_circuit.push(this->_smgr, irr::core::vector3df(732.611206, 0, 508.762360));
    this->_circuit.push(this->_smgr, irr::core::vector3df(681.941040, 0, 528.457336));
    this->_circuit.push(this->_smgr, irr::core::vector3df(606.851562, 0, 528.374756));
    this->_circuit.push(this->_smgr, irr::core::vector3df(552.799194, 0, 524.725403));
    this->_circuit.push(this->_smgr, irr::core::vector3df(497.207397, 0, 519.007324));
    this->_circuit.push(this->_smgr, irr::core::vector3df(448.076294, 0, 520.342163));
    this->_circuit.push(this->_smgr, irr::core::vector3df(423.325165, 0, 550.664429));
    this->_circuit.push(this->_smgr, irr::core::vector3df(424.176971, 0, 608.884705));
    this->_circuit.push(this->_smgr, irr::core::vector3df(426.804077, 0, 639.852295));
    this->_circuit.push(this->_smgr, irr::core::vector3df(446.281281, 0, 703.510681));
    this->_circuit.push(this->_smgr, irr::core::vector3df(453.959442, 0, 780.337952));
    this->_circuit.push(this->_smgr, irr::core::vector3df(473.494415, 0, 910.555664));
    this->_circuit.push(this->_smgr, irr::core::vector3df(482.364960, 0, 996.858276));
    this->_carWatcher.setCheckpoints(this->_circuit.getCheckpoints());
}

void Race::setPlayer(Car *player) {
    this->_player = player;
    this->_player->setPosition(this->_circuit.getStartingBlock(this->_currentPlayerAmount).first);
    this->_player->setRotation(this->_circuit.getStartingBlock(this->_currentPlayerAmount).second);
    this->_currentPlayerAmount++;

    this->_carWatcher.setCar(this->_player);

    this->_cCheck = 0;
    this->_n1Check = (this->_circuit.getCheckpoints().size() > this->_cCheck ? this->_circuit.getCheckpoints()[this->_cCheck].getID() : -9); this->_cCheck++;
    this->_n2Check = (this->_circuit.getCheckpoints().size() > this->_cCheck ? this->_circuit.getCheckpoints()[this->_cCheck].getID() : -9); this->_cCheck++;
    this->_n3Check = (this->_circuit.getCheckpoints().size() > this->_cCheck ? this->_circuit.getCheckpoints()[this->_cCheck].getID() : -9); this->_cCheck++;
}

void Race::push_ennemy(Car *ennemy) {
    ennemy->setPosition(this->_circuit.getStartingBlock(this->_currentPlayerAmount).first);
    ennemy->setRotation(this->_circuit.getStartingBlock(this->_currentPlayerAmount).second);
    this->_ennemies.push_back(ennemy);
    this->_currentPlayerAmount++;
}

void Race::addAICar(std::string const &short_id) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0.0, 6.0);
    AICar *car = new AICar(this->_smgr, this->_gui, this->_eventReceiver, this->_bulletPhysSys, this->_circuit, (int)round(dist(mt)));
    car->setPosition(this->_circuit.getStartingBlock(this->_currentPlayerAmount).first);
    car->setRotation(this->_circuit.getStartingBlock(this->_currentPlayerAmount).second);
    car->mustSendData(true);
    car->setShouldNetwork(true);
    car->setNetworkID(short_id);
    this->_aiCars.push_back(car);
    this->_currentPlayerAmount++;
}

void Race::OnEnterInCourseChPt(GameCheckpoint const &ch) {
    if (ch.getID() == this->_n1Check) {
        this->_n1Check = this->_n2Check;
        this->_n2Check = this->_n3Check;
        this->_n3Check = (this->_circuit.getCheckpoints().size() > this->_cCheck ? this->_circuit.getCheckpoints()[this->_cCheck].getID() : -9);
        this->_cCheck++;
        for (auto check : this->_circuit.getCheckpoints()) {
            if (check.getID() == ch.getID()) {
                check.setChVisible(false);
            }
        }
        if (ch.getID() == this->_circuit.getCheckpoints()[this->_circuit.getCheckpoints().size() - 1].getID())
            Client::Instance().endRace(Client::Instance().getShortId());
    }
}

int Race::getCurrentPlayerAmount() const {
    return this->_currentPlayerAmount;
}

void Race::FreezePlayers() {
    if (this->_player != NULL)
        this->_player->setFreeze(true);
    for (auto &ia : this->_aiCars) {
        ia->setFreeze(true);
    }
}

void Race::UnFreezePlayers() {
    if (this->_player != NULL)
        this->_player->setFreeze(false);
    for (auto &ia : this->_aiCars) {
        ia->setFreeze(false);
    }
}

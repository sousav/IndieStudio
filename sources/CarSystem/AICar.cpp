//
// AICar.cpp for  in /Users/vicostudio/Documents/Shared/TEK2/CPP/IndieStudio/sources/CarSystem/
//
// Made by Sousa Victor
// Login   <sousa_v@epitech.eu>
//
// Started on  Wed May 24 20:31:35 2017 Sousa Victor
// Last update Thu Jun 15 23:22:54 2017 Sousa Victor
//

#include "AICar.hpp"

using namespace indie;

AICar::AICar(irr::scene::ISceneManager *sceneManager, irr::gui::IGUIEnvironment* guiManager, EventReceiver *eventReceiver, physics::CBulletPhysics *bulletPhysicsSystem, Circuit const &circuit, int car_no):
    Car(sceneManager, guiManager, eventReceiver, bulletPhysicsSystem, circuit, car_no, irr::core::vector3df(2, 36.5, 0), true),
    _steerBrain(std::vector<unsigned> {2, 15, 1}), _engineBrain(std::vector<unsigned> {3, 15, 2}), _carWatcher(this, circuit.getCheckpoints(), this, sceneManager) {

    this->_cCheck = 0;
    this->_n1Check = (this->_circuit.getCheckpoints().size() > this->_cCheck ? this->_circuit.getCheckpoints()[this->_cCheck].getID() : -9); this->_cCheck++;
    this->_n2Check = (this->_circuit.getCheckpoints().size() > this->_cCheck ? this->_circuit.getCheckpoints()[this->_cCheck].getID() : -9); this->_cCheck++;
    this->_n3Check = (this->_circuit.getCheckpoints().size() > this->_cCheck ? this->_circuit.getCheckpoints()[this->_cCheck].getID() : -9); this->_cCheck++;

    this->_steerBrain.loadFrom(std::string(SOURCES_PATH) + "/NetworkData/samples_save/car_steering.txt");
    this->_engineBrain.loadFrom(std::string(SOURCES_PATH) + "/NetworkData/samples_save/car_engine.txt");

    this->_shouldNetwork = false;

}

AICar::~AICar() {

}

void AICar::OnFrame() {
    this->_carWatcher.OnFrame();

    GameCheckpoint const *c1 = NULL;
    GameCheckpoint const *c2 = NULL;
    GameCheckpoint const *c3 = NULL;
    int i = 0;
    for (auto check : this->_circuit.getCheckpoints()) {
        if (check.getID() == this->_n1Check) {
            c1 = &this->_circuit.getCheckpoints()[i];
        } else if (check.getID() == this->_n2Check) {
            c2 = &this->_circuit.getCheckpoints()[i];
        } else if (check.getID() == this->_n3Check) {
            c3 = &this->_circuit.getCheckpoints()[i];
        } else {
        }
        i++;
    }

    std::vector<double> steerInput;
    if (c1 != NULL) {
        irr::core::vector3df camDir = (this->_car->getRotation().rotationToDirection()).normalize();
        irr::core::vector2df camDir2d(camDir.X, camDir.Z);
        irr::core::vector3df checkDir = (c1->getChPosition() - this->getPosition()).normalize();
        irr::core::vector2df checkDir2d(checkDir.X, checkDir.Z);
        float angle = atan2(camDir2d.X * checkDir2d.Y - camDir2d.Y * checkDir2d.X, camDir2d.X * checkDir2d.X + camDir2d.Y * checkDir2d.Y);
        steerInput.push_back(angle);

        float dist = (c1->getPosition() - this->getPosition()).getLength();
        steerInput.push_back(dist / 1000.0);
    } else {
        steerInput.push_back(0.0);
        steerInput.push_back(0.0);
    }
    this->_steerBrain.feedForward(steerInput);

    std::vector<double> engineInput;
    if (c1 != NULL) {
        float dist1 = (c1->getPosition() - this->getPosition()).getLength();
        engineInput.push_back(dist1 / 1000.0);
        if (c2 != NULL) {
            float dist2 = (c2->getPosition() - c1->getPosition()).getLength();
            engineInput.push_back(dist2 / 1000.0);
            if (c3 != NULL) {
                float dist3 = (c3->getPosition() - c2->getPosition()).getLength();
                engineInput.push_back(dist3 / 1000.0);
            } else {
                engineInput.push_back(1.0);
            }
        } else {
            engineInput.push_back(1.0);
            engineInput.push_back(1.0);
        }
    } else {
        engineInput.push_back(1.0);
        engineInput.push_back(1.0);
        engineInput.push_back(1.0);
    }
    this->_engineBrain.feedForward(engineInput);

    Car::OnFrame();
}

void AICar::OnEnterInCourseChPt(GameCheckpoint const &ch) {
    if (ch.getID() == this->_n1Check) {
        this->_n1Check = this->_n2Check;
        this->_n2Check = this->_n3Check;
        this->_n3Check = (this->_circuit.getCheckpoints().size() > this->_cCheck ? this->_circuit.getCheckpoints()[this->_cCheck].getID() : -9); this->_cCheck++;
        for (auto check : this->_circuit.getCheckpoints()) {
            if (check.getID() == ch.getID()) {
                check.setChVisible(false);
            }
        }
        if (ch.getID() == this->_circuit.getCheckpoints()[this->_circuit.getCheckpoints().size() - 1].getID())
            Client::Instance().endRace(this->_netID);
    }
}

void AICar::KeyboardEvent() {
    std::vector<double> engineResult = this->_engineBrain.getResults();
    // std::cout << engineResult[0] << "  " << std::abs(engineResult[1]) << std::endl;
    this->_car->move(engineResult[0]);
    this->_car->brake(std::abs(engineResult[1]));

    std::vector<double> steerResult = this->_steerBrain.getResults();
    this->_car->steer(steerResult[0]);
}

void AICar::SendInfo() {
    if (this->_shouldNetwork) {
        Car::SendInfo();
    }
}

void AICar::setShouldNetwork(bool b) {
    this->_shouldNetwork = b;
}

void AICar::updateCamera() {

}

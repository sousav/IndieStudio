//
// LearningCar.cpp for  in /Users/vicostudio/Documents/Shared/TEK2/CPP/IndieStudio/sources/NeuralNetwork/
//
// Made by Sousa Victor
// Login   <sousa_v@epitech.eu>
//
// Started on  Thu Jun  1 03:38:07 2017 Sousa Victor
// Last update Mon Jun  5 02:46:41 2017 Sousa Victor
//

#include "LearningCar.hpp"

using namespace indie;

LearningCar::LearningCar(irr::scene::ISceneManager *sceneManager, irr::gui::IGUIEnvironment* guiManager, EventReceiver *eventReceiver, physics::CBulletPhysics *bulletPhysicsSystem, Circuit const &circuit, int car_no):
    AICar(sceneManager, guiManager, eventReceiver, bulletPhysicsSystem, circuit, car_no) {

    this->_fitness = 0;
    this->_hasFailed = false;
    this->_indicTotal = 0;
    this->_indicSpeed = 0;

    this->_startPos = this->_car->getPosition();
}

LearningCar::~LearningCar() {

}

void LearningCar::OnFrame() {
    this->_indicTotal += DeltaTimer::DeltaTime;
    if (getVel() < 1) {
        this->_indicSpeed += DeltaTimer::DeltaTime;
    } else {
        this->_indicSpeed = 0;
    }
    this->_hasFailed = (this->_indicSpeed > 3 || this->_indicTotal > 15);
    this->_fitness = (this->_startPos - this->_car->getPosition()).getLength() + (this->_cCheck - 3) * 50;
    AICar::OnFrame();
}

Neural::Genome const LearningCar::GetGenome() const {
    return this->_steerBrain.toGenome();
}

void LearningCar::LoadGenome(Neural::Genome const &genome) {
    this->_steerBrain.fromGenome(genome);
}

void LearningCar::SaveNetwork() const {
    //this->_neuralSystem.saveTo("/Users/vicostudio/Documents/Shared/TEK2/CPP/IndieStudio/build/output/car_" + std::to_string(this->_generationID) + "_" + std::to_string(this->_genomeID) + ".txt");
}

void LearningCar::ClearFailure() {
    this->_fitness = 0;
    this->_hasFailed = false;
    this->_indicSpeed = 0;
}

int LearningCar::getGenomeID() const {
    return this->_genomeID;
}

void LearningCar::setGenomeID(int genomeID) {
    this->_genomeID = genomeID;
}

int LearningCar::getGenerationID() const {
    return this->_generationID;
}

void LearningCar::setGenerationID(int generationID) {
    this->_generationID = generationID;
}

float LearningCar::getFitness() const {
    return this->_fitness;
}

void LearningCar::setFitness(float fitness) {
    this->_fitness = fitness;
}


bool LearningCar::getFailed() const {
    return this->_hasFailed;
}

void LearningCar::setFailed(bool failed) {
    this->_hasFailed = failed;
}

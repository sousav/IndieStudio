//
// GeneticTrainer.cpp for  in /Users/vicostudio/Documents/Shared/TEK2/CPP/IndieStudio/sources/NeuralNetwork/
//
// Made by Sousa Victor
// Login   <sousa_v@epitech.eu>
//
// Started on  Thu Jun  1 04:22:47 2017 Sousa Victor
// Last update Sun Jun  4 23:58:34 2017 Sousa Victor
//

#include "GeneticTrainer.hpp"

using namespace indie;

GeneticTrainer::GeneticTrainer(irr::scene::ISceneManager *sceneManager, irr::gui::IGUIEnvironment* guiManager, EventReceiver *eventReceiver, physics::CBulletPhysics *bulletPhysicsSystem) {
    this->_smgr = sceneManager;
    this->_gui = guiManager;
    this->_eventReceiver = eventReceiver;
    this->_bulletPhysicsSystem = bulletPhysicsSystem;

    this->_circuit << GameCheckpoint(this->_smgr, 0,  0, NULL, 10001, GameCheckpoint::IN_COURSE, 10, irr::core::vector3df(41.907440, 0, -1.561529));
    this->_circuit << GameCheckpoint(this->_smgr, 0,  0, NULL, 10002, GameCheckpoint::IN_COURSE, 10, irr::core::vector3df(98.776421, 0, -2.324740));
    this->_circuit << GameCheckpoint(this->_smgr, 0,  0, NULL, 10003, GameCheckpoint::IN_COURSE, 10, irr::core::vector3df(117.770309, 0, -3.066118));
    this->_circuit << GameCheckpoint(this->_smgr, 0,  0, NULL, 10004, GameCheckpoint::IN_COURSE, 10, irr::core::vector3df(130.029495, 0, -18.802727));
    this->_circuit << GameCheckpoint(this->_smgr, 0,  0, NULL, 10005, GameCheckpoint::IN_COURSE, 10, irr::core::vector3df(132.472397, 0, -42.372440));
    this->_circuit << GameCheckpoint(this->_smgr, 0,  0, NULL, 10006, GameCheckpoint::IN_COURSE, 10, irr::core::vector3df(128.778763, 0, -85.412750));
    this->_circuit << GameCheckpoint(this->_smgr, 0,  0, NULL, 10007, GameCheckpoint::IN_COURSE, 10, irr::core::vector3df(126.353058, 0, -113.734451));
    this->_circuit << GameCheckpoint(this->_smgr, 0,  0, NULL, 10008, GameCheckpoint::IN_COURSE, 10, irr::core::vector3df(123.282791, 0, -152.628357));
    this->_circuit << GameCheckpoint(this->_smgr, 0,  0, NULL, 10009, GameCheckpoint::IN_COURSE, 10, irr::core::vector3df(133.096786, 0, -173.476974));
    this->_circuit << GameCheckpoint(this->_smgr, 0,  0, NULL, 100010, GameCheckpoint::IN_COURSE, 10, irr::core::vector3df(164.909134, 0, -180.785385));
    this->_circuit << GameCheckpoint(this->_smgr, 0,  0, NULL, 100011, GameCheckpoint::IN_COURSE, 10, irr::core::vector3df(202.363037, 0, -184.392593));
    this->_circuit << GameCheckpoint(this->_smgr, 0,  0, NULL, 100012, GameCheckpoint::IN_COURSE, 10, irr::core::vector3df(236.357895, 0, -188.374603));
    this->_circuit << GameCheckpoint(this->_smgr, 0,  0, NULL, 100013, GameCheckpoint::IN_COURSE, 10, irr::core::vector3df(267.142151, 0, -196.617065));
    this->_circuit << GameCheckpoint(this->_smgr, 0,  0, NULL, 100014, GameCheckpoint::IN_COURSE, 10, irr::core::vector3df(308.940857, 0, -211.333496));
    this->_circuit << GameCheckpoint(this->_smgr, 0,  0, NULL, 100015, GameCheckpoint::IN_COURSE, 10, irr::core::vector3df(352.182251, 0, -222.352295));
    this->_circuit << GameCheckpoint(this->_smgr, 0,  0, NULL, 100016, GameCheckpoint::IN_COURSE, 10, irr::core::vector3df(393.277832, 0, -230.603226));
    this->_circuit << GameCheckpoint(this->_smgr, 0,  0, NULL, 100017, GameCheckpoint::IN_COURSE, 10, irr::core::vector3df(431.864441, 0, -238.350555));
    this->_circuit << GameCheckpoint(this->_smgr, 0,  0, NULL, 100018, GameCheckpoint::IN_COURSE, 10, irr::core::vector3df(473.407959, 0, -246.691513));
    this->_circuit << GameCheckpoint(this->_smgr, 0,  0, NULL, 100019, GameCheckpoint::IN_COURSE, 10, irr::core::vector3df(517.125610, 0, -255.469193));
    this->_circuit << GameCheckpoint(this->_smgr, 0,  0, NULL, 100020, GameCheckpoint::IN_COURSE, 10, irr::core::vector3df(571.248657, 0, -272.288940));
    this->_circuit << GameCheckpoint(this->_smgr, 0,  0, NULL, 100021, GameCheckpoint::IN_COURSE, 10, irr::core::vector3df(589.422485, 0, -281.576874));
    this->_circuit << GameCheckpoint(this->_smgr, 0,  0, NULL, 100022, GameCheckpoint::IN_COURSE, 10, irr::core::vector3df(585.868469, 0, -307.293854));
    this->_circuit << GameCheckpoint(this->_smgr, 0,  0, NULL, 100023, GameCheckpoint::IN_COURSE, 10, irr::core::vector3df(584.245361, 0, -338.126495));
    this->_circuit << GameCheckpoint(this->_smgr, 0,  0, NULL, 100024, GameCheckpoint::IN_COURSE, 10, irr::core::vector3df(582.346680, 0, -374.235809));
    this->_circuit << GameCheckpoint(this->_smgr, 0,  0, NULL, 100025, GameCheckpoint::IN_COURSE, 10, irr::core::vector3df(579.556641, 0, -427.298370));
    this->_circuit << GameCheckpoint(this->_smgr, 0,  0, NULL, 100026, GameCheckpoint::IN_COURSE, 10, irr::core::vector3df(577.992554, 0, -457.046387));
    this->_circuit << GameCheckpoint(this->_smgr, 0,  0, NULL, 100027, GameCheckpoint::IN_COURSE, 10, irr::core::vector3df(575.322815, 0, -489.621002));
    this->_circuit << GameCheckpoint(this->_smgr, 0,  0, NULL, 100028, GameCheckpoint::IN_COURSE, 10, irr::core::vector3df(572.670471, 0, -512.188599));
    this->_circuit << GameCheckpoint(this->_smgr, 0,  0, NULL, 100029, GameCheckpoint::IN_COURSE, 10, irr::core::vector3df(544.540222, 0, -521.229980));
    this->_circuit << GameCheckpoint(this->_smgr, 0,  0, NULL, 100030, GameCheckpoint::IN_COURSE, 10, irr::core::vector3df(493.372131, 0, -516.829346));
    this->_circuit << GameCheckpoint(this->_smgr, 0,  0, NULL, 100031, GameCheckpoint::IN_COURSE, 10, irr::core::vector3df(450.889130, 0, -514.424072));
    this->_circuit << GameCheckpoint(this->_smgr, 0,  0, NULL, 100032, GameCheckpoint::IN_COURSE, 10, irr::core::vector3df(436.077393, 0, -522.799561));
    this->_circuit << GameCheckpoint(this->_smgr, 0,  0, NULL, 100033, GameCheckpoint::IN_COURSE, 10, irr::core::vector3df(427.145966, 0, -548.326843));
    this->_circuit << GameCheckpoint(this->_smgr, 0,  0, NULL, 100034, GameCheckpoint::IN_COURSE, 10, irr::core::vector3df(420.931671, 0, -572.526367));
    this->_circuit << GameCheckpoint(this->_smgr, 0,  0, NULL, 100035, GameCheckpoint::IN_COURSE, 10, irr::core::vector3df(401.181549, 0, -579.828186));
    this->_circuit << GameCheckpoint(this->_smgr, 0,  0, NULL, 100036, GameCheckpoint::IN_COURSE, 10, irr::core::vector3df(353.279633, 0, -562.357910));
    this->_circuit << GameCheckpoint(this->_smgr, 0,  0, NULL, 100037, GameCheckpoint::IN_COURSE, 10, irr::core::vector3df(312.473846, 0, -545.127319));
    this->_circuit << GameCheckpoint(this->_smgr, 0,  0, NULL, 100038, GameCheckpoint::IN_COURSE, 10, irr::core::vector3df(266.363159, 0, -531.269470));
    this->_circuit << GameCheckpoint(this->_smgr, 0,  0, NULL, 100039, GameCheckpoint::IN_COURSE, 10, irr::core::vector3df(215.496124, 0, -520.022034));
    this->_circuit << GameCheckpoint(this->_smgr, 0,  0, NULL, 100040, GameCheckpoint::IN_COURSE, 10, irr::core::vector3df(168.508499, 0, -510.341644));
    this->_circuit << GameCheckpoint(this->_smgr, 0,  0, NULL, 100041, GameCheckpoint::IN_COURSE, 10, irr::core::vector3df(136.110672, 0, -507.059662));
    this->_circuit << GameCheckpoint(this->_smgr, 0,  0, NULL, 100042, GameCheckpoint::IN_COURSE, 10, irr::core::vector3df(112.413773, 0, -494.546112));
    this->_circuit << GameCheckpoint(this->_smgr, 0,  0, NULL, 100043, GameCheckpoint::IN_COURSE, 10, irr::core::vector3df(110.795876, 0, -464.753052));
    this->_circuit << GameCheckpoint(this->_smgr, 0,  0, NULL, 100044, GameCheckpoint::IN_COURSE, 10, irr::core::vector3df(110.948669, 0, -420.985718));
    this->_circuit << GameCheckpoint(this->_smgr, 0,  0, NULL, 100045, GameCheckpoint::IN_COURSE, 10, irr::core::vector3df(112.555084, 0, -376.995361));
    this->_circuit << GameCheckpoint(this->_smgr, 0,  0, NULL, 100046, GameCheckpoint::IN_COURSE, 10, irr::core::vector3df(114.624924, 0, -330.619141));
    this->_circuit << GameCheckpoint(this->_smgr, 0,  0, NULL, 100047, GameCheckpoint::IN_COURSE, 10, irr::core::vector3df(118.452034, 0, -261.921936));
    this->_circuit << GameCheckpoint(this->_smgr, 0,  0, NULL, 100048, GameCheckpoint::IN_COURSE, 10, irr::core::vector3df(121.310341, 0, -210.531403));
    this->_circuit << GameCheckpoint(this->_smgr, 0,  0, NULL, 100049, GameCheckpoint::IN_COURSE, 10, irr::core::vector3df(123.917709, 0, -163.638885));
    this->_circuit << GameCheckpoint(this->_smgr, 0,  0, NULL, 100051, GameCheckpoint::IN_COURSE, 10, irr::core::vector3df(126.520348, 0, -115.915413));
    this->_circuit << GameCheckpoint(this->_smgr, 0,  0, NULL, 100052, GameCheckpoint::IN_COURSE, 10, irr::core::vector3df(129.530014, 0, -59.770920));
    this->_circuit << GameCheckpoint(this->_smgr, 0,  0, NULL, 100053, GameCheckpoint::IN_COURSE, 10, irr::core::vector3df(132.783081, 0, 1.030067));
    this->_circuit << GameCheckpoint(this->_smgr, 0,  0, NULL, 100054, GameCheckpoint::IN_COURSE, 10, irr::core::vector3df(134.732559, 0, 37.498192));
    this->_circuit << GameCheckpoint(this->_smgr, 0,  0, NULL, 100055, GameCheckpoint::IN_COURSE, 10, irr::core::vector3df(137.245346, 0, 84.251678));
    this->_circuit << GameCheckpoint(this->_smgr, 0,  0, NULL, 100056, GameCheckpoint::IN_COURSE, 10, irr::core::vector3df(139.946564, 0, 134.308228));
    this->_circuit << GameCheckpoint(this->_smgr, 0,  0, NULL, 100057, GameCheckpoint::IN_COURSE, 10, irr::core::vector3df(142.427612, 0, 180.247162));
    this->_circuit << GameCheckpoint(this->_smgr, 0,  0, NULL, 100058, GameCheckpoint::IN_COURSE, 10, irr::core::vector3df(144.886276, 0, 225.952103));
    this->_circuit << GameCheckpoint(this->_smgr, 0,  0, NULL, 100059, GameCheckpoint::IN_COURSE, 10, irr::core::vector3df(148.166595, 0, 274.692627));
    this->_circuit << GameCheckpoint(this->_smgr, 0,  0, NULL, 100060, GameCheckpoint::IN_COURSE, 10, irr::core::vector3df(145.837433, 0, 313.119843));
    this->_circuit << GameCheckpoint(this->_smgr, 0,  0, NULL, 100061, GameCheckpoint::IN_COURSE, 10, irr::core::vector3df(146.506607, 0, 358.357056));
    this->_circuit << GameCheckpoint(this->_smgr, 0,  0, NULL, 100062, GameCheckpoint::IN_COURSE, 10, irr::core::vector3df(148.107300, 0, 412.932068));
    this->_circuit << GameCheckpoint(this->_smgr, 0,  0, NULL, 100063, GameCheckpoint::IN_COURSE, 10, irr::core::vector3df(148.319214, 0, 462.972321));
    this->_circuit << GameCheckpoint(this->_smgr, 0,  0, NULL, 100064, GameCheckpoint::IN_COURSE, 10, irr::core::vector3df(148.339890, 0, 500.497253));
    this->_circuit << GameCheckpoint(this->_smgr, 0,  0, NULL, 100065, GameCheckpoint::IN_COURSE, 10, irr::core::vector3df(155.385117, 0, 532.196472));
    this->_circuit << GameCheckpoint(this->_smgr, 0,  0, NULL, 100066, GameCheckpoint::IN_COURSE, 10, irr::core::vector3df(192.651672, 0, 527.302551));
    this->_circuit << GameCheckpoint(this->_smgr, 0,  0, NULL, 100067, GameCheckpoint::IN_COURSE, 10, irr::core::vector3df(256.374908, 0, 525.204407));

    this->_genPool.GenerateNewPopulation (15, 213);
    this->_currentAgentFitness = 0.0f;
    this->_bestFitness = 0.0f;

    Neural::Genome *genome = this->_genPool.GetNextGenome();
    this->_aiCar = NULL;
    this->_aiCar = new LearningCar(this->_smgr, this->_gui, this->_eventReceiver, this->_bulletPhysicsSystem, this->_circuit);
    this->_aiCar->LoadGenome(*genome);

    this->_infoFit = this->_gui->addStaticText(L"", irr::core::rect<irr::s32>(400, 20, 1500, 80));
    this->_infoFit->setTextAlignment(irr::gui::EGUIA_SCALE , irr::gui::EGUIA_SCALE);
    this->_infoBestFit = this->_gui->addStaticText(L"", irr::core::rect<irr::s32>(400, 80, 1500, 140));
    this->_infoBestFit->setTextAlignment(irr::gui::EGUIA_SCALE , irr::gui::EGUIA_SCALE);
    this->_infoGenome = this->_gui->addStaticText(L"", irr::core::rect<irr::s32>(400, 140, 1500, 200));
    this->_infoGenome->setTextAlignment(irr::gui::EGUIA_SCALE , irr::gui::EGUIA_SCALE);
    this->_infoGeneration = this->_gui->addStaticText(L"", irr::core::rect<irr::s32>(400, 200, 1500, 260));
    this->_infoGeneration->setTextAlignment(irr::gui::EGUIA_SCALE , irr::gui::EGUIA_SCALE);
}

GeneticTrainer::~GeneticTrainer() {

}

void GeneticTrainer::OnFrame() {
    this->_circuit.OnFrame();
    this->_aiCar->OnFrame();
    std::string str1("      \nCurrentFitness: " + std::to_string(_currentAgentFitness));
    std::string str2("      \nBestFitness: " + std::to_string(_bestFitness));
    std::string str3("      \nGenome: " + std::to_string(this->_genPool.GetCurrentGenomeIndex()));
    std::string str4("      \nGeneration: " + std::to_string(this->_genPool.GetCurrentGeneration()));
    this->_infoFit->setText(Utils::StrToWstr(str1));
    this->_infoBestFit->setText(Utils::StrToWstr(str2));
    this->_infoGenome->setText(Utils::StrToWstr(str3));
    this->_infoGeneration->setText(Utils::StrToWstr(str4));

    this->_aiCar->setGenomeID(this->_genPool.GetCurrentGenomeIndex());
    this->_aiCar->setGenerationID(this->_genPool.GetCurrentGeneration());

    if (this->_aiCar->getFailed()) {
        if (this->_genPool.GetCurrentGenomeIndex() == 15 - 1){
            EvolveGenomes();
            return;
        }
        NextTestSubject();
    }
    this->_currentAgentFitness = this->_aiCar->getFitness();
    if (this->_currentAgentFitness > this->_bestFitness) {
        this->_bestFitness = this->_currentAgentFitness;
    }
}

void GeneticTrainer::NextTestSubject(){
    this->_aiCar->SaveNetwork();

    this->_genPool.SetGenomeFitness(this->_currentAgentFitness, this->_genPool.GetCurrentGenomeIndex());
    this->_currentAgentFitness = 0.0f;
    Neural::Genome *genome = this->_genPool.GetNextGenome();

    delete this->_aiCar;
    this->_aiCar = new LearningCar(this->_smgr, this->_gui, this->_eventReceiver, this->_bulletPhysicsSystem, this->_circuit);
    this->_aiCar->LoadGenome(*genome);
}

void GeneticTrainer::EvolveGenomes(){
    this->_genPool.BreedPopulation();
    NextTestSubject();
}

Car *GeneticTrainer::getCar() const {
    return this->_aiCar;
}

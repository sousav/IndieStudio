/*
** RandomEvent.cpp for Shared in /Users/gmblucas/Desktop/Shared/IndieStudio/sources
**
** Made by Lucas Gambini
** Login   <gmblucas@epitech.net>
**
** Started on  Sat May 20 01:55:01 2017 Lucas Gambini
** Last update Sun Jun 18 22:34:30 2017 Lucas Gambini
*/

#include "RandomEvent.hpp"

using namespace indie;

RandomEvent::RandomEvent(irr::scene::ISceneManager* smgr, carWatcher *watcher) {
    this->_smgr = smgr;
    this->_watcher = watcher;
    this->_currentOffset = -1;
    #ifndef DEBUG
        this->_IMin = 10;
        this->_IMax = 40;
    #else
        this->_IMin = 1;
        this->_IMax = 5;
    #endif
    srand(time(NULL));

    this->_preset.push_back(irr::core::vector3df(-164.332672, 0, 5.319206));
    this->_preset.push_back(irr::core::vector3df(-1861.654175, 0, -686.144226));
    this->_preset.push_back(irr::core::vector3df(-238.138550, 0, -927.903687));
    this->_preset.push_back(irr::core::vector3df(105.142326, 0, -497.781921));
    this->_preset.push_back(irr::core::vector3df(1443.559937, 0, 187.650177));
    this->_preset.push_back(irr::core::vector3df(1792.627075, 0, 1379.914673));
    this->_preset.push_back(irr::core::vector3df(2147.340820, 0, -434.592194));
    this->_preset.push_back(irr::core::vector3df(2358.016846, 0, 662.122070));
    this->_preset.push_back(irr::core::vector3df(5785.583008, 0, -1900.686279));
    this->_preset.push_back(irr::core::vector3df(8193.258789, 0, -1776.445068));
    this->_preset.push_back(irr::core::vector3df(2552.944092, 0, 2653.504150));
    this->_preset.push_back(irr::core::vector3df(3256.100830, 0, 4262.480957));
    this->_preset.push_back(irr::core::vector3df(4345.298340, 0, -5281.133301));
    this->_preset.push_back(irr::core::vector3df(2047.266479, 0, -5985.814453));
    this->_preset.push_back(irr::core::vector3df(929.871521, 0, -3405.100342));
    this->_preset.push_back(irr::core::vector3df(-2509.852783, 0, -2326.814209));
    this->_preset.push_back(irr::core::vector3df(-4066.192139, 0, -2054.364746));
    this->_preset.push_back(irr::core::vector3df(-4160.228027, 0, 308.927643));
    this->_preset.push_back(irr::core::vector3df(-1963.312500, 0, 1907.926270));

    this->_index = rand() % this->_preset.size();
}

RandomEvent::~RandomEvent() {

}

void RandomEvent::OnFrame() {
    if (this->_preset.size() == 0)
        return;
    if (this->_currentOffset == -1) {
        while ((this->_currentOffset = rand() % this->_IMax) < this->_IMin);
    } else if ((int)this->_elapsedTime >= this->_currentOffset) {
        GameCheckpoint check = GameCheckpoint(this->_smgr, 3, 0, NULL, this->_index, GameCheckpoint::MONEY, 5, this->_preset[this->_index]);
        this->_watcher->addCheckpoint(check);
        this->_preset.erase(this->_preset.begin() + this->_index);
        this->_currentOffset = -1;
        this->_elapsedTime = 0;
        if (this->_preset.size() != 0)
            this->_index = rand() % this->_preset.size();

    } else {
        this->_elapsedTime += DeltaTimer::DeltaTime;
    }
}

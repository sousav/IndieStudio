/*
** carWatcher.hpp for Shared in /Users/gmblucas/Desktop/Shared/IndieStudio/includes/Watcher
**
** Made by Lucas Gambini
** Login   <gmblucas@epitech.net>
**
** Started on  Sat May 13 20:18:21 2017 Lucas Gambini
** Last update Tue Jun 13 05:23:02 2017 Sousa Victor
*/

#ifndef CAR_WATCHER_HPP
#define CAR_WATCHER_HPP

#include <irrlicht.h>
#include <map>
#include <vector>
#include <vector3d.h>
#include "Car.hpp"
#include "EventReceiver.hpp"
#include "GameCheckpoint.hpp"

namespace indie {

    class carWatcher : public IGameObject {

    public:
        carWatcher(Car *, std::vector<GameCheckpoint> const &, EventReceiver *, irr::scene::ISceneManager *);
        virtual ~carWatcher();

        virtual void OnFrame();
        void addCheckpoint(GameCheckpoint &check);
        std::vector<GameCheckpoint> getCheckpoints() const;
        void setCheckpoints(std::vector<GameCheckpoint> const &);
        void setCar(Car *car);

        void setNeedRemove(bool);
        bool getNeedRemove() const;

    private:
        bool isCarInCheck(GameCheckpoint const &ch, irr::core::vector3df const &cpos) const;
        bool inLine(float a, float new_a, float rad) const;

        irr::scene::ISceneManager* _smgr;
        Car *_car;
        EventReceiver *_eventReceiver;
        std::vector<GameCheckpoint> _checkpoints;
        bool _needRemove;
    };

}

#endif /* !CAR_WATCHER_HPP */

/*
** RandomEvent.hpp for Shared in /Users/gmblucas/Desktop/Shared/IndieStudio/includes
**
** Made by Lucas Gambini
** Login   <gmblucas@epitech.net>
**
** Started on  Sat May 20 01:48:12 2017 Lucas Gambini
** Last update Tue Jun  6 19:30:59 2017 Sousa Victor
*/

#ifndef RANDOM_EVENT_HPP
#define RANDOM_EVENT_HPP

#include "carWatcher.hpp"
#include "IGameObject.hpp"
#include <random>
#ifdef _WIN32
#include <time.h>
#endif

namespace indie {

    class RandomEvent : public IGameObject {

        public:
            RandomEvent(irr::scene::ISceneManager *, carWatcher *);
            ~RandomEvent();

            void OnFrame();

        private:
            irr::scene::ISceneManager* _smgr;
            carWatcher *_watcher;
            int _currentOffset;
            irr::f32 _elapsedTime;
            std::vector<irr::core::vector3df> _preset;
            int _index;
            int _IMin;
            int _IMax;
    };

};

#endif /* !RANDOM_EVENT_HPP */

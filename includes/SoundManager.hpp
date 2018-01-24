/*
** SoundManager.hpp for IndieStudio in /Users/gmblucas/Desktop/Shared/IndieStudio/includes
**
** Made by Lucas Gambini
** Login   <gmblucas@epitech.net>
**
** Started on  Fri Jun 16 18:16:57 2017 Lucas Gambini
** Last update Fri Jun 16 18:23:33 2017 Lucas Gambini
*/

#ifndef SOUNDMANAGER_HPP
#define SOUNDMANAGER_HPP

#include <irrKlang.h>

namespace indie {

    class SoundManager {

    public:
        SoundManager();
        ~SoundManager();
        static SoundManager &Instance();
        irrklang::ISoundEngine* getEngine();

    private:
        static SoundManager _instance;
        irrklang::ISoundEngine* _engine;


    };

}


#endif /* !SOUNDMANAGER_HPP */

//
// IGameObject.hpp for  in /Users/vicostudio/Documents/Shared/TEK2/CPP/cpp_indie_studio/includes/
//
// Made by Sousa Victor
// Login   <sousa_v@epitech.eu>
//
// Started on  Sun May  7 18:34:01 2017 Sousa Victor
// Last update Mon May  8 23:57:29 2017 Sousa Victor
//

#ifndef AGAMEOBJECT_HPP_
#define AGAMEOBJECT_HPP_

#include "IGameObject.hpp"

namespace indie {

    class AGameObject : public IGameObject {

    public:
        AGameObject();
        AGameObject(irr::scene::ISceneManager *sceneManager);
        AGameObject(const AGameObject &obj);
        AGameObject &operator=(const AGameObject &obj);
        ~AGameObject();

        virtual void OnFrame() = 0;

    protected:
        irr::scene::ISceneManager *_smgr;

    };

}

#else

namespace indie {
    class AGameObject;
}

#endif /*AGAMEOBJECT_HPP_*/

//
// APhysicObject.hpp for  in /Users/vicostudio/Documents/Shared/TEK2/CPP/cpp_indie_studio_github/includes/
//
// Made by Sousa Victor
// Login   <sousa_v@epitech.eu>
//
// Started on  Thu May 11 00:49:59 2017 Sousa Victor
// Last update Fri May 19 21:26:20 2017 Sousa Victor
//

#ifndef APHYSICOBJECT_HPP_
#define APHYSICOBJECT_HPP_

#include "AModelObject.hpp"

namespace indie {

    class APhysicObject: public AModelObject {

    public:
        APhysicObject();
        APhysicObject(irr::scene::ISceneManager *sceneManager, std::string const &path,
                 irr::scene::ISceneNode *parent = 0, irr::s32 id = -1, irr::f32 mass = 0,
                 const irr::core::vector3df &position = irr::core::vector3df(0,0,0),
                 const irr::core::vector3df &rotation = irr::core::vector3df(0,0,0),
                 const irr::core::vector3df &scale = irr::core::vector3df(1.0f, 1.0f, 1.0f));
         APhysicObject(const APhysicObject &obj);
         APhysicObject &operator=(const APhysicObject &obj);
         virtual ~APhysicObject();

        virtual void OnFrame() = 0;

    protected:

    };

}

#endif /*APHYSICOBJECT_HPP_*/

//
// Minimap.hpp for  in /Users/ethankerdelhue/Documents/shared/IndieStudio/sources/
//
// Made by Ethan Kerdelhue
// Login   <ethan.kerdelhue@epitech.eu@epitech.eu>
//
// Started on  Sat May 13 20:33:23 2017 Ethan Kerdelhue
// Last update Tue Jun  6 19:23:17 2017 Ethan Kerdelhue
//

#ifndef MINIMAP_HPP
  #define MINIMAP_HPP

#include <math.h>
#include "Utils.hpp"
#include "AGameObject.hpp"
#include "Car.hpp"
#include "IGUI.hpp"
#include "carWatcher.hpp"

namespace indie {

  class Minimap : public AGameObject {

  public:
    Minimap (irr::scene::ISceneManager *sceneManager, irr::scene::ISceneNode* parent,
             irr::s32 id, Car *car, carWatcher *carWatcher, irr::video::IVideoDriver* driver,
             irr::IrrlichtDevice *device, irr::gui::IGUIEnvironment *gui, irr::core::dimension2du const &screenDim);

    virtual ~Minimap ();
    virtual void OnFrame();

    virtual void setViewport(irr::core::rect<irr::s32> viewport) {
        this->_viewport = viewport;
    }
    virtual irr::core::rect<irr::s32> getViewport() const {
        return this->_viewport;
    }

    protected:
        Car                           *_car;
        carWatcher *_carWatcher;
        irr::scene::ICameraSceneNode  *_camera;
        irr::video::ITexture          *_image;
        irr::core::rect<irr::s32>     _viewport;
        irr::video::IVideoDriver      *_driver;
        irr::gui::IGUIEnvironment          *_gui;
        irr::core::dimension2du _screenDim;
        irr::gui::IGUIStaticText *_pos;
        std::map<GameCheckpoint::Type, video::ITexture *>_textureMap;
        std::vector<irr::gui::IGUIImage *> _imgVector;
  };
}

#endif

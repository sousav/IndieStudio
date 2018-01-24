/*
** Garage.hpp for Shared in /Users/gmblucas/Desktop/Shared/IndieStudio/includes/GUI
**
** Made by Lucas Gambini
** Login   <gmblucas@epitech.net>
**
** Started on  Thu May 18 01:01:56 2017 Lucas Gambini
** Last update Sat May 20 00:38:42 2017 Lucas Gambini
*/

#ifndef GARAGE_HPP
#define GARAGE_HPP

#include <irrlicht.h>
#include <IGUIEnvironment.h>
#include "IGUI.hpp"

namespace indie {

    class Garage : public IGUI {

        public: enum BTN_IDS
        {
            REPAIR = 4242,
            LEAVE
        };

        public:
            Garage(irr::gui::IGUIEnvironment *, irr::video::IVideoDriver *, irr::core::dimension2du);
            virtual ~Garage();

            void SetupGUI();
            void setVisible(bool visible);
            bool isVisible(void) const;

            virtual void OnFrame();

        private:
            irr::gui::IGUIEnvironment *_gui;
            irr::gui::IGUIWindow *_window;
            irr::video::IVideoDriver *_driver;

            bool _isVisible;
            irr::core::dimension2du _windowSize;

            irr::gui::IGUIStaticText *_title;
            irr::gui::IGUIButton *_repair;
            irr::gui::IGUIButton *_leave_;

        };

}

#endif /* !GARAGE_HPP */

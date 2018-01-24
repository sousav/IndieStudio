/*
** Course.hpp for Shared in /Users/gmblucas/Desktop/Shared/IndieStudio/includes/GUI
**
** Made by Lucas Gambini
** Login   <gmblucas@epitech.net>
**
** Started on  Sat May 20 00:37:46 2017 Lucas Gambini
** Last update Mon Jun 12 01:36:59 2017 Lucas Gambini
*/

#ifndef COURSE_HPP
#define COURSE_HPP

#include <irrlicht.h>
#include <vector>
#include <IGUIEnvironment.h>
#include "IGUI.hpp"
#include "Utils.hpp"

namespace indie {

    class Course : public IGUI {

        public: enum BTN_IDS
        {
            CANCEL = 6969,
            RUN
        };

        public:
            Course(irr::gui::IGUIEnvironment *, irr::video::IVideoDriver *, irr::core::dimension2du);
            virtual ~Course();

            void SetupGUI();
            void setVisible(bool visible);
            bool isVisible(void) const;
            void OnFrame();

            void addPlayer(std::string const &);
            void ripPlayers();
            void ripPlayer(std::string const &);

        private:
            irr::gui::IGUIEnvironment *_gui;
            irr::gui::IGUIWindow *_window;
            irr::video::IVideoDriver *_driver;

            bool _isVisible;
            irr::core::dimension2du _windowSize;

            irr::gui::IGUIStaticText *_title;
            irr::gui::IGUIButton *_cancel;
            irr::gui::IGUIButton *_run;
            std::vector<irr::gui::IGUIStaticText *> _players;

        };


}

#endif /* !COURSE_HPP */

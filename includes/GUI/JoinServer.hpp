/*
** JoinServer.hpp for Shared in /Users/gmblucas/Desktop/Shared/IndieStudio/includes/GUI
**
** Made by Lucas Gambini
** Login   <gmblucas@epitech.net>
**
** Started on  Wed May 31 00:49:06 2017 Lucas Gambini
** Last update Wed May 31 16:29:52 2017 Lucas Gambini
*/

#ifndef JOINSERVER_HPP
#define JOINSERVER_HPP

#include <irrlicht.h>
#include <IGUIEnvironment.h>
#include "IGUI.hpp"

namespace indie {

    class JoinServer : public IGUI {

        public: enum BTN_IDS
        {
            LEAVE = 34,
            JOIN
        };

        public:
            JoinServer(irr::gui::IGUIEnvironment *, irr::video::IVideoDriver *, irr::core::dimension2du);
            virtual ~JoinServer();

            void SetupGUI();
            void setVisible(bool visible);
            bool isVisible(void) const;

            virtual void OnFrame();

            const wchar_t* getText() const;

        private:
            irr::gui::IGUIEnvironment *_gui;
            irr::gui::IGUIWindow *_window;
            irr::video::IVideoDriver *_driver;

            bool _isVisible;
            irr::core::dimension2du _windowSize;

            irr::gui::IGUIStaticText *_title;
            irr::gui::IGUIButton *_leave_;
            irr::gui::IGUIButton *_join;
            irr::gui::IGUIEditBox *_editBox;

        };

}

#endif /* !JOINSERVER_HPP */

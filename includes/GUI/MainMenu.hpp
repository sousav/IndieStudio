/*
** MainMenu.hpp for IndieStudio
**
** Made by	Full Name
** Login	Full Name
**
** Started on	Tue Jun 06 15:36:48 2017 Full Name
** Last update Fri Jun 16 13:50:47 2017 Lucas Gambini
*/

#ifndef _MAINMENU_HPP_
#define _MAINMENU_HPP_

#include <irrlicht.h>
#include <IGUIEnvironment.h>
#include "EventReceiver.hpp"
#include "IGUI.hpp"
#include "Settings.hpp"

namespace indie {

    class MainMenu : public IGUI {

    public: enum MAIN_MENU
    {
        PLAY = 8282,
        MULTIJOUEUR,
        QUIT,
    };

    public:
        MainMenu(irr::gui::IGUIEnvironment*, irr::video::IVideoDriver*, irr::core::dimension2du);
        ~MainMenu();
         void SetupGUI();
         void OnFrame(void);

         void setVisible(bool visible);
         bool isVisible(void) const;

         bool getPlay() const;
         void setPlay(bool play);

    private:
        irr::gui::IGUIEnvironment *_gui;
        irr::gui::IGUIWindow *_window;
        irr::video::IVideoDriver *_driver;
        irr::core::dimension2du _windowSize;

        bool _isVisible;

        bool _play;

        irr::gui::IGUIButton *_start;
        irr::gui::IGUIButton *_multijoueur;
        irr::gui::IGUIButton *_quit;

        irr::video::ITexture *_texture;
        irr::gui::IGUIImage *_back;
        irr::gui::IGUIStaticText *_title;
        

    };
}

#endif /* !_MAINMENU_HPP_ */

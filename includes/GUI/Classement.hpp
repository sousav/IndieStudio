/*
** Classement.hpp for IndieStudio
**
** Made by	Full Name
** Login	Full Name
**
** Started on	Mon Jun 05 16:05:20 2017 Full Name
** Last update	Tue Jun 06 15:05:37 2017 Full Name
*/

#ifndef _CLASSEMENT_HPP_
#define _CLASSEMENT_HPP_

#include <irrlicht.h>
#include <IGUIEnvironment.h>
#include <vector>
#include <string>
#include "IGUI.hpp"

namespace indie {

    class Classement : public IGUI {

    public:
        Classement(irr::gui::IGUIEnvironment*, irr::video::IVideoDriver*, irr::core::dimension2du, std::vector<std::string>);
        ~Classement();
         void SetupGUI();
         void OnFrame(void);

         void setVisible(bool visible);
         bool isVisible(void) const;

    private:
        irr::gui::IGUIEnvironment *_gui;
        irr::gui::IGUIWindow *_window;
        irr::video::IVideoDriver *_driver;
        irr::core::dimension2du _windowSize;
        irr::gui::IGUIStaticText *_title;
        irr::gui::IGUIStaticText *_first;
        irr::gui::IGUIStaticText *_second;
        irr::gui::IGUIStaticText *_third;
        irr::gui::IGUIStaticText *_forth;
        irr::gui::IGUIButton *_exit;
        std::vector<std::string> _result;
    };
}

#endif /* !_CLASSEMENT_HPP_ */

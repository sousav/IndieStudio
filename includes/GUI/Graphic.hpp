/*
** Graphic.hpp for IndieStudio in /Users/Vacca_J/Epitech/Tek2/Projet/IndieStudio/includes/GUI
**
** Made by Vacca_J
** Login   <Vacca_J@epitech.net>
**
** Started on  Sat May 20 22:09:37 2017 Vacca_J
** Last update Sat Jun 17 04:22:56 2017 Lucas Gambini
*/
  #ifndef GRAPHIC_HPP_
  #define GRAPHIC_HPP_

#include <irrlicht.h>
#include <ITexture.h>
#include <IGUIEnvironment.h>
#include "IGameObject.hpp"
#include "IGUI.hpp"
#include "Utils.hpp"

namespace indie {

class Graphic : public IGUI {

    public: enum GRAPH_BTN
    {
        RESOL1 = 2222,
        RESOL2,
        RESOL3,
        EXIT
    };

private:
  irr::gui::IGUIWindow *_window;
  irr::gui::IGUIEnvironment *_gui;
  irr::video::IVideoDriver *_driver;
  irr::core::dimension2du _windowSize;

  irr::gui::IGUIStaticText *_title;
  irr::gui::IGUIButton *_resol1;
  irr::gui::IGUIButton *_resol2;
  irr::gui::IGUIButton *_resol3;
  irr::gui::IGUIButton *_exit;
  irr::gui::IGUIEditBox *_editBox;


  bool _isVisible;
public:

  Graphic(irr::gui::IGUIEnvironment*, irr::video::IVideoDriver*, irr::core::dimension2du);
  ~Graphic ();
  void setGraphic();
  int getText() const;

  void SetupGUI();
  void setVisible(bool visible);
  bool isVisible(void) const;
  void OnFrame();

  };

}

  #endif /* !GRAPHIC_HPP_ */

/*
** Keyboard.hpp for IndieStudio in /Users/Vacca_J/Epitech/Tek2/Projet/IndieStudio/includes/GUI
**
** Made by Vacca_J
** Login   <Vacca_J@epitech.net>
**
** Started on  Sat May 20 17:36:35 2017 Vacca_J
** Last update Sun Jun 18 04:35:11 2017 Sousa Victor
*/

#ifndef KEYBOARD_HPP_
#define KEYBOARD_HPP_

#include <irrlicht.h>
#include <ITexture.h>
#include <IGUIEnvironment.h>
#include <vector>
#include <iostream>
#include <string>
#include <IEventReceiver.h>
#include <map>
#include "EventReceiver.hpp"
#include "IGameObject.hpp"
#include "IGUI.hpp"

namespace indie {

class Keyboard : public IGUI , public EventReceiver {

  public: enum KEYBOARD_BTNS
  {
      up = 1001,
      down,
      left,
      right,
      forward,
      backward,
      space,
      quit
  };

  public: enum KEYCODE_TYPE
  {
     UP = 1,
     DOWN,
     LEFT,
     RIGHT,
     FORWARD,
     BACKWARD,
     SPACE
 };

private:
  int _id;
  irr::gui::IGUIWindow *_window;
  irr::gui::IGUIEnvironment *_gui;
  irr::video::IVideoDriver *_driver;
  irr::core::dimension2du _windowSize;

  irr::gui::IGUIStaticText *_title;
  irr::gui::IGUIButton *_up;
  irr::gui::IGUIButton *_down;
  irr::gui::IGUIButton *_left;
  irr::gui::IGUIButton *_right;
  irr::gui::IGUIButton *_space;

  irr::gui::IGUIButton *_backward;
  irr::gui::IGUIButton *_forward;


  irr::gui::IGUIButton *_exit;

  std::map<KEYCODE_TYPE, irr::EKEY_CODE> _mymap;

  irr::gui::IGUIStaticText *_title2;
  bool _isVisible;
public:
  void OnEnterKey(irr::EKEY_CODE keyCode);

  Keyboard(irr::gui::IGUIEnvironment*, irr::video::IVideoDriver*, irr::core::dimension2du);
  ~Keyboard ();
  void setKeyboard();

  void resetUp(void);
  void resetDown(void);
  void resetLeft(void);
  void resetRight(void);

  void resetForward(void);
  void resetBackward(void);

  void resetBrake(void);

  const std::map<KEYCODE_TYPE, irr::EKEY_CODE> &getMap() const;

  void SetupGUI();
  void setVisible(bool visible);
  bool isVisible(void) const;
  void OnFrame();

  };

}

#else

namespace indie {

    class Keyboard;

}

#endif /* !KEYBOARD_HPP_ */

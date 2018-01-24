/*
** Setting.hpp for IndieStudio in /Users/Vacca_J/Epitech/Tek2/Projet/IndieStudio/includes/GUI
**
** Made by Vacca_J
** Login   <Vacca_J@epitech.net>
**
** Started on  Sun May 14 15:15:48 2017 Vacca_J
** Last update Tue May 23 01:15:04 2017 Vacca_J
*/

#ifndef SETTING_HPP_
#define SETTING_HPP_

#include <irrlicht.h>
#include <ITexture.h>
#include <IGUIEnvironment.h>
#include "IGameObject.hpp"
#include "IGUI.hpp"
#include "Audio.hpp"
#include "Graphic.hpp"
#include "Keyboard.hpp"

namespace indie {

class Settings : public IGUI {

  public: enum SETTINGS_BTNS
  {
      GRAPHIC = 8001,
      AUDIO,
      KEYBOARD,
  };

private:
  irr::gui::IGUIWindow *_window;
  irr::gui::IGUIEnvironment *_gui;
  irr::video::IVideoDriver *_driver;
  irr::core::dimension2du _windowSize;

  irr::video::ITexture *_images;
  irr::gui::IGUIStaticText *_title;
  irr::gui::IGUIButton *_graphic;
  irr::gui::IGUIButton *_song;
  irr::gui::IGUIButton *_keyboard;
  Audio *_Waudio;
  Keyboard *_Wkeyboard;
  Graphic *_Wgraphic;

  bool _isVisible;
public:

  Settings(irr::gui::IGUIEnvironment*, irr::video::IVideoDriver*, irr::core::dimension2du);
  ~Settings ();
  void setSettings();

  void SetupGUI();
  void setVisible(bool visible);
  bool isVisible(void) const;
  void OnFrame();
  void OnGraphic();
  void OnEnterGraphic();
  void OnEnterAudio();
  void OnEnterKeyboard();

  Audio *getAudio();
  Graphic *getGraphic();
  Keyboard *getKeyboard();

  };

}
#endif /* !SETTING_HPP_ */

/*
** song.hpp for IndieStudio in /Users/Vacca_J/Epitech/Tek2/Projet/IndieStudio/includes/GUI
**
** Made by Vacca_J
** Login   <Vacca_J@epitech.net>
**
** Started on  Sat May 20 14:33:37 2017 Vacca_J
** Last update Fri Jun 16 18:29:00 2017 Lucas Gambini
*/

#ifndef AUDIO_HPP
#define AUDIO_HPP

#include <vector>
#include <irrlicht.h>
#include <ITexture.h>
#include <IGUIEnvironment.h>
#include "IGameObject.hpp"
#include "IGUI.hpp"
#include "SoundManager.hpp"

namespace indie {

class Audio : public IGUI {

  public: enum AUDIO_BTNS
  {
      PLUS = 2001,
      MOIN,
      Quit,
  };

private:
  irr::gui::IGUIWindow *_window;
  irr::gui::IGUIEnvironment *_gui;
  irr::video::IVideoDriver *_driver;
  irr::core::dimension2du _windowSize;

  irr::gui::IGUIStaticText *_title;
  irr::gui::IGUIButton *_plus;
  irr::gui::IGUIButton *_moin;
  irr::gui::IGUIButton *_exit;
  irr::gui::IGUIImage *_bar1;
  irr::gui::IGUIImage *_bar2;
  irr::gui::IGUIImage *_bar3;
  irr::gui::IGUIImage *_bar4;
  irr::gui::IGUIImage *_bar5;
  irr::gui::IGUIImage *_bar6;
  irr::gui::IGUIImage *_bar7;
  irr::gui::IGUIImage *_bar8;
  irr::gui::IGUIImage *_bar9;
  irr::gui::IGUIImage *_bar10;
  std::vector<irr::gui::IGUIImage *> _volume;
  irr::video::ITexture *_red;
  irr::video::ITexture *_green;

  bool _isVisible;

public:

  Audio(irr::gui::IGUIEnvironment*, irr::video::IVideoDriver*, irr::core::dimension2du);
  ~Audio ();
  void setAudio();
  void plus();
  void moin();
  void SetupGUI();
  void setVisible(bool visible);
  bool isVisible(void) const;
  void OnFrame();
  };

}

#endif /* !AUDIO_HPP */

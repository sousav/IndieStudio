/*
** IGUI.hpp for Shared in /Users/gmblucas/Desktop/Shared/IndieStudio/includes/GUI
**
** Made by Lucas Gambini
** Login   <gmblucas@epitech.net>
**
** Started on  Fri May 19 21:58:56 2017 Lucas Gambini
** Last update Fri May 19 22:10:48 2017 Lucas Gambini
*/

#ifndef IGUI_HPP
#define IGUI_HPP

#include "IGameObject.hpp"

namespace indie {

    class IGUI : public IGameObject {

    public:
        virtual ~IGUI(){};
        virtual void SetupGUI() = 0;
        virtual void OnFrame() = 0;
        virtual bool isVisible() const = 0;
        virtual void setVisible(bool) = 0;
    };

}

#endif /* !IGUI_HPP */

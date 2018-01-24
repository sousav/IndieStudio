/*
** SizeS.hpp for IndieStudio in /Users/gmblucas/Desktop/Shared/IndieStudio/includes
**
** Made by Lucas Gambini
** Login   <gmblucas@epitech.net>
**
** Started on  Fri Jun 16 18:16:57 2017 Lucas Gambini
** Last update Sat Jun 17 23:22:06 2017 Lucas Gambini
*/

#ifndef SIZES_HPP
#define SIZES_HPP

namespace indie {

    class SizeS {

    public:
        SizeS();
        ~SizeS();
        static SizeS &Instance();

        int Width;
        int Height;

    private:
        static SizeS _instance;

    };

}


#endif /* !SIZES_HPP */

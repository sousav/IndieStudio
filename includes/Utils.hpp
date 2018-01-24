//
// Utils.hpp for  in /Users/vicostudio/Documents/Shared/TEK2/CPP/cpp_indie_studio_/includes/
//
// Made by Sousa Victor
// Login   <sousa_v@epitech.eu>
//
// Started on  Mon May 15 11:30:07 2017 Sousa Victor
// Last update Mon May 15 11:32:51 2017 Sousa Victor
//

#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <string>

namespace indie {

    class Utils {

        public: static wchar_t* StrToWstr(std::string str) {
            return const_cast<wchar_t*>(std::wstring(str.begin(), str.end()).c_str());
        }

    };

}

#endif /*UTILS_HPP_*/

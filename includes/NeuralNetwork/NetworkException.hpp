//
// NetworkException.hpp for  in /Users/vicostudio/Documents/Shared Folder/Work/NeuralNetwork/CPP/Neural/includes/
//
// Made by Sousa Victor
// Login   <sousa_v@epitech.eu>
//
// Started on  Mon May  1 02:36:39 2017 Sousa Victor
// Last update Tue May  2 01:50:26 2017 Sousa Victor
//

#ifndef NETWORKEXCEPTION
#define NETWORKEXCEPTION

#include <string>

namespace Neural {

    class NetworkException : public std::exception {
        public:
            NetworkException(std::string const &message) {
                _message = message;
            };
            virtual ~NetworkException() throw() {};
            virtual const char *what(void) const throw() {
                return (this->_message.data());
            }

        private:
            std::string _message;
    };

    class InvalidInput : public NetworkException {

        public:
            InvalidInput(std::string const &message): NetworkException(message) {};
            virtual ~InvalidInput() throw() {};

    };

    class InvalidTrainingFile : public NetworkException {

        public:
            InvalidTrainingFile(std::string const &message): NetworkException(message) {};
            virtual ~InvalidTrainingFile() throw() {};

    };

    class InvalidSavingFile : public NetworkException {

        public:
            InvalidSavingFile(std::string const &message): NetworkException(message) {};
            virtual ~InvalidSavingFile() throw() {};

    };

}

#endif /*NETWORKEXCEPTION*/

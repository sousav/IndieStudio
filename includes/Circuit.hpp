//
// Circuit.hpp for  in /Users/vicostudio/Documents/Shared/TEK2/CPP/IndieStudio/includes/
//
// Made by Sousa Victor
// Login   <sousa_v@epitech.eu>
//
// Started on  Sat Jun  3 20:09:08 2017 Sousa Victor
// Last update Wed Jun 14 20:50:27 2017 Lucas Gambini
//

#ifndef CIRCUIT_HPP_
#define CIRCUIT_HPP_

#include <vector>
#include "GameCheckpoint.hpp"

namespace indie {

    class Circuit : public IGameObject {

    public:
        Circuit();
        Circuit(const Circuit& obj);
        ~Circuit();
        Circuit &operator=(const Circuit& obj);

        virtual void OnFrame();

        void reCreate();

        void push(irr::scene::ISceneManager *sceneManager, irr::core::vector3df const &point);
        Circuit &operator <<(GameCheckpoint const &point);
        Circuit &operator <<(std::pair<irr::core::vector3df, irr::core::vector3df> const &point);

        std::vector<GameCheckpoint> const &getNextCheckpoints(unsigned index) const;
        std::vector<GameCheckpoint> const &getCheckpoints() const;

        std::vector<std::pair<irr::core::vector3df, irr::core::vector3df> > const &getStartingBlock() const;
        std::pair<irr::core::vector3df, irr::core::vector3df> const &getStartingBlock(int index) const;

    private:
        std::vector<std::pair<irr::core::vector3df, irr::core::vector3df> >_startingBlock;
        std::vector<GameCheckpoint> _checkpoints;

    };

}

#endif /*CIRCUIT_HPP_*/

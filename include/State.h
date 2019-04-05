#ifndef STATE_H
#define STATE_H

#include <SFML/Graphics.hpp>

class State
{
    public:
        void init();
        void pause();
        void resume();
        void cleanUp();

        virtual void handleEvents() = 0;
        virtual void update() = 0;
        virtual void draw(sf::RenderWindow &app) = 0;
};

#endif // STATE_H

#ifndef STATE_H
#define STATE_H

#include <SFML/Graphics.hpp>

class State
{
public:
    virtual void handleEvents() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
};

#endif // STATE_H

#pragma once
#ifndef CONTROLSSTATE_H
#define CONTROLSSTATE_H

#include "GameState.h"

class ControlsState : public GameState
{
public:

    virtual void draw(const float dt);
    virtual void update(const float dt);
    virtual void handleInput();

     ControlsState(Game* game);

private:

    void returnMenu();

    sf::Clock clock;

    sf::Texture controls;
    sf::Sprite spritecontrols;

};

#endif // CONTROLSSTATE_H

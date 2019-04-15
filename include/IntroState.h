#ifndef INTROSTATE_H
#define INTROSTATE_H


#include <SFML/Graphics.hpp>

#include "GameState.h"
#include "SplashState.h"



class IntroState : public GameState
{
public:

    virtual void draw(const float dt);
    virtual void update(const float dt);
    virtual void handleInput();

     IntroState(Game* game);

private:
    void loadSplash();
    sf::Clock clock;


};

#endif // INTROSTATE_H

#ifndef SPLASHSTATE_H
#define SPLASHSTATE_H

#include <SFML/Graphics.hpp>

#include "GameState.h"
#include "SplashState.h"



class SplashState : public GameState
{
public:

    virtual void draw(const float dt);
    virtual void update(const float dt);
    virtual void handleInput();

        SplashState(Game* game);


private:
    void loadMainMenu();
    sf::Clock clock;
    sf::Texture load;
    sf::Sprite sprite;

    sf::Texture tittle;
    sf::Sprite sprites;



};
#endif // SPLASHSTATE_H

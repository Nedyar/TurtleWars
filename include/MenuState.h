#ifndef MENUSTATE_H
#define MENUSTATE_H


#include <SFML/Graphics.hpp>

#include "GameState.h"

#include "menu.h"
  //we will be deriving this abstract classes functions.

class MenuState : public GameState  //make GameState functions public to this class so we can derive it's functions.
{
public:
    //constructor (compiler will automatically make a default one)
    MenuState(Game* game);

    //the three functions are teh three things we must do.
    virtual void draw(const float dt);
    virtual void update(const float dt);
    virtual void handleInput();

private:
    //let's make a view for this just in case we want it
    sf::Clock clock;
    sf::View view;
    sf::Texture tex;
    sf::Sprite sprite;
    //this will be used to change the game state to the "Play the actual fucking game" state.
    void loadgame();
    void loadcontrols();
};
#endif // MENUSTATE_H

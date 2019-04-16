#ifndef GAME_H
#define GAME_H

#include <State.h>
#include <stack>
#include "SFML/Graphics.hpp"

class Game
{
public:
    //constructor and deconstructor
    static Game* instance();
    ~Game();

    //functions for changing game state
    void pushState(State* state);
    void popState();

    //function to get the current State (note this function must be a pointer)
    State* CurrentState();

    //game loop function
    void gameLoop();
    void handleEvents(sf::RenderWindow &app);
    void update();
    void draw(sf::RenderWindow &app);

    //sfml window
    sf::RenderWindow window;

protected:
    Game();

private:
    static Game* pinstance;
    std::stack<State*> states;


};
#endif // GAME_H

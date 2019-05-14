#ifndef GAME_H
#define GAME_H

#include <State.h>
#include <stack>
#include <motorSFML.h>

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

    //sfml window
    sf::RenderWindow window;

protected:
    Game();

private:
    static Game* pinstance;
    std::stack<State*> states;
    motorSFML *motor;

};
#endif // GAME_H

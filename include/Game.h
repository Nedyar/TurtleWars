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

    void resetPoints();
    void addPoint(int player);
    int* getPoints();

    void resetGames();
    void addGame();
    int getGames();

    int winner();

    void setNPlayers(int n);
    int getNPlayers();

    //game loop function
    void gameLoop();

protected:
    Game();

private:
    static Game* pinstance;
    std::stack<State*> states;
    motorSFML *motor;

    int* points = new int[4];
    int games = 0;
    int nCharacters = 4;

};
#endif // GAME_H

#ifndef PAUSESTATE_H
#define PAUSESTATE_H

#include "GameState.h"
class PauseState : public GameState
{
public:

    PauseState(Game* game);

     void draw(const float dt);
     void update(const float dt);
     void handleInput();



private:

    sf::Clock clock;
    void resumeGame();
    void loadMainMenu();
    void loadcontrols();
    //void exitGame();

};


#endif // PAUSESTATE_H

#ifndef PAUSESTATE_H
#define PAUSESTATE_H

#include <State.h>
#include <Menu.h>


class PauseState : public State
{
public:
    PauseState();
    virtual ~PauseState();

    void handleEvents() override;
    void update() override;
    void draw() override;

private:
    int action;
    Menu menu = Menu("Resume","Skip Level","Back to Menu");

    sf::Clock clock;
    void resumeGame();
    void loadMainMenu();
    void loadcontrols();
};

#endif // PAUSESTATE_H

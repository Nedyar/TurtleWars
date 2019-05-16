#ifndef INTROSTATE_H
#define INTROSTATE_H

#include <State.h>
#include <MainMenu.h>

class IntroState : public State
{
public:
    IntroState();
    virtual ~IntroState();

    void handleEvents() override;
    void update() override;
    void draw() override;

private:
    const int INTRO_TIME = 6;
    sf::Clock clock;
};

#endif // INTROSTATE_H

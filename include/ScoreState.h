#ifndef SCORESTATE_H
#define SCORESTATE_H

#include <State.h>


class ScoreState : public State
{
public:
    ScoreState();
    virtual ~ScoreState();

    void handleEvents() override;
    void update() override;
    void draw() override;

    void loadLevel();
    void loadMainMenu();

private:
    sf::Clock clock;
    sf::Font font;
    sf::Text scoreText;

    int winner = -1;
};

#endif // SCORESTATE_H

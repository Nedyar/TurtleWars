#ifndef SPLASHSTATE_H
#define SPLASHSTATE_H

#include <State.h>



class SplashState : public State
{
public:
    SplashState();
    virtual ~SplashState();

    void handleEvents() override;
    void update() override;
    void draw() override;

protected:

private:
    sf::Clock clock;
    sf::Font font;
    sf::Text presskey;
    const int SPLASH_TIME = 20;

    void loadLevel();
};

#endif // SPLASHSTATE_H

#ifndef CONTROLSSTATE_H
#define CONTROLSSTATE_H

#include <State.h>
#include <Texture.h>
#include <Sprite.h>


class ControlsState : public State
{
public:
    ControlsState();
    virtual ~ControlsState();

    void handleEvents() override;
    void update() override;
    void draw() override;

private:

    Texture* texture;
    Sprite* sprite;

    int action = 0;

    sf::Text controls;
    sf::Text controlsKeyboard;
    sf::Font font;
};

#endif // CONTROLSSTATE_H

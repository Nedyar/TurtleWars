#ifndef MAINMENU_H
#define MAINMENU_H

#include <State.h>
#include <Menu.h>


class MainMenu : public State
{
public:
    MainMenu();
    virtual ~MainMenu();

    void handleEvents() override;
    void update() override;
    void draw() override;

private:
    int action;

    Menu menu = Menu("Play","Controls","Exit");
    sf::Clock clock;

    void loadgame();
    void loadcontrols();
};

#endif // MAINMENU_H

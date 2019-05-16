#include "motorSFML.h"

motorSFML* motorSFML::pInstance = 0;

motorSFML::motorSFML()
{
    window.create(sf::VideoMode(WIDTH, HEIGHT), "TurtleWars");
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);
}

motorSFML::~motorSFML()
{
    delete pInstance;
}

motorSFML* motorSFML::Instance()
{
    if(pInstance == 0)
        pInstance = new motorSFML();
    return pInstance;
}

void motorSFML::clean()
{
    window.clear();
}

void motorSFML::draw(sf::Sprite *sprite)
{
    window.draw(*sprite);
}

void motorSFML::draw(sf::Text text)
{
    window.draw(text);
}

void motorSFML::draw(sf::RectangleShape polygon)
{
    window.draw(polygon);
}

void motorSFML::display()
{
    window.display();
}

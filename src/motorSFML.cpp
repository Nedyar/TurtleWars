#include "motorSFML.h"

motorSFML* motorSFML::pInstance = 0;

motorSFML::motorSFML()
{

}

motorSFML::~motorSFML()
{
    delete pInstance;
}

motorSFML* motorSFML::Instance()
{
    if(pInstance == 0) {
        pInstance = (motorSFML*)malloc(sizeof(motorSFML));
        pInstance = new motorSFML();
    }

    return pInstance;
}

void motorSFML::clean(sf::RenderWindow &window)
{
    window.clear();
}

void motorSFML::draw(sf::RenderWindow &window, sf::Sprite *sprite)
{
    window.draw(*sprite);
}

void motorSFML::display(sf::RenderWindow &window)
{
    window.display();
}

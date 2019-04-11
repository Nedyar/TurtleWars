#ifndef MOTORSFML_H
#define MOTORSFML_H

#include <SFML/Graphics.hpp>


class motorSFML
{
    public:
        static motorSFML* Instance();
        ~motorSFML();
        void draw(sf::RenderWindow &window, sf::Sprite *sprite);
        void display(sf::RenderWindow &window);
        void clean(sf::RenderWindow &window);

    protected:
        motorSFML();
        motorSFML(const motorSFML&);
        motorSFML &operator= (const motorSFML&);

    private:
        static motorSFML* pInstance;
};

#endif // MOTORSFML_H

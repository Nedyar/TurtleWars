#ifndef BULLET_H
#define BULLET_H
#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>

class Bullet
{
    public:
        Bullet(double posx, double posy, double ang, double maxLen);
        virtual ~Bullet();
        void update();
        void render(sf::RenderWindow &app);

        double maxLength;
        double posiniX;
        double posiniY;
        sf::Sprite bulletSprite;
        sf::Texture bulletTexture;
    protected:

    private:

        double angle;

        double vel;
};

#endif // BULLET_H

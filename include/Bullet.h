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

    protected:

    private:
        sf::Sprite bulletSprite;
        sf::Texture bulletTexture;
        double angle;
        double maxLength;
        double posiniX;
        double posiniY;
        double vel;
};

#endif // BULLET_H

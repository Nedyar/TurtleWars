#ifndef BULLET_H
#define BULLET_H

const int VEL = 15;

#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>

class Bullet
{
public:
    Bullet(double posx, double posy, double ang, double maxLen);
    virtual ~Bullet();
    void update();
    void draw(sf::RenderWindow &app);

protected:

private:
    double maxLength = 0;
    double posiniX = 0;
    double posiniY = 0;
    sf::Sprite bulletSprite;
    sf::Texture bulletTexture;
    double angle = 0;
    double vel = 0;
};

#endif // BULLET_H

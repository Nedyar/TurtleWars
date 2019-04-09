#ifndef BULLET_H
#define BULLET_H
#include <SFML/Graphics.hpp>

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
};

#endif // BULLET_H

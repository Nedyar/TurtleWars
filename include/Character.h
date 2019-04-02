#ifndef CHARACTER_H
#define CHARACTER_H

#include <Weapon.h>
#include <SFML/Graphics.hpp>


class Character
{
    public:
        Character(int number);
        virtual ~Character();

        int getPlayer();
        Weapon* getWeapon();
        bool shoot();
        bool hasWeapon();

        void walk(bool right);
        bool jump();
        bool crouch();
        void standUp();

        void draw(sf::RenderWindow &app);
        void update();

        // Will deprecate
        sf::Sprite getSprite();

    protected:

    private:
        int player;
        Weapon* weapon;
        bool has_weapon;


        float pos;
        bool walking;
        bool facingLeft;
        bool jumping;
        bool onGround;
        bool crouching;
        bool sliding;

        // Will deprecate
        double yJumpedFrom;
        sf::Sprite sprite;
        sf::Texture texture;
};

#endif // CHARACTER_H

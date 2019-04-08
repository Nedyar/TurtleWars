#ifndef CHARACTER_H
#define CHARACTER_H

#include <Weapon.h>
#include <SFML/Graphics.hpp>
#include <Physics2D.h>


class Character
{
    public:
        Character(int player);
        virtual ~Character();

        int getPlayer();
        Weapon* getWeapon();
        bool shoot();
        bool hasWeapon();

        void walk(bool right);
        bool jump();
        bool crouch();
        void standUp();
        void die();

        bool dropWeapon();
        bool takeWeapon(Weapon* weapon);

        void draw(sf::RenderWindow &app);
        void update();

        // Will deprecate
        sf::Sprite getSprite();

    protected:

    private:
        int player;
        Weapon* weapon;
        bool has_weapon;


        float posture;
        bool walking;
        bool facingLeft;
        bool jumping;
        bool onGround;
        bool crouching;
        bool sliding;
        bool dead;

        Body *body;

        // Will deprecate
        double yJumpedFrom;
        sf::Sprite sprite;
        sf::Texture texture;
};

#endif // CHARACTER_H

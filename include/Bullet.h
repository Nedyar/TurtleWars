#ifndef BULLET_H
#define BULLET_H

const int VEL = 7;

#include <SFML/Graphics.hpp>
#include <math.h>
#include <Body.h>
#include <Collidable.h>
#include <Sprite.h>
#include <Texture.h>
#include <math.h>

class Bullet : public Collidable
{
public:
    Bullet(double posx, double posy, double ang, double maxLen);
    virtual ~Bullet();
    void update();
    void draw();
    int getId() override;
    void deleteMe();
    //Body* body = nullptr;

protected:

private:
    double maxLength = 0;
    double posiniX = 0;
    double posiniY = 0;
    Sprite* bulletSprite;
    Texture* bulletTexture;
    double angle = 0;
    double vel = 0;
    bool mustDelete = false;
    //Body* body = nullptr;
};

#endif // BULLET_H

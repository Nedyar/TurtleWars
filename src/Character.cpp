#include "Character.h"
#include "Character.h"
#include <Level.h>
#include <typeindex>
#include <motorSFML.h>

//#include <iostream>
//using namespace std;

Character::Character(int n, int posx, int posy)
{
    id = 1;
    player = n;
    xPosture = 0;
    yPosture = 0;
    weapon = nullptr;
    weaponSpawnerOver = nullptr;
    walking = false;
    facingLeft = false;
    mustFace = false;
    jumping = false;
    onGround = false;
    crouching = false;
    sliding = false;
    dead = false;
    fakingDead = false;
    mustDie = false;
    lookingUp = false;

    // will deprecate
    switch (player)
    {
    case 1:
        texture = new Texture("img/move.png"); //texture.loadFromFile("img/move.png");
        break;
    case 2:
        texture = new Texture("img/move_red.png");
        break;
    case 3:
        texture = new Texture("img/move_blue.png");
        break;
    default:
        texture = new Texture("img/move_yellow.png");
        break;
    }
    armTexture = new Texture("img/arm.png");

    sprite = new Sprite(*texture->getTexture());
    armSprite = new Sprite(*armTexture->getTexture());

    //sf::IntRect rect = sf::IntRect(0,0,32,32);
    sprite->setTextureRect(0,0,32,32);
    sprite->setOrigin(sprite->getLocalBounds().width/2,sprite->getLocalBounds().height/2);
    sprite->setPosition(posx,posy);

    //rect = sf::IntRect(0,0,9,8);
    armSprite->setTextureRect(0,0,9,8);
    armSprite->setOrigin(armSprite->getLocalBounds().width/2,armSprite->getLocalBounds().height/2);
    armSprite->setPosition(posx,posy);
    width = sprite->getLocalBounds().width;
    height = sprite->getLocalBounds().height;

    //optencion del body
    body = Physics2D::Instance()->createCharacterBody(posx,posy,width,height);
    body->setUserData(this);

    font.loadFromFile("fonts/majorforce.ttf");
    textWinner.setFont(font);
    textWinner.setString("+1");
    textWinner.setCharacterSize(18);

    musicCharger();
}

Character::~Character()
{

}

int Character::getPlayer()
{
    return player;
}

Weapon* Character::getWeapon()
{
    return weapon;
}

Body* Character::getBody()
{
    return body;
}

bool Character::shoot()
{
    if (weapon != nullptr)
    {
        return weapon->shoot();
    }
    else
        return false;
}

bool Character::hasWeapon()
{
    return weapon != nullptr;
}

void Character::swapWeapon()
{
    if (weapon == nullptr)
        takeWeapon();
    else
        dropWeapon();
}

bool Character::dropWeapon()
{
    if (weapon != nullptr)
    {
        Level* level = Level::instance();
        level->addWeapon(weapon);


        weapon->resetClock();
        weapon->setOwner(nullptr);
        weapon->createBody();

        if (lookingUp)
            weapon->setYVelocity(-JUMP_FORCE);
        else
        {
            int xDir = 1 - facingLeft*2;
            weapon->setXVelocity(body->getBody()->GetLinearVelocity().x+4*xDir);
        }

        weapon = nullptr;

        //delete weapon;
        return true;
    }
    return false;
}

bool Character::takeWeapon()
{

    if (weapon == nullptr)
    {

        Weapon* newWeapon = nullptr;

        if (!weaponsOver.empty())
        {
            pickupsound.play();
            //cout << "estoy sobre arma" << endl;
            Weapon* weaponOver = weaponsOver.front();
            weaponsOver.erase(weaponsOver.begin());

            Level::instance()->removeWeapon(weaponOver);
            newWeapon = weaponOver;
            weaponOver = nullptr;
        }
        else if (weaponSpawnerOver != nullptr)
        {

            newWeapon = weaponSpawnerOver->takeWeapon();
        }

        if (newWeapon != nullptr)
        {
            pickupsound.play();

            newWeapon->setOwner(this);
            weapon = newWeapon;
            weapon->deleteBody();
            //cout << "Arma equipada" << endl;
            return true;
        }
    }

    //cout << "Arma no equipada" << endl;;

    return false;
}

void Character::setWeaponSpawnerOver(WeaponSpawner* newWS)
{
    weaponSpawnerOver = newWS;
}

void Character::addWeaponOver(Weapon* newWeapon)
{
    weaponsOver.push_back(newWeapon);
}

void Character::removeWeaponOver(Weapon* newWeapon)
{
    for (int i = 0; i < weaponsOver.size(); i++)
    {
        if (weaponsOver.at(i) == newWeapon)
        {
            weaponsOver.erase(weaponsOver.begin()+i);
            break;
        }
    }
}

void Character::lookUp()
{
    lookingUp = true;
}

void Character::startWalking(bool left)
{
    if (!dead)
    {
        fakingDead = false;
        walking = true;
        mustFace = left;
        crouchplayed=false;
    }
}

void Character::stopWalking()
{
    //cout << "Me paro" << endl;
    walking = false;
}

bool Character::jump()
{
    if (!dead && onGround && !jumping)
    {
        body->getBody()->SetLinearVelocity((b2Vec2(body->getBody()->GetLinearVelocity().x,-JUMP_FORCE)));
        xPosture = 0;
        standUp();
        fakingDead = false;
        jumping = true;
        onGround = false;

        jumpsound.play();
    }
}

bool Character::crouch()
{
    if (!dead && !crouching)
    {
        fakingDead = false;
        crouching = true;

        double vel = body->getBody()->GetLinearVelocity().x;
        if (vel != 0)
        {
            sliding = true;
            xPosture = 1;
        }

        return true;
    }

    return false;
}

void Character::standUp()
{
    if (!dead)
    {
        crouching = false;
        sliding = false;

    }
}

void Character::kill()
{
    mustDie = true;
}

void Character::die()
{
    stopWalking();
    fakingDead = false;
    dropWeapon();
    dead = true;

    if(deathplayed==false)
    deathsound.play();

    deathplayed=true;
}

void Character::fakeDie()
{
    if (!dead)
    {
        stopWalking();
        dropWeapon();
        fakingDead = true;


        if(crouchplayed==false)
        crouchsound.play();

        crouchplayed=true;
    }
}

void Character::draw()
{
    motorSFML *motor = motorSFML::Instance();
    //app.draw(sprite);
    motor->draw(sprite->getSprite());
    if (weapon != nullptr)
        weapon->draw();
    if (!dead && !fakingDead)
        motor->draw(armSprite->getSprite()); //app.draw(armSprite);
    if(winner)
    {
        textWinner.setPosition(sprite->getPosition().x-10, sprite->getPosition().y-40);
        motor->draw(textWinner);
    }
}

void Character::update()
{
//Cambiar body cuando se agacha

//    cout << "Cosas locas" << endl;
    if((crouching || dead || fakingDead) && bigBody){
        //hacer pequeño
        b2Vec2 velo = body->getBody()->GetLinearVelocity();
        World::Instance()->destroyBody(body->getBody());
        body = Physics2D::Instance()->createCharacterBody(body->getPositionX(),body->getPositionY()+(height/4),width,height/2, 0.005);
        body->getBody()->SetLinearVelocity(velo);
        body->setUserData(this);

        bigBody = false;
//        cout << "Me agacho una vez" << endl;

    }
    if(!crouching && !fakingDead && !dead && !bigBody){
        //hacer grande
        b2Vec2 velo = body->getBody()->GetLinearVelocity();
        World::Instance()->destroyBody(body->getBody());
        body = Physics2D::Instance()->createCharacterBody(body->getPositionX(),body->getPositionY(),width,height);
        body->getBody()->SetLinearVelocity(velo);
        body->setUserData(this);
        bigBody = true;
//        cout << "Me levanto una vez" << endl;
    }
//    cout << "Cosas locas" << endl;



    if (!sliding)
        facingLeft = mustFace;

        //-------------------------------Correccion Spider Turtle
    xPositionLastOld = xPositionOld;
    xPositionOld = xPositionLast;
    xPositionLast = xPositionNew;
    xPositionNew = body->getPositionX();

    double last = xPositionLastOld+xPositionOld;
    double next = xPositionLast+xPositionNew;

    lastOldFacingLeft = oldFacingLeft;
    oldFacingLeft = lastFacingLeft;
    lastFacingLeft = facingLeft;

    if(walking && !first){
       if(last == next){//si esta chocando contra algo, quitar fuerzas
            cancelForces = true;
        }
    }
    int lastFacing = lastOldFacingLeft +oldFacingLeft;
    int newFacing = lastFacingLeft + facingLeft;

    first = false;
    if(!walking || lastFacing != newFacing){
        first = true;
        cancelForces = false;
    }
     //-------------------------------Correccion Spider Turtle FIN

    //para la muerte por caida al llegar al limite de abajo
    if(sprite->getPosition().y>LINE_OF_DEATH)
    {
        mustDie=true;
    }

    if (mustDie)
        die();

    if (body->getBody()->GetLinearVelocity().y != 0)
        onGround = false;
    else
        onGround = true;

    if (sliding)
    {
        xPosture = 0;
        yPosture = 2;
    }
    else if (crouching)
    {
        if (xPosture < 1 || (int)xPosture > 2)
            xPosture = 1;
        else if (xPosture < 2)
            xPosture += .5;

//        cout << xPosture << endl;


        yPosture = 2;
    }
    else if (walking)
    {
        yPosture = 0;
        xPosture += .2;

        if (xPosture >= 8)
        {
            xPosture = 0;
        }

        float str = 1.5 - facingLeft*3;

        if(!cancelForces){
            body->getBody()->SetLinearVelocity(b2Vec2(str,body->getBody()->GetLinearVelocity().y));
        }else{
            body->getBody()->SetLinearVelocity(b2Vec2(0,body->getBody()->GetLinearVelocity().y));
        }

    }
    else
    {
        yPosture = 0;
        xPosture = 0;
    }

    if (jumping && !crouching)
    {
        yPosture = 1;

        if (body->getBody()->GetLinearVelocity().y < 0)
        {
            if (body->getBody()->GetLinearVelocity().y < -2.25)
                xPosture = 0;
            else if (body->getBody()->GetLinearVelocity().y < -1.5)
                xPosture = 1;
            else if (body->getBody()->GetLinearVelocity().y < -0.75)
                xPosture = 2;
            else
                xPosture = 3;
        }
        else
        {
            jumping = false;
        }
    }
    else if (!onGround && !crouching)
    {
        yPosture = 1;

        if (body->getBody()->GetLinearVelocity().y > 0)
        {
            if (body->getBody()->GetLinearVelocity().y < 0.75)
                xPosture = 4;
            else if (body->getBody()->GetLinearVelocity().y < 1.5)
                xPosture = 5;
            else if (body->getBody()->GetLinearVelocity().y < 2.25)
                xPosture = 6;
            else
                xPosture = 7;
        }
    }

    if (dead || fakingDead)
    {
        yPosture = 3;
        xPosture = 0;
    }

    int armPosY = body->getPositionY()+yDifArm;
    if (crouching)
        armPosY += 3;

    int intX = 0;
    if (weapon != nullptr)
    {
        intX = 9;

        int modx = 0;
        int mody = 0;

        if (typeid(dynamic_cast<Grenade*>(weapon)) == typeid(Gun*))
        {
            modx = 3;
            mody = 4.2;
        }
        else if (typeid(dynamic_cast<Grenade*>(weapon)) == typeid(Grenade*))
        {
            modx = 2.5;
            mody = 4;
        }
        else
        {
            modx = 4;
            mody = 5;
        }


        if (facingLeft)
        {
            weapon->setFacingLeft(true);
            modx *= -1;
        }
        else
            weapon->setFacingLeft(false);

        if (crouching)
            weapon->setPos(sprite->getPosition().x+modx,sprite->getPosition().y+3+mody);
        else
            weapon->setPos(sprite->getPosition().x+modx,sprite->getPosition().y+mody);


        weapon->update();


    }

    //sf::IntRect bodyRect = sf::IntRect(32*((int)xPosture),yPosture*32,32,32);
    sprite->setTextureRect(32*((int)xPosture),yPosture*32,32,32);
    sprite->setPosition(body->getPositionX(),body->getPositionY());
    if(crouching || fakingDead || dead){
    //correccion del sprite cuando esta agachado, muerto, fakedead
        sprite->setPosition(body->getPositionX(),body->getPositionY()-height/4);
    }

    //sprite.setRotation(body->getAngle());

    int xDir = 1- facingLeft*2;

    //sf::IntRect armRect = sf::IntRect(intX,0,9,8);
    armSprite->setTextureRect(intX,0,9,8);
    armSprite->setPosition(body->getPositionX()-xDifArm*xDir,armPosY);

    if(crouching || fakingDead || dead){
    //correccion del sprite cuando esta agachado, muerto, fakedead
        armSprite->setPosition(body->getPositionX()-xDifArm*xDir,armPosY-7);
    }
    //armSprite.setRotation(body->getAngle());
    lookingUp = false;
    sprite->setScale(xDir,1);
    armSprite->setScale(xDir,1);
}

int Character::getId()
{
    return id;
}

bool Character::isDead()
{
    return dead;
}

void Character::musicCharger(){


    motorSFML::Instance()->loadSound("./sounds/jump.wav",sbjump,jumpsound);
    jumpsound.setVolume(59);
    motorSFML::Instance()->loadSound("./sounds/death.wav",sbdeath,deathsound);
    motorSFML::Instance()->loadSound("./sounds/cutOffQuack.wav",sbcrouch,crouchsound);
    crouchsound.setVolume(50);
    motorSFML::Instance()->loadSound("./sounds/hitBox.wav",sbpickup,pickupsound);


}


void Character::isWinner(){
    winner=true;
}

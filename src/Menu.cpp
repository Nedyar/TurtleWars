#include "Menu.h"

#include <cstring>

Menu::Menu(char nombre1[], char nombre2[], char nombre3[])
{
    font.loadFromFile("fonts/majorforce.ttf");
    sf::Color color(249,176,0);

    int x = 295;
    menu[0].setFont(font);

    menu[0].setCharacterSize(64);

    menu[0].setColor(sf::Color::White);
    menu[0].setString(nombre1);

    sf::FloatRect textRect = menu[0].getLocalBounds();
    menu[0].setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);

    menu[0].setPosition(960/2, x);

    menu[1].setFont(font);
    menu[1].setCharacterSize(64);
    menu[1].setColor(color);
    menu[1].setString(nombre2);

    sf::FloatRect textRect1 = menu[1].getLocalBounds();
    menu[1].setOrigin(textRect1.left + textRect1.width/2.0f, textRect1.top  + textRect1.height/2.0f);

    menu[1].setPosition(960/2, x+120);

    menu[2].setFont(font);
    menu[2].setCharacterSize(64);
    menu[2].setColor(color);
    menu[2].setString(nombre3);

    sf::FloatRect textRect2 = menu[2].getLocalBounds();
    menu[2].setOrigin(textRect2.left + textRect2.width/2.0f, textRect2.top  + textRect2.height/2.0f);

    menu[2].setPosition(960/2, x+235);

    selectedItemIndex = 0;
}

Menu::~Menu()
{
    //dtor
}

void Menu::draw(char name[])
{
    char type[]="pause";

    int num = strcmp(name,type);
    sf::Text tittle;
    tittle.setFont(font);

    if(num==0)
    {
        tittle.setString("Pause");
    }
    else
    {
        tittle.setString("Turtle Royal");
    }


    tittle.setCharacterSize(120);
    tittle.setColor(sf::Color::White);

    sf::FloatRect textRect1 = tittle.getLocalBounds();
    tittle.setOrigin(textRect1.left + textRect1.width/2.0f, textRect1.top  + textRect1.height/2.0f);

    tittle.setPosition(960/2,125);


    Texture* texture;
    if (num != 0)
        texture = new Texture("img/MenuPlay.png");
    else
        texture = new Texture("img/MenuPause.png");

    Sprite* sprite = new Sprite(*texture->getTexture());

    sprite->setOrigin(0,0);
    sprite->setPosition(0,0);


    motorSFML::Instance()->draw(sprite->getSprite());
    motorSFML::Instance()->draw(tittle);
    for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
    {
        motorSFML::Instance()->draw(menu[i]);
    }
}

void Menu::MoveUp()
{
    sf::Color color(249,176,0);
    menu[selectedItemIndex].setColor(color);
    if (selectedItemIndex - 1 >= 0)
        selectedItemIndex--;
    else
        selectedItemIndex = MAX_NUMBER_OF_ITEMS-1;
    menu[selectedItemIndex].setColor(sf::Color::White);
}

void Menu::MoveDown()
{
    sf::Color color(249,176,0);
    menu[selectedItemIndex].setColor(color);
    if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
        selectedItemIndex++;
    else
        selectedItemIndex = 0;
    menu[selectedItemIndex].setColor(sf::Color::White);
}

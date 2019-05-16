#ifndef MENU_H
#define MENU_H

#define MAX_NUMBER_OF_ITEMS 3

#include <motorSFML.h>
#include <Texture.h>
#include <Sprite.h>

class Menu
{
public:
    Menu(char nombre1[], char nombre2[], char nombre3[]);

    ~Menu();

    void draw(char name[]);
    void MoveUp();
    void MoveDown();
    int GetPressedItem()
    {
        return selectedItemIndex;
    }

private:
    int selectedItemIndex;
    sf::Font font;
    sf::Text menu[MAX_NUMBER_OF_ITEMS];

};
#endif // MENU_H

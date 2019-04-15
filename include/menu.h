#ifndef MENU_H
#define MENU_H


#include "SFML/Graphics.hpp"
#define MAX_NUMBER_OF_ITEMS 3

class Menu
{
public:
 Menu(char nombre1[], char nombre2[], char nombre3[]);

	~Menu();

	void draw(sf::RenderWindow &window, char name[]);
	void MoveUp();
	void MoveDown();
	int GetPressedItem() { return selectedItemIndex; }

private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];

    sf::Texture tex;
    sf::Sprite sprite;

};
#endif // MENU_H

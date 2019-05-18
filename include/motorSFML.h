#ifndef MOTORSFML_H
#define MOTORSFML_H

#include <SFML/Graphics.hpp>


class motorSFML
{
public:
    static motorSFML* Instance();
    ~motorSFML();
    void draw(sf::Sprite *sprite);
    void draw(sf::Text text);
    //sf::RectangleShape Polygon
    void draw(sf::RectangleShape polygon);
    void display();
    void clean();
    void setCamara(double x, double y, double widthCam, double heightCam);
    void resetCamara();

    sf::RenderWindow window;
    sf::View camara;

protected:
    motorSFML();
    motorSFML(const motorSFML&);
    motorSFML &operator= (const motorSFML&);

private:
    static motorSFML* pInstance;

    const int WIDTH = 960;
    const int HEIGHT = 640; //640
};

#endif // MOTORSFML_H

#ifndef MOTORSFML_H
#define MOTORSFML_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


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

    void setMusic(char music[], float x);
    void loadSound(char sound[],sf::SoundBuffer &sb, sf::Sound &saux);
    void loadSound(char sound[]);

    sf::RenderWindow window;
    sf::View camara;
    sf::Music musica;
    sf::Sound sonido;
    sf::SoundBuffer buffer;

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

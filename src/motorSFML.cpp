#include "motorSFML.h"
#include <iostream>

motorSFML* motorSFML::pInstance = 0;

motorSFML::motorSFML()
{
    window.create(sf::VideoMode(WIDTH, HEIGHT), "TurtleWars");
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);

    sf::View camara( sf::FloatRect(0, 0, WIDTH, HEIGHT) );
    camara.setViewport( sf::FloatRect(0, 0, 1, 1) );
    window.setView(camara);

}

motorSFML::~motorSFML()
{
    delete pInstance;
}

motorSFML* motorSFML::Instance()
{
    if(pInstance == 0)
        pInstance = new motorSFML();
    return pInstance;
}

void motorSFML::clean()
{
    window.clear();
}

void motorSFML::draw(sf::Sprite *sprite)
{
    window.draw(*sprite);
}

void motorSFML::draw(sf::Text text)
{
    window.draw(text);
}

void motorSFML::draw(sf::RectangleShape polygon)
{
    window.draw(polygon);
}

void motorSFML::display()
{
    window.display();
}

void motorSFML::setMusic(char music[],float x)
{

    if (!musica.openFromFile(music))
    {
    //HANDLE ERROR
    }
    musica.setLoop(true);
    musica.setVolume(x);
    musica.play();
}
//ESTE METODO ESTA PARA EL CARGADOR DE SONIDOS DEL PERSONAJE, QUE NECESITA DIFERENTES BUFFERS
void motorSFML::loadSound(char sound[],sf::SoundBuffer &sb, sf::Sound &saux)
{
    if (!sb.loadFromFile(sound))
    {
    //HANDLE ERROR
    }
    saux.setBuffer(sb);
    //saux.play();
}
//ESTE ESTA SOLO PARA LOS DEL MENU, QUE ES EL MISMO SONIDO DE TRANSICION, Y NO REQUIERE DIFERENTES BUFFER
 void motorSFML::loadSound(char sound[])
{
    if (!buffer.loadFromFile(sound))
    {
    //HANDLE ERROR
    }
    sonido.setBuffer(buffer);
    sonido.play();
}

void motorSFML::setCamara(double x, double y, double widthCam, double heightCam)
{

    //std::cout << camara.getCenter().x << "  " << camara.getCenter().y << std::endl;
    camara.setSize(widthCam, heightCam);
    camara.setCenter(x,y);
    window.setView(camara);
}

void motorSFML::resetCamara() {
    camara.setCenter(WIDTH/2,HEIGHT/2);
    camara.setSize(WIDTH,HEIGHT);
    window.setView(camara);
}

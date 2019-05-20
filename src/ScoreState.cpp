#include "ScoreState.h"

#include <Game.h>
#include <Level.h>
#include <motorSFML.h>
#include <string>
#include <IntroState.h>

ScoreState::ScoreState()
{
    font.loadFromFile("fonts/majorforce.ttf");

    scoreText.setFont(font);
    scoreText.setString("SCORE");
    scoreText.setCharacterSize(120);
    scoreText.setColor(sf::Color::White);
    scoreText.setOrigin(634/2,41/2);
    scoreText.setPosition(960/2,100);
    sf::FloatRect textRect1 = scoreText.getLocalBounds();
    scoreText.setOrigin(textRect1.left + textRect1.width/2.0f, textRect1.top  + textRect1.height/2.0f);
}

ScoreState::~ScoreState()
{
    //dtor
}

void ScoreState::handleEvents()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
        if(this->clock.getElapsedTime().asSeconds()>2)
            if (Game::instance()->winner() == -1)
                loadLevel();
            else
                loadMainMenu();
}

void ScoreState::loadLevel()
{
    Game::instance()->popState();
    Game::instance()->pushState(Level::instance());
}

void ScoreState::loadMainMenu()
{
    Game::instance()->popState();
    Game::instance()->pushState(new IntroState());
}

void ScoreState::update()
{
}

void ScoreState::draw()
{
    motorSFML::Instance()->resetCamara();
    motorSFML::Instance()->draw(scoreText);

    for (int i = 0; i < Game::instance()->getNPlayers(); i++)
    {
        sf::Text player;

        player.setFont(font);


        std::string s = "Player " + std::to_string(i+1) + ": " + std::to_string(Game::instance()->getPoints()[i]);

        player.setString(s);
        player.setCharacterSize(60);
        sf::Color color;

        if (i == 0)
            color = sf::Color::Green;
        else if (i == 1)
            color = sf::Color::Red;
        else if (i == 2)
            color = sf::Color::Blue;
        else
            color = sf::Color::Yellow;

        player.setColor(color);
        player.setOrigin(634/2,41/2);
        player.setPosition(960/2,150+95*(i+1));
        sf::FloatRect textRect1 = scoreText.getLocalBounds();
        player.setOrigin(textRect1.left + textRect1.width/2.0f, textRect1.top  + textRect1.height/2.0f);

        motorSFML::Instance()->draw(player);
    }

    sf::Text pressStart;

    pressStart.setFont(font);

    pressStart.setString("Press Start");
    pressStart.setCharacterSize(40);


    if((int)this->clock.getElapsedTime().asSeconds()%2==0)
    {
        pressStart.setColor(sf::Color::Transparent);

    }else
        pressStart.setColor(sf::Color::White);


    pressStart.setOrigin(634/2,41/2);
    pressStart.setPosition(960/2,600);
    sf::FloatRect textRect1 = pressStart.getLocalBounds();
    pressStart.setOrigin(textRect1.left + textRect1.width/2.0f, textRect1.top  + textRect1.height/2.0f);


    if (this->clock.getElapsedTime().asSeconds()>2)
    motorSFML::Instance()->draw(pressStart);

}

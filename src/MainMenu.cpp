#include "MainMenu.h"

#include <Game.h>
#include <SplashState.h>
#include <Level.h>

MainMenu::MainMenu()
{
    Game::instance()->resetPoints();
    Game::instance()->resetGames();
    Level::instance()->Restart();
}

MainMenu::~MainMenu()
{
    //dtor
}

void MainMenu::handleEvents()
{

    /* sf::Event event;

         while (motorSFML::Instance()->window.pollEvent(event))
         {
             switch (event.type)
             {
             case sf::Event::KeyReleased:
                 switch (event.key.code)
                 {
                 case sf::Keyboard::Up:
                     action = 1;
                     cout << "Arriba" << endl;
                     break;

                 case sf::Keyboard::Down:
                     action = 2;
                     break;

                 case sf::Keyboard::Return:
                     switch (menu.GetPressedItem())
                     {
                     case 0:
                         if(this->clock.getElapsedTime().asSeconds()>1)
                         {
                             loadgame();
                             Game::instance()->gameLoop();
                         }

                         break;
                     case 1:
                         loadcontrols();
                         break;
                     case 2:
                         motorSFML::Instance()->window.close();
                         break;
                     }

                     break;
                 }

                 break;
             case sf::Event::Closed:
                 motorSFML::Instance()->window.close();

                 break;

             }
         }

    */

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        action = 2;
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        action = 1;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
        action = 3;

    /*sf::Event event;

    while (motorSFML::Instance()->window.pollEvent(event))
        if (event.type == sf::Event::Closed)
                motorSFML::Instance()->window.close();*/
}




void MainMenu::update()
{
    if (action == 1)
        menu.MoveUp();
    else if (action == 2)
        menu.MoveDown();
    else if (action == 3)
    {

        switch (menu.GetPressedItem())
        {
        case 0:
            if(this->clock.getElapsedTime().asSeconds()>1)
                loadgame();
            break;
        case 1:
            loadcontrols();
            break;
        case 2:
            motorSFML::Instance()->window.close();
            break;
        }
    }
    action = 0;
//else

}


void MainMenu::draw()
{
    motorSFML::Instance()->resetCamara();
    menu.draw("");
}


void MainMenu::loadgame()
{
    Game::instance()->popState();
    Game::instance()->pushState(new SplashState());
    //Game::instance()->pushState(Level::instance(2,3));
}

void MainMenu::loadcontrols()
{

//    game->pushState(new ControlsState(this->game));

}

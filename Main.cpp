#include <Game.h>

int main()
{
    Game* game = Game::instance(); //create game object (so far this constructor just intiializes our window)

    game->gameLoop();

    return 0;
}

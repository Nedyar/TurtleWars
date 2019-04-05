#ifndef LEVEL_H
#define LEVEL_H

#include <State.h>
#include <Character.h>


class Level : public State
{
    public:
        static Level* instance();

        void handleEvents() override;
        void update() override;
        void draw(sf::RenderWindow &app) override;

        Character **players;

    protected:
        Level();
        virtual ~Level();

    private:
        static Level* pinstance;
};

#endif // LEVEL_H

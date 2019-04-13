#ifndef COLLIDABLE_H
#define COLLIDABLE_H

class Collidable
{
    public:
        virtual int getId() = 0;
    protected:
        int id = 0;
};

#endif // COLLIDABLE_H

#ifndef COLLIDABLE_H
#define COLLIDABLE_H

class Collidable
{
    public:
        virtual int getId() = 0;
    protected:
        int id;
};

#endif // COLLIDABLE_H

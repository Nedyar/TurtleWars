#include "Phisics2D.h"



Phisics2D* Phisics2D::instance = nullptr;

Phisics2D* Phisics2D::Instance(){
    if(!instance)
    {
        instance = new Phisics2D;
        printf("Init Physics!\n");
    }

    return instance;
}

Phisics2D::Phisics2D()
{
    //bod = new Body();
}


void Phisics2D::createBody(sf::Sprite &sprite){

    bod = new Body();

    std::cout << "postion x: "<< bod->getPositionX() <<std::endl;

}





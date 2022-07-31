#include "Rect.h"
#include "glob_SRC.h"



Rect::Rect()
{
    trigerAble = true;
    this->setFillColor(sf::Color::White);
    this->setOutlineColor(sf::Color::Red);
    this->setOutlineThickness(-10.f);
    this->setOutlineColor(sf::Color::Red);
    this->setSize(sf::Vector2f(100.f,100.f));
}

Rect::~Rect(){}

void Rect::autoSetPos()
{
     trigerAble = true;
     float x =  rand() % static_cast <int> (world_S.x - 100.f);
     float y =  rand() % static_cast <int> (world_S.y - 100.f);;

     this->setPosition(x,y);
     this->redefineColides();
}

void Rect::redefineColides()
{
      aX = this->getPosition().x - (this->getSize().x - 10)/2;
      bX = aX + this->getSize().x - 10;
      aY = this->getPosition().y - (this->getSize().y - 10)/2;;
      bY = aY + this->getSize().y - 10;

      centrX = this->getPosition().x - 10;
      centrY = this->getPosition().y - 10;
      touch_line = (this->getSize().x - 10)/2;

}

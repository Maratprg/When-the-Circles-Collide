#ifndef CIRCLE_H
#define CIRCLE_H

#include <SFML/Graphics.hpp>
#include <glob_SRC.h>

class Circle
{
 private:
    sf::Vector2f vec;
    sf::CircleShape first;
    sf::Vector2f CollidePoints [8];

    float radius;

    area::ID ar;
    direction::ID_X dirx;
    direction::ID_Y diry;

 public:
    Circle();
    ~Circle();
    void setArea(area::ID);
    void setVec(float x, float y);
    float getX() {return first.getPosition().x;};
    float getY() {return first.getPosition().y;};

    void autoSetPos();
    void setCollider();

    void moveVec(float x, float y);


    void setDirection(direction::ID_X x, direction::ID_Y y) {dirx = x; diry = y;};
    void setDirection(direction::ID_X x) {dirx = x;};
    void setDirection(direction::ID_Y y) {diry = y;};
    void reverseDir();
    void reverseAndForce(float l);

    direction::ID_X getDirectionX() {return dirx;};
    direction::ID_Y getDirectionY() {return diry;};

    void setRandColor();
    void setColor(sf::Color color);
    void setOutline(sf::Color color);

    sf::Vector2f getCollidePoints(int i); //get coordinate collider poits vector by giving the array index
    sf::CircleShape& getCircle();

    sf::Color getColor();

    float getRadius() {return first.getRadius();};
    sf::Vector2f& getVec() {return vec;};

    public:
        bool isReversed; // the boolean of a single collision with a player
        int score;       // a variable that gives scores
        int health;      // health value variable
  };


#endif // CIRCLE_H

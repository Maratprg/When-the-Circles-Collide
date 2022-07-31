#include "Circle.h"


Circle::Circle()
{
    vec.x = 60.f;
    vec.y = 60.f;
    radius = 0.05 * world_S.x;

    this->setRandColor();
    this->setCollider();

    first.setPosition(vec);
    first.setRadius(radius);

    dirx = direction::ID_X::LEFT;
    diry = direction::ID_Y::DOWN;

    // set value of bool of colide to false
    isReversed = false;

    score = 0; health = -1; // initialisation the variables health and score
}

Circle::~Circle() {}

sf::CircleShape& Circle::getCircle() {return first;}

void Circle::reverseDir()
{
    if (dirx == direction::ID_X::LEFT) { dirx = direction::ID_X::RIGHT; }
    else if (dirx == direction::ID_X::RIGHT) { dirx = direction::ID_X::LEFT; }
    else {};

    if (diry == direction::ID_Y::UP) { diry = direction::ID_Y::DOWN; }
    else if (diry == direction::ID_Y::DOWN) { diry = direction::ID_Y::UP; }
    else {};

}

void Circle::reverseAndForce(float l)
{
    if (dirx == direction::ID_X::LEFT) { dirx = direction::ID_X::RIGHT; }
    else if (dirx == direction::ID_X::RIGHT) { dirx = direction::ID_X::LEFT; }
    else {};

    if (diry == direction::ID_Y::UP) { diry = direction::ID_Y::DOWN; }
    else if (diry == direction::ID_Y::DOWN) { diry = direction::ID_Y::UP; }
    else {};

    // forced moving
    if (dirx == direction::ID_X::LEFT)  this->moveVec(- l,0.f); // cout << "DIR" << endl;
    if (dirx == direction::ID_X::RIGHT) this->moveVec(+ l,0.f); // cout << "DIR" << endl;
    if (diry == direction::ID_Y::UP)    this->moveVec(0.f,- l); // cout << "DIR" << endl;
    if (diry == direction::ID_Y::DOWN)  this->moveVec(0.f,+ l); // cout << "DIR" << endl;

}

void Circle::setArea(area::ID) {}

void Circle::setVec(float x, float y)
{
    vec.x = x; vec.y = y;
    this->setCollider();
    this->autoSetPos();
}

void Circle::autoSetPos()
{
    this->first.setPosition(vec.x,vec.y);
}

void Circle::setCollider()
{
    // reinitialization for collider points handler
    float centerX = vec.x + radius;
    float centerY = vec.y + radius;

    CollidePoints[0].x = centerX + radius;
    CollidePoints[0].y = centerY;

    CollidePoints[1].x = centerX + 0.7 * radius;
    CollidePoints[1].y = centerY + 0.7 * radius;

    CollidePoints[2].x = centerX;
    CollidePoints[2].y = centerY + radius;

    CollidePoints[3].x = centerX - 0.7 * radius;
    CollidePoints[3].y = centerY + 0.7 * radius;

    CollidePoints[4].x = centerX - radius;
    CollidePoints[4].y = centerY;

    CollidePoints[5].x = centerX - 0.7 * radius;
    CollidePoints[5].y = centerY - 0.7 * radius;

    CollidePoints[6].x = centerX;
    CollidePoints[6].y = centerY - radius;

    CollidePoints[7].x = centerX + 0.7 * radius;
    CollidePoints[7].y = centerY - 0.7 * radius;
}

void Circle::moveVec(float x, float y)
{
    vec.x = vec.x + x;
    vec.y = vec.y + y;
    this->setCollider();
    this->autoSetPos();
}

void Circle::setRandColor()
{
    int random = 1 + rand() % 9;
    if (random == 1) first.setFillColor(sf::Color::Green);
    if (random == 2) first.setFillColor(sf::Color::Blue);
    if (random == 3) first.setFillColor(sf::Color::Yellow);
    if (random == 4) first.setFillColor(sf::Color::Magenta);
    if (random == 5) first.setFillColor(sf::Color(50,150,150)); // smoothGreen
    if (random == 6) first.setFillColor(sf::Color(250,150,255)); // smoothPink
    if (random == 7) first.setFillColor(sf::Color(250,150,130)); // smoothOrange
    if (random == 8) first.setFillColor(sf::Color(135,135,135)); // smoothGrey
    if (random == 9) first.setFillColor(sf::Color(135,0,135)); // smoothPurple
}

void Circle::setColor(sf::Color color)
{
    first.setFillColor(color);
}

void Circle::setOutline(sf::Color color)
{
    first.setOutlineThickness(0.15 * radius);
    first.setOutlineColor(color);
}

sf::Vector2f  Circle::getCollidePoints(int i)
{
    sf::Vector2f ret(CollidePoints[i].x, CollidePoints[i].y);
    return ret;
}

sf::Color Circle::getColor()
{
    return first.getFillColor();
}


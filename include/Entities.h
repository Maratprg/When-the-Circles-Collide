#ifndef ENTITIES_H
#define ENTITIES_H

#include <SFML/Graphics.hpp>
#include "Circle.h"
#include "Rect.h"
#include "../JoyTextSource.h"

class Entities : sf::RenderWindow
{
    private:
        Circle Player;
        Circle circles[c_circles];

    public:
       Entities();
       ~Entities();

       void resetEntitiesPosition();

       int getCirclesSize();
       void setCirclesDirectPos();
       void setCirclesRandomDirections();
       void setCirclesRandomColor();

       void update_Entities();
       void brainwashCollide();
       void resetScoreHealthPlayer();

       void HandlePlayerInput(sf::Keyboard::Key key, bool isPressed);
       void gamePad();
       void keyBoard();
       void redifineKeys();

       sf::CircleShape& getDraw(int i);
       sf::CircleShape& getPlayer();

       sf::Vector2f get_Entity_CollidePoints(int number, int i);

       // direction variables
       bool player_Up;
       bool player_Down;
       bool player_Left;
       bool player_Right;

       bool flagMoovable;
       bool isKeyboard;

       // hypotinuze line for render colliders
       sf::Vertex line[2];
       void setLinePoints(float a, float b, float c, float d);

       int getPlayerHealth() {return Player.health;};
       void updatePlayerHealth(int i) { Player.health += i;};

       int getPlayerScore() {return Player.score;};
       void setPlayerScore(int i) {Player.score += i;};

       sf::Vector2f& getPlayerCoordinates();
       float getPlayerRadius() {return Player.getRadius();};

    public:
        Rect A;
        Rect B;
        sf::Clock clock; // managing time

    public:
        ResourseHandler res;

        sf::Sound soundWall [5];
        sf::Sound soundCollide;
        sf::Sound soundHealth;
        sf::Sound soundScore;

        bool sounder [4]; // sounds service(Wall, Collide, Health, Score)
        bool getballS[c_circles];
};

#endif // ENTITIES_H

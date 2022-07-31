#ifndef GLOB_SRC_H
#define GLOB_SRC_H

#include <SFML/Graphics.hpp>
#include <iostream>

//globall world sizes
static sf::Vector2f world_S (1200.f, 900.f);

//global circles counts
const int c_circles = 5;

//making global directions
namespace direction
{
    enum ID_X
    {
       RIGHT,
       LEFT,
    };
    enum ID_Y
    {
       UP,
       DOWN,
    };
}

// areas of circles positions
namespace area
{
    enum ID
    {
        TOP_L,
        TOP_R,
        BOT_L,
        BOT_R
    };
}

// specific scene namespaces
namespace specific_Scene
{
    enum ID
    {
        Scene_One,
        Scene_Two,
        Scene_Three,
        Enum_count
    };
}

//texture struct places
struct T_Text
{
    public:
        sf::Font font;

    public:
        sf::Text text1;
        sf::Text text2;
        sf::Text text3;

        sf::Text blinkInput1;
        sf::Text blinkInput2;

        sf::Text finalScore;

    public:
        T_Text();
        ~T_Text();
};

#endif // GLOB_SRC_H

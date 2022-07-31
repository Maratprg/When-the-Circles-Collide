#ifndef RECT_H
#define RECT_H

#include <SFML/Graphics.hpp>

// making class of health and score rectangles
class Rect : public sf::RectangleShape
{
    public:
        Rect();
        ~Rect();

        void autoSetPos();
        void redefineColides();
        void setTrigerAble(bool t) {trigerAble = t;};

    public:
        int health;
        int score;
        bool trigerAble;

    public:
        float aX;
        float bX;
        float aY;
        float bY;
        float centrX;
        float centrY;
        float touch_line;
};

#endif // RECT_H

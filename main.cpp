#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <typeinfo>
#include <cmath>
#include <sstream>

#include "glob_SRC.h"
#include "JoyTextSource.h"
#include "Circle.h"
#include "Rect.h"
#include "Game.h"


int main()
{
    srand(time(nullptr));

    Game game;
    game.run();

    return 0;
}

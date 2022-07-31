#ifndef GAME_H
#define GAME_H

#include "Entities.h"
#include <sstream>

class Game
{
    public:
            Game();
            ~Game();
        void run();
        void rebornEntities(); // dctor and reini Entity ctor

    private:
        void processEvents();
        void update();
        void render();

        void startMuz();
        void stopMuz();

        void checkSound();

        void checkInputOne(); // first view events

        void checkValuesTwo(); // game view events
        int finalScore; // final score value

    public:
        Entities entities;  // organizations of entities
        T_Text texty;       // organization of text structs

        sf::RenderWindow window;

        // making stream to create string to text struct
        std::stringstream ss;

        sf::Sprite scenePNG;
        specific_Scene::ID id;

        // time of FPS
        sf::Clock iternalCl;
};

#endif // GAME_H

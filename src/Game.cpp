#include "Game.h"


Game::Game () : window (sf::VideoMode(world_S.x,world_S.y), "When the CIRCLES COLLIDE.", sf::Style::Close)
{
    entities.setCirclesDirectPos();
    entities.setCirclesRandomDirections();

    for (int i = 0; i < 8; i ++)
    {
    std::cout << " array collider points at " << i << " x " << entities.get_Entity_CollidePoints(1,i).x << " y "
            << entities.get_Entity_CollidePoints(1,i).y << std::endl;
    }

    entities.clock.restart();

    // making first scene
    id = specific_Scene::ID::Scene_One;

}

Game::~Game () {}

void Game::run()
{
    // diagnostic sonds in game
    entities.soundScore.play();

    // the clock restarting when the player press enter
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    sf::Time timePerFrame = sf::seconds(1.f/60.f);

    // first view music
    this->startMuz();

    // first view texture
    scenePNG.setTexture(entities.res.getTexture(textures::ID::FirstScreen));

    // first restart of game time
    entities.clock.restart();

    // THE BASE GAME LOOP
    while (window.isOpen())
    {

            sf::Event event;
            while (window.pollEvent(event)) {  if (event.type == sf::Event::Closed) window.close();  }

      // first scene
      if(id == specific_Scene::ID::Scene_One)
      {
         this->checkInputOne();
         window.clear();
           if (entities.clock.getElapsedTime().asSeconds() < 0.75)
                {
                window.draw(scenePNG);
                }
           else
                {
                window.draw(scenePNG);
                window.draw(texty.blinkInput1);
                window.draw(texty.blinkInput2);
                }
       if (entities.clock.getElapsedTime().asSeconds() > 1.5) entities.clock.restart();
       window.display();
       }

      // second scene
      else if (id == specific_Scene::ID::Scene_Two)
      {
         // cout << " time before update " << timeSinceLastUpdate.asSeconds()<< endl;
         timeSinceLastUpdate += iternalCl.restart();
         // cout << " time sine update " << timeSinceLastUpdate.asSeconds() << endl;
         // keeping the game pad inputs
         entities.gamePad();
         // keeping the keyboar inputs
         entities.keyBoard();
         // window clear second scene
         window.clear();

                // rendering score and health units
                if (entities.A.trigerAble) window.draw(entities.A);
                if (entities.B.trigerAble) window.draw(entities.B);

                // rendering circles
                for (int i=0; i<c_circles; i++)
                    {
                    window.draw(entities.getDraw(i));
                    window.draw(entities.getPlayer());
                    window.draw(entities.line, 2, sf::Lines);
                    }

                // rendering health and score texts
                float var = entities.clock.getElapsedTime().asSeconds();

                    std::string metaString, outputString;
                    ss.clear();
                    ss << static_cast<int>(var);
                    ss >> metaString;
                    outputString = " Time     : " + metaString;
                    texty.text1.setString(outputString);

                    ss.clear();
                    ss << entities.getPlayerHealth();
                    ss >> metaString;
                    outputString = " Health   : " + metaString;
                    texty.text2.setString(outputString);

                    ss.clear();
                    ss << entities.getPlayerScore();
                    ss >> metaString;
                    outputString = " Score    : " + metaString;
                    texty.text3.setString(outputString);

                this->checkSound();

                window.draw(texty.text1);
                window.draw(texty.text2);
                window.draw(texty.text3);

            window.display();

            // rendering health and score units by its life cicle
            if ( entities.clock.getElapsedTime().asSeconds() > 10.f )
                    {
                        entities.clock.restart();
                        entities.A.autoSetPos();
                        entities.B.autoSetPos();

                       std::cout << " Player Coordinates X/Y  (un redius) " << entities.getPlayerCoordinates().x << " / "
                                    <<  entities.getPlayerCoordinates().y << " with radius "
                                    <<  entities.getPlayerCoordinates().x + entities.getPlayerRadius() << " / "
                                    <<  entities.getPlayerCoordinates().y + entities.getPlayerRadius() << std::endl;
                    };

            // до неотображенного обнавления отслеживаем события перехода на сцену 3
            // в классе Game запоминаем значения очков чтобы ниже итерации значения не поменялись
            this -> checkValuesTwo();

            while (timeSinceLastUpdate > timePerFrame)
                {
                        timeSinceLastUpdate -= timePerFrame;
                        for (int i=0; i<c_circles; i++)
                        {
                        entities.update_Entities();
                        }
                        entities.brainwashCollide();
                }
        }

      // third scene
      else if (id == specific_Scene::ID::Scene_Three)
      {
           this->checkInputOne();

           window.clear();

           if (entities.clock.getElapsedTime().asSeconds() < 0.75)
                {
                window.draw(scenePNG);
                }
           else
                {
                window.draw(scenePNG);
                window.draw(texty.finalScore);
                }
        if (entities.clock.getElapsedTime().asSeconds() > 1.5) entities.clock.restart();
        window.display();


     }

       else {};

    } //END OG GAMELOOP

} // end of run


void Game::rebornEntities() {}

void Game::startMuz()
{
   entities.res.getMusic().setVolume(18);
   entities.res.getMusic().play();
   entities.res.getMusic().setLoop(true);
}

void Game::stopMuz() {entities.res.getMusic().stop();}

void Game::checkSound()
{
  for (int i=0; i<c_circles; i++)
        {
            if (entities.getballS[i]) { entities.soundWall[i].play(); entities.getballS[i] = false; };
        }

   if (entities.sounder[0]) entities.soundCollide.play(); entities.sounder[0] = false;
   if (entities.sounder[1]) entities.soundHealth.play(); entities.sounder[1] = false;
   if (entities.sounder[2]) entities.soundScore.play(); entities.sounder[2] = false;

}

// making first and last views and the stages
void Game::checkInputOne()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        id = specific_Scene::ID::Scene_Two;
        this->stopMuz();
        entities.resetScoreHealthPlayer();
        iternalCl.restart();
    }
}

void Game::checkValuesTwo()
{
   if ( entities.getPlayerHealth() < -10 )
        {
          int finalScore = entities.getPlayerScore(); // keeping the score value

          entities.resetEntitiesPosition(); // circles goes start position
          entities.setCirclesRandomColor(); // circles change colors

          std::string outputString;
                    ss.clear();
                    ss << static_cast<int>(finalScore);
                    ss >> outputString;

          texty.finalScore.setString(outputString);
          scenePNG.setTexture(entities.res.getTexture(textures::ID::LastScreen)); // final view texture loading
          this->startMuz();
          id = specific_Scene::ID::Scene_Three; // goes to final scene
        }
}

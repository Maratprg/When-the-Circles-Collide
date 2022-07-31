#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include "JoyTextSource.h"



ResourseHandler::ResourseHandler()
{
this->loadMusic();
this->loadSoundsBuff();
this->loadTextures();
}

ResourseHandler::~ResourseHandler() {}

void ResourseHandler::setNodeItem(textures::ID id, std::string file_Path)
{
   nodulus[id].loadFromFile(file_Path);
}

void ResourseHandler::showNodeItem(textures::ID id)
{
    std::cout << "texture ID " << id << std::endl;
}
sf::Texture& ResourseHandler::getTexture(textures::ID id) { return nodulus[id]; }


void ResourseHandler::setBuff(shortSound::ID id, std::string file_Path)
{
  //sound buffer map container
  sf::SoundBuffer b;
  b.loadFromFile(file_Path);
  bMap[id] = b;

  //sounds map container
  sf::Sound s;
  s.setBuffer(b);
  soMap[id] = s;
}


sf::SoundBuffer& ResourseHandler::getBuff(shortSound::ID id)
{
  std::map <shortSound::ID, sf::SoundBuffer> :: iterator it;
  it = bMap.find(id);
  return it->second;
}

sf::Sound& ResourseHandler::getSound(shortSound::ID id)
{
   std::map <shortSound::ID, sf::Sound> :: iterator it;
   it = soMap.find(id);
   return it->second;
}

void ResourseHandler::loadSoundsBuff()
{
    try
        {
          this->setBuff(shortSound::ID::Wall, "media/Wall.ogg");
          this->setBuff(shortSound::ID::Collide, "media/Collide.ogg");
          this->setBuff(shortSound::ID::Health_Unit, "media/Health.ogg");
          this->setBuff(shortSound::ID::Score_Unit, "media/Score.ogg");
        }

    catch (std::runtime_error& e)
        {
        std::cout << "Expection SoundBuff! " << e.what() << std::endl;
        }
}

void ResourseHandler::loadMusic()
{
    try
        {
          this->setMusic("media/Tapping.ogg");
        }

    catch (std::runtime_error& e)
        {
        std::cout << "Expection Music! " << e.what() << std::endl;
        }

}

void ResourseHandler::loadTextures()
{
    try
        {
        this->setNodeItem(textures::ID::FirstScreen, "media/First.png");
        this->setNodeItem(textures::ID::SecondScreen, "media/Second.png");
        this->setNodeItem(textures::ID::LastScreen, "media/Third.png");
        }

   catch (std::runtime_error& e)
        {
        std::cout << "Expection Texture! " << e.what() << std::endl;
        }
}




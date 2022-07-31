#ifndef JOYTEXTSOURCE_H_INCLUDED
#define JOYTEXTSOURCE_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <map>

namespace textures
{
    enum ID
        {
            FirstScreen,
            SecondScreen,
            LastScreen,
            Enum_count
        };
}

namespace shortSound
{
    enum ID
        {
            Wall,
            Collide,
            Health_Unit,
            Score_Unit,
            Enum_count
        };
}

class ResourseHandler
{
    private:
        sf::Texture nodulus [textures::ID::Enum_count];
        sf::Music music;

        std::map <shortSound::ID, sf::SoundBuffer> bMap;
        std::map <shortSound::ID, sf::Sound> soMap;

    public:
        ResourseHandler();
        ~ResourseHandler();

        void setNodeItem(textures::ID id, std::string file_Path);
        void showNodeItem(textures::ID id);
        sf::Texture& getTexture(textures::ID id);

        void setBuff(shortSound::ID id, std::string file_Path);
        sf::SoundBuffer& getBuff(shortSound::ID id);

        sf::Sound& getSound(shortSound::ID id);

        void setMusic(std::string file_Path) {music.openFromFile(file_Path);};
        void playMusic() {music.play();};
        sf::Music& getMusic() {return music;};

    public:
        void loadSoundsBuff();
        void loadMusic();
        void loadTextures();
};


#endif // JOYTEXTSOURCE_H_INCLUDED

#include "glob_SRC.h"


T_Text::T_Text()
{
    if (!font.loadFromFile("consola.ttf")) std::cout << " Error: Cant find font file! " << std::endl;

    font.loadFromFile("consola.ttf");

    text1.setFont(font);
    text2.setFont(font);
    text3.setFont(font);
    blinkInput1.setFont(font);
    blinkInput2.setFont(font);
    finalScore.setFont(font);


    text1.setCharacterSize(18);
    text2.setCharacterSize(18);
    text3.setCharacterSize(18);
    blinkInput1.setCharacterSize(45);
    blinkInput2.setCharacterSize(45);
    blinkInput1.setOutlineThickness(10);
    blinkInput2.setOutlineThickness(10);
    blinkInput1.setStyle(sf::Text::Bold);
    blinkInput2.setStyle(sf::Text::Bold);
    blinkInput1.setOutlineColor(sf::Color(255,47,70));
    blinkInput2.setOutlineColor(sf::Color(255,47,70));
    finalScore.setCharacterSize(60);
    finalScore.setStyle(sf::Text::Bold);

    text1.setColor(sf::Color::White);
    text2.setColor(sf::Color::White);
    text3.setColor(sf::Color::White);
    blinkInput1.setColor(sf::Color::Yellow);
    blinkInput2.setColor(sf::Color::Yellow);
    finalScore.setColor(sf::Color::White);

    text1.setPosition(sf::Vector2f(10.f, 10.f));
    text2.setPosition(sf::Vector2f(10.f, 30.f));
    text3.setPosition(sf::Vector2f(10.f, 50.f));
    blinkInput1.setPosition(sf::Vector2f(420, 400));
    blinkInput2.setPosition(sf::Vector2f(300, 500));
    finalScore.setPosition(sf::Vector2f(651, 670));

    text1.setString("");
    text2.setString(" Health  : ");
    text3.setString(" Score   : ");
    blinkInput1.setString("Enter - Start");
    blinkInput2.setString("Space - Redifine GamePad");

}

T_Text::~T_Text() {}

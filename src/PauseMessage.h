#pragma once
#include <SFML/Graphics.hpp>
#include "ServerPackage.h"

class PauseMessage
{
    ServerPackage serverPackage {};
    sf::Text pauseMessage;

    sf::Font font;
    sf::Text hudText;
    int currentSetting = 0;

    struct Setting
    {
        const char* name;
        float* value;
    };

    float perlinFrequency = 7.0f;
    float perlinFrequencyBase = 4.0f;
    std::vector<Setting> settings;

public:
    PauseMessage();
    void userEvent(sf::Event event);
    void setFont(const sf::Font& font);
    void setServerPackage(const ServerPackage & sp) { this->serverPackage = sp; }
    void draw(sf::RenderWindow& window);

private:
    void drawContolInfromation(sf::RenderWindow& window);
};

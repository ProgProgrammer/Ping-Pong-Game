#include "stdafx.h"
#include "PauseMessage.h"
#include <sstream>

PauseMessage::PauseMessage()
{
    sf::Text pauseMessage;
    pauseMessage.setCharacterSize(40);
    pauseMessage.setPosition(170.f, 150.f);
    pauseMessage.setFillColor(sf::Color::White);
    pauseMessage.setString("Welcome to SFML pong!\nPress space to start the game");
    
    hudText.setCharacterSize(14);
    hudText.setFillColor(sf::Color::White);
    hudText.setOutlineColor(sf::Color::Black);
    hudText.setOutlineThickness(2.0f);
    hudText.setPosition(5.0f, 5.0f);
    
    settings.push_back({ "perlinFrequency",     &perlinFrequency });
    settings.push_back({ "perlinFrequencyBase", &perlinFrequencyBase });
}

void PauseMessage::userEvent(sf::Event event)
{
    if(event.type == sf::Event::KeyPressed)
    {
        switch(event.key.code)
        {
        case sf::Keyboard::Down:
            currentSetting = (currentSetting + 1) % settings.size();
            break;
        case sf::Keyboard::Up:
            currentSetting = (currentSetting + settings.size() - 1) % settings.size();
            break;
        case sf::Keyboard::Left:
            *(settings[currentSetting].value) -= 0.1f;
            break;
        case sf::Keyboard::Right:
            *(settings[currentSetting].value) += 0.1f; break;
        default: break;
        }
    }
}

void PauseMessage::setFont(const sf::Font& font)
{
    pauseMessage.setFont(font);
    hudText.setFont(font);
}

void PauseMessage::drawContolInfromation(sf::RenderWindow& window)
{
    std::ostringstream osstr;
    osstr.str("");
    osstr
        //<< "Frame:  " << clock.restart().asMilliseconds() << "ms\n"
        << "Use the arrow keys to change the values.\nUse the return key to regenerate the terrain.\n\n";

    for(int i = 0; i < settings.size(); ++i)
    {
        osstr 
            << ((i == currentSetting) ? ">>  " : "       ") 
            << settings[i].name << ":  " << *(settings[i].value) << "\n";        
    }

    hudText.setString(osstr.str());
    window.draw(hudText);
}

void PauseMessage::draw(sf::RenderWindow& window)
{
    switch (serverPackage.gameStatus)
    {
    case GameStatus::Lose:
        pauseMessage.setString("You lost!\nPress space to restart or\nescape to exit");
        break;
    case GameStatus::Win:
        pauseMessage.setString("You won!\nPress space to restart or\nescape to exit");
        break;
    case GameStatus::Playing:
        // TODO Something wrong with architecture. do nothing
        break;
    case GameStatus::Pause:
    case GameStatus::Init:
        pauseMessage.setString("Welcome to SFML pong!\nPress space to start the game");
    }

    if(serverPackage.gameStatus != GameStatus::Playing)
    {
        window.draw(pauseMessage);
        drawContolInfromation(window);        
    }
}

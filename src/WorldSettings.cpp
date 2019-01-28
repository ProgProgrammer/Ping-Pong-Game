#include "stdafx.h"
#include "WorldSettings.h"

void WorldSettings::load()
{
    if (!settingsParser.loadFromFile("resources/settings.txt"))
    {
        throw std::logic_error("Error loading settings file!");
    }

    settingsParser.get("width", width);
    settingsParser.get("height", height);

    std::string firstPlayerStr = "User";
    settingsParser.get("FirstPlayer", firstPlayerStr);
    settingsParser.get("FirstPlayerControlKeys", firstPlayerControlKeys);
    std::string secondPlayerStr = "Bot";
    settingsParser.get("SecondPlayer", secondPlayerStr);
    settingsParser.get("SecondPlayerControlKeys", secondPlayerControlKeys);


    if (firstPlayerStr == "User")
        firstClientType = ClientType::User;
    else if (firstPlayerStr == "Bot")
        firstClientType = ClientType::Bot;
    else
        throw std::logic_error("Unknown string of FirstPlayer");

    if (secondPlayerStr == "User")
        secondClientType = ClientType::User;
    else if (secondPlayerStr == "Bot")
        secondClientType = ClientType::Bot;
    else
        throw std::logic_error("Unknown string of SecondPlayer");

    settingsParser.print();
}

void WorldSettings::save()
{
    //TODO 
    throw std::logic_error("not implemented function");
}

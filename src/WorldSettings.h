#pragma once
#include "SettingsParser.hpp"
#include "ClientFactory.h"

class WorldSettings
{
    SettingsParser settingsParser;

public:
    int width = 800;
    int height = 600;
    std::string title = "Ping Pong";
    std::string firstPlayerControlKeys = "WS";
    std::string secondPlayerControlKeys = "PL";
    ClientType firstClientType = ClientType::User;
    ClientType secondClientType = ClientType::Bot;

    void load();
    void save();
};

#pragma once
#include <SFML/Graphics.hpp>
#include "ClientFactory.h"
#include "Server.h"
#include "SettingsParser.hpp"
#include "WorldSettings.h"

class World
{
    WorldSettings worldSettings;
    sf::RenderWindow window;
    Server server;
    ClientFactory clientFactory;
    std::shared_ptr<IClient> client01;
    std::shared_ptr<IClient> client02;

public:
    World();
    int mainLoop();
};

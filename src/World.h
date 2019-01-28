#pragma once
#include <SFML/Graphics.hpp>
#include "ClientFactory.h"
#include "Server.h"
#include "PauseMessage.h"

class World
{
    const int gameWidth = 800;
    const int gameHeight = 600;
    sf::RenderWindow window;
    Server server;
    ClientFactory clientFactory;
    std::shared_ptr<IClient> client01;
    std::shared_ptr<IClient> client02;
    sf::Font font;
    PauseMessage pauseMessage;

public:
    World();
    int mainLoop();

private:
    void loadTextFont();

};

#include "stdafx.h"
#include "World.h"
#include <sstream>


World::World(): window(sf::VideoMode(gameWidth, gameHeight, 32), "SFML Pong",
                       sf::Style::Titlebar | sf::Style::Close)
                , server(gameWidth, gameHeight)
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    window.setVerticalSyncEnabled(true);
    client01 = clientFactory.createClient(ClientType::User, "WS");
    client02 = clientFactory.createClient(ClientType::Bot, "PL");
    server.setClient01(client01);
    server.setClient02(client02);
    loadTextFont();
    pauseMessage.setFont(font);
}

int World::mainLoop()
{
    while (window.isOpen())
    {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Window closed or escape key pressed: exit
            if (event.type == sf::Event::Closed ||
                event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            {
                window.close();
                break;
            }

            // Space key pressed: play
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
            {
                server.restartGame();
            }

            pauseMessage.userEvent(event);
        }

        const auto serverPackage = server.getPackage();
        client01->setServerPackage(serverPackage);
        client01->updateState();
        client02->setServerPackage(serverPackage);
        client02->updateState();        
        server.iterate();
        const auto sp = server.getPackage();
        pauseMessage.setServerPackage(sp);

        window.clear(sf::Color(50, 200, 50)); // Clear the window
        server.draw(window);
        pauseMessage.draw(window);
        window.display(); // Display things on screen
    }

    return EXIT_SUCCESS;
}

void World::loadTextFont()
{
    const std::string fontFileName = "resources/sansation.ttf";
    if (!font.loadFromFile(fontFileName))
    {
        std::stringstream ss;
        ss << "can't load font from file " << fontFileName;
        throw std::runtime_error(ss.str());
    }
}

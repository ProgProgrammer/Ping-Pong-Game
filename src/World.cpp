﻿#include "stdafx.h"
#include "World.h"

World::World()
{
    worldSettings.load();

    window.create(sf::VideoMode(worldSettings.width, worldSettings.height, 32), 
        worldSettings.title, sf::Style::Titlebar | sf::Style::Close);

    server.create(worldSettings.width, worldSettings.height);

    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    window.setVerticalSyncEnabled(true);
    client01 = clientFactory.createClient(worldSettings.firstClientType, worldSettings.firstPlayerControlKeys);
    client02 = clientFactory.createClient(worldSettings.secondClientType, worldSettings.secondPlayerControlKeys);
    server.setClient01(client01);
    server.setClient02(client02);
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
        }

        const auto serverPackage = server.getPackage();
        client01->setServerPackage(serverPackage);
        client01->updateState();
        client02->setServerPackage(serverPackage);
        client02->updateState();
        server.iterate();

        server.draw(window);

        // Display things on screen
        window.display();
    }

    return EXIT_SUCCESS;
}

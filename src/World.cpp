#include "stdafx.h"
#include "World.h"

World::World()
{
    if(!settings.loadFromFile("resources/settings.txt"))
    {
        throw std::logic_error("Error loading settings file!");
    }

    int width = 800;
    int height = 600;
    settings.get("width", width);
    settings.get("height", height);

    std::string title = "PingPong";
    settings.get("title", title);

    std::string firstPlayerStr = "User";
    settings.get("FirstPlayer", firstPlayerStr);
    std::string firstPlayerControlKeys = "WS";
    settings.get("FirstPlayerControlKeys", firstPlayerControlKeys);
    std::string secondPlayerStr = "Bot";
    settings.get("SecondPlayer", secondPlayerStr);
    std::string secondPlayerControlKeys = "PL";
    settings.get("SecondPlayerControlKeys", secondPlayerControlKeys);

    ClientType firstClientType = ClientType::User;
    ClientType secondClientType = ClientType::Bot;

    if(firstPlayerStr == "User")
        firstClientType = ClientType::User;
    else if(firstPlayerStr == "Bot")
        firstClientType = ClientType::Bot;
    else
        throw std::logic_error("Unknown string of FirstPlayer");

    if(secondPlayerStr == "User")
        secondClientType = ClientType::User;
    else if(secondPlayerStr == "Bot")
        secondClientType = ClientType::Bot;
    else
        throw std::logic_error("Unknown string of SecondPlayer");


    settings.print();

    window.create(sf::VideoMode(width, height, 32), title,
        sf::Style::Titlebar | sf::Style::Close);

    server.create(width, height);

    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    window.setVerticalSyncEnabled(true);
    client01 = clientFactory.createClient(firstClientType, firstPlayerControlKeys);
    client02 = clientFactory.createClient(secondClientType, secondPlayerControlKeys);
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

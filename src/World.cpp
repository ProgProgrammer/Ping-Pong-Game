#include "stdafx.h"
#include "World.h"
#include <sstream>

struct Setting
{
    const char* name;
    float* value;
};

// Terrain noise parameters
const int perlinOctaves = 3;

float perlinFrequency = 7.0f;
float perlinFrequencyBase = 4.0f;

// Terrain generation parameters
float heightBase = 0.0f;
float edgeFactor = 0.9f;
float edgeDropoffExponent = 1.5f;

float snowcapHeight = 0.6f;

// Terrain lighting parameters
float heightFactor = 2.0f;
float heightFlatten = 3.0f;
float lightFactor = 0.7f;


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

    // Load the text font
    const std::string fontFileName = "resources/sansation.ttf";
    if(!font.loadFromFile(fontFileName))
    {
        std::stringstream ss;
        ss << "can't load font from file " << fontFileName;
        throw std::runtime_error(ss.str());
    }

    hudText.setFont(font);
    hudText.setCharacterSize(14);
    hudText.setFillColor(sf::Color::White);
    hudText.setOutlineColor(sf::Color::Black);
    hudText.setOutlineThickness(2.0f);
    hudText.setPosition(5.0f, 5.0f);

}

int World::mainLoop()
{

    // Set up an array of pointers to our settings for arrow navigation
    Setting settings[] =
    {
        { "perlinFrequency",     &perlinFrequency },
    { "perlinFrequencyBase", &perlinFrequencyBase },
    { "heightBase",          &heightBase },
    { "edgeFactor",          &edgeFactor },
    { "edgeDropoffExponent", &edgeDropoffExponent },
    { "snowcapHeight",       &snowcapHeight },
    { "heightFactor",        &heightFactor },
    { "heightFlatten",       &heightFlatten },
    { "lightFactor",         &lightFactor }
    };

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

            // Arrow key pressed:
            if(event.type == sf::Event::KeyPressed)
            {
                switch(event.key.code)
                {
                case sf::Keyboard::Return:
                    server.restartGame();
                    break;
                case sf::Keyboard::Down:   
                    currentSetting = (currentSetting + 1) % settingCount; 
                    break;
                case sf::Keyboard::Up:     
                    currentSetting = (currentSetting + settingCount - 1) % settingCount; 
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

        const auto serverPackage = server.getPackage();
        client01->setServerPackage(serverPackage);
        client01->updateState();
        client02->setServerPackage(serverPackage);
        client02->updateState();
        
        server.iterate();
        server.draw(window);



        std::ostringstream osstr;
        // Update and draw the HUD text
        osstr.str("");
        osstr 
            //<< "Frame:  " << clock.restart().asMilliseconds() << "ms\n"
            << "Use the arrow keys to change the values.\nUse the return key to regenerate the terrain.\n\n";

        for(int i = 0; i < settingCount; ++i)
            osstr << ((i == currentSetting) ? ">>  " : "       ") << settings[i].name << ":  " << *(settings[i].value) << "\n";

        hudText.setString(osstr.str());

        window.draw(hudText);

        // Display things on screen
        window.display();
    }

    return EXIT_SUCCESS;
}

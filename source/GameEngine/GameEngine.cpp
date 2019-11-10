#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include "GameEngine.h"


//
//
[[nodiscard]]
bool isOneType(Rune* first, Rune* second)
{
    if ( first->getType() == second->getType() )
    {
        return true;
    }

    return false;
}


//
//
void GameEngine::run()
{
    sf::Cursor cursor;

    sf::Texture image;
    image.loadFromFile("resources/Oxygen.rgba");

    cursor.loadFromPixels(image.copyToImage().getPixelsPtr(), sf::Vector2u(32, 32), sf::Vector2u(0, 0));

    window->setMouseCursor(cursor);

    Rune* first = nullptr, *second = nullptr;

    window->setFramerateLimit(60);
    while ( window->isOpen() )
    {
        sf::Event event;
        while ( window->pollEvent(event) )
        {
            if ( event.type == sf::Event::Closed )
            {
                window->close();
            }/*
            if ( event.type == sf::Event::MouseButtonPressed )
            {
                //  press button and get the Rune and highlight it
                //  if pressed second time on the same rune - unhighlight it
                //  if pressed on the second rune and the type of 1-st and 2-nd rune is equal - delete them and unhighlight
                //  else unhighlight them.
                //
                int x = sf::Mouse::getPosition().x;
                int y = sf::Mouse::getPosition().y;

                if ( first == nullptr )
                {
                    first = geometry.getRune(x, y);
                    if ( first != nullptr )
                    {
                        std::cout << first->getID();
                        first->highlight();
                    }
                }
                else
                {
                    second = geometry.getRune(x, y);
                    if ( second == nullptr )
                    {
                        break;
                    }
                    if ( first == second )
                    {
                        first->unhighlight();
                        first = second = nullptr;
                    }

                    if ( second == nullptr )
                    {
                        break;
                    }

                    first->unhighlight();
                    second->unhighlight();

                    if ( first->getType() == second->getType() )
                    geometry.deleteRunes(first, second);
                    first = nullptr;
                    second = nullptr;
                }
            }*/

        }
        user->update(stage, &geometry);

        if ( user->levelChoice() != tempLevel )
        {
            tempLevel = user->levelChoice();
            backgroundManager->changeBackground(static_cast<Enums::Background::Background>(static_cast<int>(tempLevel)));
            user->clear();
            geometry.clear();
            if(stage != Enums::Stage::MENU)
            geometry.loadLevel(static_cast<int>(tempLevel));
        }


        window->clear();

        backgroundManager->draw(window);

        if(stage == Enums::Stage::GAME)
        geometry.draw(window, stage, backgroundManager);
        window->display();
    }

    return;
}


//
//
GameEngine::GameEngine():
stage(Enums::Stage::MENU)
{
    user = new User();
    initializeWindow();

    tempLevel = user->levelChoice();
    backgroundManager = new BackgroundManager();

    backgroundManager->changeBackground(Enums::Background::Background::MENU);
    geometry.loadLevel(2);
}


//
//
void GameEngine::initializeWindow()
{

    sf::Image icon;
    icon.loadFromFile("resources/Textures/Runes/0.png");

    window = new sf::RenderWindow(sf::VideoMode(1920, 1080), title, sf::Style::Fullscreen);

    window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    return;
}
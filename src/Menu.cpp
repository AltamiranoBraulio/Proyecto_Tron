#pragma once
#include <iostream>
#include "Menu.hpp"

// constructor
Menu::Menu(float width, float height)
{
    this->height = height;
    this->width = width;
    selectedItemIndex = 0;
    setProperties();
}

// draw menu and instruction
void Menu::draw(RenderWindow &window)
{
    for (const auto &i : menu)
        window.draw(i);
    window.draw(instruction);
}

// move left in menu options
void Menu::moveLeft()
{
    if (selectedItemIndex - 1 >= 0)
    {
        menu[selectedItemIndex].setFillColor(Color::White);
        selectedItemIndex--;
        menu[selectedItemIndex].setFillColor(Color::Cyan);
    }
}

// move right in menu options
void Menu::moveRight()
{
    if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
    {
        menu[selectedItemIndex].setFillColor(Color::White);
        selectedItemIndex++;
        menu[selectedItemIndex].setFillColor(Color(255, 90, 0));
    }
}

// run and show menu window, returns mode used in running game engine
int Menu::startMenu() const
{

    RenderWindow window(VideoMode((unsigned int)width, (unsigned int)
                                                           height),
                        "TronGame");

    Menu menu_opt(window.getSize().x, window.getSize().y);

    Image image;
    image.loadFromFile("resources/menu_background.jpg");

    Texture texture;
    texture.loadFromImage(image);

    Sprite background;
    background.setTexture(texture);

    auto size = background.getTexture()->getSize();
    background.setScale(float(window.getSize().x) / size.x, float(window.getSize().y) / size.y);

    while (window.isOpen())
    {
        Event event{};

        while (window.pollEvent(event))
        {
            if (Keyboard::isKeyPressed(Keyboard::Left))
            {
                menu_opt.moveLeft();
                break;
            }
            if (Keyboard::isKeyPressed(Keyboard::Right))
            {
                menu_opt.moveRight();
                break;
            }
            if (Keyboard::isKeyPressed(Keyboard::Return))
            {
                return menu_opt.getPressedItem();
            }

            if (event.type == Event::Closed)
            {
                window.close();
            }
        }

        window.clear();
        window.draw(background);
        menu_opt.draw(window);

        window.display();
    }
    return -1;
}

// setting text properties for menu
void Menu::setProperties()
{

    // load font
    if (!font.loadFromFile("fonts/centaur.ttf"))
    {
        std::cout << "Cannot load font";
    }

    // for mode 0
    menu[0].setFont(font);
    menu[0].setCharacterSize(40);
    menu[0].setFillColor(sf::Color::Cyan);
    menu[0].setString("COVERED-MODE");
    menu[0].setPosition(width / 5 - 80, height - height / 5);

    // for mode 1
    menu[1].setFont(font);
    menu[1].setCharacterSize(40);
    menu[1].setFillColor(sf::Color::White);
    menu[1].setString("CLASSIC-MODE");
    menu[1].setPosition(width - width / 5 - 200, height - height / 5);

    // for control instruction
    instruction.setFont(font);
    instruction.setCharacterSize(20);
    instruction.setFillColor(sf::Color::White);
    instruction.setString("CONTROLS: WASD KEYS and ARROW KEYS");
    instruction.setPosition(width / 2 - 200, height - 30);
}

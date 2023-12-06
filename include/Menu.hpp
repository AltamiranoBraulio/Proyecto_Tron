#pragma once
#ifndef TRONGAME_MENU_H
#define TRONGAME_MENU_H

#define MAX_NUMBER_OF_ITEMS 2

#include "SFML/Graphics.hpp"

using namespace sf;

class Menu
{
private:
    int selectedItemIndex;
    Font font;
    Text menu[MAX_NUMBER_OF_ITEMS];
    Text instruction;

public:
    float width;
    float height;

    Menu(float width, float height);

    void draw(RenderWindow &window);

    void moveLeft();

    void moveRight();

    int getPressedItem() const { return selectedItemIndex; }

    int startMenu() const;

    void setProperties();
};

#endif // TRONGAME_MENU_H

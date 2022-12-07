#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "button.h"

using namespace std;
using namespace sf;

class TopMenu
{
public:
    void loadVector()
    {
        for (int i = 0; i < 6; i++)
        {
            TopButton* btn = new TopButton(names[i], { i * 100, 0 });
            topMenuButtons.push_back(btn);
        }
        
    }
    void drawTo(RenderWindow &window)
    {
        for (int i = 0; i < 6; i++)
        {
            topMenuButtons[i]->drawTo(window);
        }
    }
    void setFont(Font& font)
    {
        for (int i = 0; i < 6; i++)
        {
            topMenuButtons[i]->setFont(font);
        }
    }
    TopButton getButton(int index)
    {
        return *topMenuButtons[index];
    }
    void setButtonColor(int index, Color color)
    {
        topMenuButtons[index]->setBackColor(color);
    }

private:
    string names[6] = { "New", "Open", "Rename", "Copy", "Paste", "Delete" };
    vector<TopButton*> topMenuButtons;    
};
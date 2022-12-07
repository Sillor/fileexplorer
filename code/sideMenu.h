#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "button.h"
using namespace std;
using namespace sf;

class SideMenu
{
public:
    SideMenu()
    {
        for (int i = 0; i < 7; i++)
        {
            SideButton* btn = new SideButton(names[i], { 0, i * 60 + 40 });
            sideMenuButtons.push_back(btn);
        }
        backgroundStrip.setSize({ 300, 2160 });
        backgroundStrip.setPosition({ 0, 0 });
        backgroundStrip.setFillColor(Color{ 0x2a2f3aff });
    }
    void drawTo(RenderWindow &window)
    {
        window.draw(backgroundStrip);
        for (int i = 0; i < 7; i++)
        {
            sideMenuButtons[i]->drawTo(window);
        }
    }
    void setFont(Font& font)
    {
        for (int i = 0; i < 7; i++)
        {
            sideMenuButtons[i]->setFont(font);
        }
    }
    SideButton getButton(int index)
    {
        return *sideMenuButtons[index];
    }
    void setButtonColor(int index, Color color)
    {
        sideMenuButtons[index]->setBackColor(color);
    }

private:
    string names[7] = { "Home", "Desktop", "Documents", "Downloads", "Music", "Pictures", "Videos" };
    vector<SideButton*> sideMenuButtons;   
    RectangleShape backgroundStrip;
};
#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "button.h"
using namespace std;
using namespace sf;

class TopMenu
{
public:
    TopMenu()
    {
        for (int i = 0; i < 6; i++)
        {
            TopButton* btn = new TopButton(names[i], { i * 100, 0 });
            topMenuButtons.push_back(btn);
        }
        backgroundStrip.setSize({ 3840, 40 });
        backgroundStrip.setPosition({ 0, 0 });
        backgroundStrip.setFillColor(Color{ 0x2a2f3aff });
    }
    void drawTo(RenderWindow &window)
    {
        window.draw(backgroundStrip);
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
    void buttonClick(RenderWindow &window)
    {
        for (int i = 0; i < 6; i++)
        {
            if (TopMenu::getButton(i).isMouseOver(window))
            {
                cout << "topButton " << i << " pressed" << endl;
                TopMenu::setButtonColor(i, Color{ 0x142238FF });
            }
        }
    }
    void mouseHover(RenderWindow &window)
    {
        for (int i = 0; i < 6; i++)
        {
            if (TopMenu::getButton(i).isMouseOver(window))
            {
                TopMenu::setButtonColor(i, Color{ 0x252933FF });
            }
            else
            {
                TopMenu::setButtonColor(i, Color{ 0x2A2f3AFF });
            }
        }
    }

private:
    string names[6] = { "New", "Open", "Rename", "Copy", "Paste", "Delete" };
    vector<TopButton*> topMenuButtons;   
    RectangleShape backgroundStrip;
};
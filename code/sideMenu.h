#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "button.h"
#include "fun.h"
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
    string getButtonName(int index)
    {
        return names[index];
    }
    void buttonClick(RenderWindow &window, Directory &currentDisplayingDirectory, string USERNAME)
    { 
        for (int i = 0; i < 7; i++)
        {
            if (SideMenu::getButton(i).isMouseOver(window))
            {
                cout << "sideButton " << i << " pressed" << endl;
                SideMenu::setButtonColor(i, Color{ 0x142238FF });
            }
        }

        for (int i = 1; i < 7; i++)
        {
            if (SideMenu::getButton(i).isMouseOver(window))
            {
                currentDisplayingDirectory.setPath("/home/" + USERNAME + "/" + SideMenu::getButtonName(i));
                currentDisplayingDirectory.populate();
            }
        }

        if (SideMenu::getButton(0).isMouseOver(window))
        {
            currentDisplayingDirectory.setPath("/home/" + USERNAME);
            currentDisplayingDirectory.populate();
        }
    }

private:
    string names[7] = { "Home", "Desktop", "Documents", "Downloads", "Music", "Pictures", "Videos" };
    string paths[7] = { "/home", "/home/Desktop", "/home/Documents", "/home/Downloads", "/home/Music", "/home/Pictures", "/home/Videos"};
    vector<SideButton*> sideMenuButtons;   
    RectangleShape backgroundStrip;
};
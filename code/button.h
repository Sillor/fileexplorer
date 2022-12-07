#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Button
{
public:
    Button() {    };
    Button(string t, Vector2f size, int charSize, Color bgColor, Color textColor)
    {
        text.setString(t);
        text.setColor(textColor);
        text.setCharacterSize(charSize);

        button.setSize(size);
        button.setFillColor(bgColor);
    }

    void setFont(Font& font)
    {
        text.setFont(font);
    }

    void setBackColor(Color color)
    {
        button.setFillColor(color);
    }

    void setTextColor(Color color)
    {
        text.setColor(color);
    }

    void setPosition(Vector2f pos)
    {
        button.setPosition(pos);

        float xPos = (pos.x + button.getGlobalBounds().width/3.f) -
                  (text.getGlobalBounds().width/2);
        float yPos = (pos.y + button.getGlobalBounds().height/3.f) -
                  (text.getGlobalBounds().height/2);
        text.setPosition({ xPos, yPos });
    }

    void drawTo(RenderWindow &window)
    {
        window.draw(button);
        window.draw(text);
    }

    bool isMouseOver(RenderWindow &window)
    {
        float mouseX = Mouse::getPosition(window).x;
        float mouseY = Mouse::getPosition(window).y;

        float btnPosX = button.getPosition().x;
        float btnPosY = button.getPosition().y;

        float btnxPosWidth = button.getPosition().x + button.getLocalBounds().width;
        float btnyPosHeight = button.getPosition().y + button.getLocalBounds().height;

        if(mouseX < btnxPosWidth && mouseX > btnPosX && mouseY < btnyPosHeight && mouseY > btnPosY)
        {
            return true;
        }
        return false;
    }

protected:
    RectangleShape button;
    Text text;
};


class TopButton : public Button
{
public:
    TopButton(string t, Vector2f pos) : Button()
    {
        text.setString(t);
        text.setColor(Color{ 0x98abb2ff });
        text.setCharacterSize(16);

        button.setSize({ 100, 40 });
        button.setFillColor(Color{ 0x2a2f3aff });

        setPosition(pos);
    }
};
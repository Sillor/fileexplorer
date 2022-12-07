#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>
#include <vector>
#include <fstream>
#include <unistd.h>  
#include "fun.h"
#include "topMenu.h"
#include "sideMenu.h"
using namespace sf;
using namespace std;


const string USERNAME = "admin";

int main()
{
	cout << endl << endl << "------------------" << endl << endl;

	Font lightFont;
	lightFont.loadFromFile("fonts/Ubuntu-Light.ttf"); // light font for buttons
	Font regularFont;
	regularFont.loadFromFile("fonts/Ubuntu-Regular.ttf"); // regular font for buttons
	TopMenu topMenu;
	topMenu.setFont(regularFont);
	SideMenu sideMenu;
	sideMenu.setFont(regularFont);

	filesystem::path currentDir = "/home/" + USERNAME + "/Desktop";	// Set this directory to be something on your computer		
	Directory currentDisplayingDirectory(currentDir);

	currentDisplayingDirectory.populate();
	currentDisplayingDirectory.printContents();

	// SFML set-up
	// --------------------------------------------------------------------
	Vector2i defaultWindowSize(3840, 2160);
	VideoMode vm(defaultWindowSize.x, defaultWindowSize.y);
	RenderWindow window(vm, "File Explorer", Style::Resize);
	Event event;
	Vector2u currentWindowSize(window.getSize());
	View mainView(FloatRect(0.0, 0.0, 1920,1080));
	window.setView(mainView);
	
	RectangleShape background(static_cast<Vector2f>(defaultWindowSize));
	background.setPosition(Vector2f(0.0, 0.0));
	// --------------------------------------------------------------------

	// MAIN LOOP
	// ##########################################################################################
	bool wait = false;
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				window.close();
			}

			if (event.type == Event::MouseButtonPressed) //if mouse pressed change color of button
			{
				topMenu.buttonClick(window);				
				sideMenu.buttonClick(window, currentDisplayingDirectory, USERNAME);
			}

			if (event.type == Event::MouseMoved) //if mouse moved over button change color of the button
			{
				topMenu.mouseHover(window);
				sideMenu.mouseHover(window);
			}

			// Rowans part
			/*
			if (event.type == Event::MouseButtonPressed)
			{

				for (auto element : currentDisplayingDirectory.getCoordinates())
				{
						//cout << "blah" << endl;
						Vector2i mousePos = Mouse::getPosition(window);
						cout << "mouse " << mousePos.x << "\t" << mousePos.y << endl; 
						cout << "topRight " << element.topRight.x << endl;
						cout << "bottomLeft " << element.bottomLeft.x << endl;
						cout << endl << endl;

						//if (mousePos.x > element.bottomLeft.x && mousePos.y bottomLeft.y)
						if ( mousePos.x <= element.topRight.x && mousePos.x >= element.topLeft.x && mousePos.y <= element.topRight.y && mousePos.y >= element.bottomLeft.y)
						{
							cout << "folder click << endl";
						}
				}
			}
			*/

		}
		

		if (wait == false || window.getSize() != currentWindowSize)
		{
			
			window.clear();
			//window.draw(background);			
			currentDisplayingDirectory.displayContents(window, background, mainView);
			sideMenu.drawTo(window); //draw side menu
			topMenu.drawTo(window); //draw top menu

			//CircleShape shape(50);
			//shape.setFillColor(sf::Color(100, 250, 50));
			//window.draw(shape);

			window.display();
			wait = true;
			//testDir.cleanTexture();
		}
		usleep(50000);
		
	}
	
	// ##########################################################################################

	return 0;
}


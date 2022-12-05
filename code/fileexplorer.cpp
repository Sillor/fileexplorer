#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>
#include <vector>
#include <fstream>
#include <unistd.h>  
#include "fun.h"

using namespace sf;
using namespace std;



int main()
{
	cout << endl << endl << "------------------" << endl << endl;


	filesystem::path currentDir = "/home/r/Desktop/testDir";	// Set this directory to be something on your computer		
	Directory testDir(currentDir);

	testDir.populate();
	testDir.printContents();

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
		}
		

		if (wait == false || window.getSize() != currentWindowSize)
		{
			window.clear();
			//window.draw(background);
			testDir.displayContents(window, background, mainView);

			//CircleShape shape(50);
			//shape.setFillColor(sf::Color(100, 250, 50));
			//window.draw(shape);

			window.display();
			wait = true;
		}
		usleep(50000);
	}
	
	// ##########################################################################################

	return 0;
}


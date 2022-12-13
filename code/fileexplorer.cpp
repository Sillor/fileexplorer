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

void setUp(Font& lightFont, Font& regularFont, TopMenu& topMenu, SideMenu& sideMenu, filesystem::path& currentDir, RenderWindow& window, View& mainView, RectangleShape& background)
{
	lightFont.loadFromFile("fonts/Ubuntu-Light.ttf"); // light font for buttons
	regularFont.loadFromFile("fonts/Ubuntu-Regular.ttf"); // light font for buttons
	topMenu.setFont(regularFont);
	sideMenu.setFont(regularFont);
	window.setView(mainView);
	background.setPosition(Vector2f(0.0, 0.0));
}

int main() {
	Font lightFont, regularFont;
	TopMenu topMenu;
	SideMenu sideMenu;
	filesystem::path currentDir = "/home/" + USERNAME + "/Desktop"; // Set this directory to be something on your computer
	Directory currentDisplayingDirectory(currentDir);
	Vector2i defaultWindowSize(3840, 2160 /*1920, 1080*/);
	VideoMode vm(defaultWindowSize.x, defaultWindowSize.y);
	RenderWindow window(vm, "File Explorer", Style::Resize);
	Event event;
	Vector2u currentWindowSize(window.getSize());
	View mainView(FloatRect(0.0, 0.0, 1920, 1080));
	RectangleShape background(static_cast<Vector2f>(defaultWindowSize));
	setUp(lightFont, regularFont, topMenu, sideMenu, currentDir, window, mainView, background);

	currentDisplayingDirectory.populate();
	currentDisplayingDirectory.printContents();

	bool wait = false;
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (Keyboard::isKeyPressed(Keyboard::Escape)){ window.close(); }
			if (event.type == Event::MouseButtonPressed) {  						/* if mouse pressed change color of button*/
				topMenu.buttonClick(window);
				sideMenu.buttonClick(window, currentDisplayingDirectory, USERNAME);
			}

			if (event.type == Event::MouseMoved) { /* if mouse moved over button change color of the button*/
				topMenu.mouseHover(window);
				sideMenu.mouseHover(window);
			}

			if (Keyboard::isKeyPressed(Keyboard::Return)) {
				currentDisplayingDirectory.setPath(returnParentDirStr(currentDisplayingDirectory.getPath()));
				currentDisplayingDirectory.populate();
			}

			if (event.type == Event::MouseButtonPressed) {
				int counter = 0;
				for (auto element : currentDisplayingDirectory.getCoordinates()) {
					Vector2i mousePos = Mouse::getPosition(window);

					if (mousePos.x <= element.topRight.x && mousePos.x >= element.topLeft.x && mousePos.y >= element.topRight.y && mousePos.y <= element.bottomLeft.y) {
						try {cout << currentDisplayingDirectory.getContents().at(counter)->getInfo().location << endl;} catch(out_of_range& ex){cout << "ERROR 10" << endl;}

						if (filesystem::is_directory(currentDisplayingDirectory.getContents().at(counter)->getPath())) {
							Directory tempDir(currentDisplayingDirectory.getContents().at(counter)->getPath());
							currentDisplayingDirectory = tempDir;
							currentDisplayingDirectory.populate();
							break;
							try { cout << currentDisplayingDirectory.getContents().at(counter)->getPath() << endl; } catch(out_of_range& exception) {cout << "ERROR 11" << endl;}
						}
						else { currentDisplayingDirectory.getContents().at(counter)->openItem(); }
					}
					counter++;
				}
			}
		}

		if (wait == false || window.getSize() != currentWindowSize) {
			window.clear();
			currentDisplayingDirectory.displayContents(window, background, mainView);
			sideMenu.drawTo(window); // draw side menu
			topMenu.drawTo(window);	 // draw top menu
			window.display();
			wait = true;
		}
		usleep(50000);
	}
	return 0;
}

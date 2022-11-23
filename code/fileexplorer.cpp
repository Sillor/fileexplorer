#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

int main()
{
	VideoMode vm(1500, 400);

	RenderWindow window(vm, "File Explorer", Style::Close);

	while (window.isOpen())
	{
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		window.clear();
		window.display();
	}

	return 0;
}



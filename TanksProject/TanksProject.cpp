#include <SFML/Graphics.hpp>
#include<iostream>
#define ToF(a) static_cast<float>(a)

bool mouseclickbutton(sf::Vector2i MousePos, sf::RectangleShape button)
{
	sf::Vector2f buttonsize(button.getSize().x, button.getSize().y);
	sf::Vector2f buttonposi(button.getPosition().x, button.getPosition().y);

	if (ToF(MousePos.x) >= (buttonposi.x - buttonsize.x / 2) && ToF(MousePos.x) <= (buttonposi.x + buttonsize.x / 2))
		if (ToF(MousePos.y) <= (buttonposi.y + buttonsize.y / 2) && ToF(MousePos.y) >= (buttonposi.y - buttonsize.y / 2))
			return true;
	return false;
}

int main()
{
	sf::RenderWindow MainMenu(sf::VideoMode(800, 600), "Tanks Menu", sf::Style::Close);
	//sf::RenderWindow GameWindow(sf::VideoMode(800, 600), "Tanks", sf::Style::Close);

	sf::Vector2f baserectangle = sf::Vector2f(100.0f, 50.0f);
	sf::Vector2f largerRectangle = sf::Vector2f(200.0f, 100.0f);
	sf::RectangleShape ExitButton(baserectangle), SingleplayerButton(largerRectangle);
	ExitButton.setOrigin(baserectangle.x / 2, baserectangle.y / 2); SingleplayerButton.setOrigin(largerRectangle.x / 2, largerRectangle.y / 2);

	ExitButton.setPosition(400.0f, 500.0f);
	SingleplayerButton.setPosition(400.0f, 400.0f);
//	Exit.setOrigin(sf::Vector2f(50.0f, 50.0f));

	sf::Texture ExitButtonText, SingpleButtonText;
	ExitButtonText.loadFromFile("Textures/MenuText.png");
	SingpleButtonText.loadFromFile("Textures/SingleplayerText.png");

	ExitButton.setTexture(&ExitButtonText);
	SingleplayerButton.setTexture(&SingpleButtonText);

	while (MainMenu.isOpen()) {
		sf::Event evnt;
		while (MainMenu.pollEvent(evnt))
		{
			
			switch (evnt.type)
			{
			case evnt.Closed:
				MainMenu.close();
			}
		}
		
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
			sf::Vector2i mousepos = sf::Mouse::getPosition(MainMenu);
			if (mouseclickbutton(mousepos, ExitButton) == true)
				MainMenu.close();
		}
		
		MainMenu.draw(ExitButton);
		MainMenu.draw(SingleplayerButton);
		MainMenu.display();
		MainMenu.clear(sf::Color(132, 137, 201));
	}
	return 0;
}
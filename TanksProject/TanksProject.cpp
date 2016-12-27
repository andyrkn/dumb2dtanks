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
	sf::RenderWindow MainMenu(sf::VideoMode(1000, 600), "Tanks Menu", sf::Style::Close);
	sf::RenderWindow GameWindow(sf::VideoMode(800, 600), "Tanks", sf::Style::Close);
	GameWindow.setVisible(false);

	sf::Vector2f baserectangle = sf::Vector2f(100.0f, 50.0f);
	sf::Vector2f largerRectangle = sf::Vector2f(200.0f, 100.0f);
	sf::Vector2f tankVector = sf::Vector2f(20.0f, 20.0f);
	sf::RectangleShape ExitButton(baserectangle), SingleplayerButton(largerRectangle);
	

	sf::RectangleShape Player1(tankVector);
	Player1.setFillColor(sf::Color(27, 68, 135));
	Player1.setOrigin(Player1.getSize().x, Player1.getSize().y);


	ExitButton.setOrigin(baserectangle.x / 2, baserectangle.y / 2); SingleplayerButton.setOrigin(largerRectangle.x / 2, largerRectangle.y / 2);

	ExitButton.setPosition(MainMenu.getSize().x/2, 500.0f);
	SingleplayerButton.setPosition(MainMenu.getSize().x / 2, 400.0f);

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
			if (mouseclickbutton(mousepos, SingleplayerButton) == true)
			{
				GameWindow.setVisible(true);
				MainMenu.setVisible(false);
				Player1.setPosition(100.0f, 100.0f);
				while (GameWindow.isOpen())
				{

					sf::Event evnt1;
					while (GameWindow.pollEvent(evnt1))
					{
						if (evnt1.type == evnt1.Closed)
							GameWindow.close();
					}

					

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
					{
						Player1.move(-0.1f, 0.0f);
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
					{
						Player1.move(0.0f, 0.1f);
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
					{
						Player1.move(0.1f, 0.0f);
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
					{
						Player1.move(0.0f, -0.1f);
					}

					GameWindow.draw(Player1);
					GameWindow.display();
					GameWindow.clear(sf::Color(230, 230, 230));
				}
				MainMenu.setVisible(true);
			}

		}


		
		MainMenu.draw(ExitButton);
		MainMenu.draw(SingleplayerButton);
		MainMenu.display();
		MainMenu.clear(sf::Color(132, 137, 201));
	}
	return 0;
}
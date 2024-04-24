// Author : Martin Kozel

#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 

#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h> 

int selectedTileType = 1; // Default tile type (1 for red)
sf::Color selectedTileColor = sf::Color::Red; // Default tile color

enum class GameState
{
	Menu,
	Gameplay,
	Editor
};

struct Button
{
	sf::Text text;
	sf::RectangleShape rectangle;
};

class Game
{
public:
	//create Window
	sf::RenderWindow window;
	sf::View view;
	float randomNum;

	sf::Font font;

	sf::RectangleShape playerShape;

	Button buttons[3];
	Button backButton;

	sf::CircleShape cursor;

	GameState m_currentGamestate = GameState::Menu;

	float velocityX = 0, velocityY = 0, gravity = 0.3;

	static const int numRows = 20;
	static const int numCols = 45;
	int levelData[numRows][numCols] =
	{
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};

	sf::RectangleShape level[numRows][numCols];

	Game()
	{
		window.create(sf::VideoMode(800, 600), "Level Editor");
	}

	void init()
	{
		if (!font.loadFromFile("ASSETS/FONTS/ariblk.ttf"))
		{
			std::cout << "Error loading font." << std::endl;
		}

		//Menu Buttons
		for (int i = 0; i < 3; i++)
		{
			//Rectangle
			buttons[i].rectangle.setSize(sf::Vector2f(200.0f, 50.0f));
			buttons[i].rectangle.setOrigin(100.0f, 25.0f);
			buttons[i].rectangle.setFillColor(sf::Color::White);

			buttons[i].rectangle.setPosition(400.0f, 150.0f + 150.0f * i);

			//Text
			buttons[i].text.setFont(font);
			buttons[i].text.setCharacterSize(24.0f);
			buttons[i].text.setFillColor(sf::Color::White);
			buttons[i].text.setOutlineThickness(2.0f);
			buttons[i].text.setOutlineColor(sf::Color::Black);

			if (i == 0)
			{
				buttons[i].text.setString("Start");
			}
			else if (i == 1)
			{
				buttons[i].text.setString("Edit");
			}
			else if (i == 2)
			{
				buttons[i].text.setString("Quit");
			}

			buttons[i].text.setOrigin(buttons[i].text.getGlobalBounds().width / 2.0f, buttons[i].text.getGlobalBounds().height / 2.0f);
			buttons[i].text.setPosition(400.0f, 150.0f + 150.0f * i);
		}

		cursor.setRadius(2.0f);
		cursor.setOrigin(2.0f, 2.0f);
		cursor.setFillColor(sf::Color::Red);
		cursor.setPosition(100.0f, 100.0f);

		view = window.getDefaultView();
		playerShape.setSize(sf::Vector2f(20, 20));
		playerShape.setPosition(160, 500);

		for (int row = 0; row < numRows; row++)
		{
			for (int col = 0; col < numCols; col++)
			{
				level[row][col].setSize(sf::Vector2f(70, 30));
				level[row][col].setPosition(col * 70, row * 30);
				level[row][col].setOutlineThickness(2.0f);
				level[row][col].setOutlineColor(sf::Color::Transparent);

				if (levelData[row][col] == 1)
				{
					level[row][col].setFillColor(sf::Color::Red);
				}
				if (levelData[row][col] == 0)
				{
					level[row][col].setFillColor(sf::Color::Black);
				}
				if (levelData[row][col] == 2)
				{
					level[row][col].setFillColor(sf::Color::Blue);
				}
			}
		}

	}

	void run()
	{
		sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
		sf::Time timeSinceLastUpdate = sf::Time::Zero;
		sf::Clock clock;
		clock.restart();

		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			timeSinceLastUpdate += clock.restart();

			if (timeSinceLastUpdate > timePerFrame)
			{
				switch (m_currentGamestate)
				{
				case GameState::Menu:
					updateMenu();
					renderMenu();
					break;
				case GameState::Gameplay:
					updateGameplay();
					renderGameplay();
					break;
				case GameState::Editor:
					updateEditor();
					renderEditor();
					break;
				default:
					break;
				}

				timeSinceLastUpdate = sf::Time::Zero;
			}
		}
	}

	void updateGameplay()
	{
		for (int row = 0; row < numRows; row++)
		{
			for (int col = 0; col < numCols; col++)
			{
				level[row][col].move(-3.7, 0);
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && velocityY == 0)
		{
			velocityY = -11.8;
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			m_currentGamestate = GameState::Menu; // Go back to the menu
		}

		velocityY = velocityY + gravity;
		playerShape.move(0, velocityY);

		gravity = 0.6;

		for (int row = 0; row < numRows; row++)
		{
			for (int col = 0; col < numCols; col++)
			{
				if (velocityY >= 0)
				{
					if (levelData[row][col] == 1)
					{

						if (playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
						{
							if (playerShape.getPosition().y < level[row][col].getPosition().y)
							{
								gravity = 0;
								velocityY = 0;
								playerShape.setPosition(playerShape.getPosition().x, level[row][col].getPosition().y);
								playerShape.move(0, -playerShape.getGlobalBounds().height);
								break;
							}
							else {
								init();
							}
						}
					}
				}

				if (velocityY < 0)
				{
					if (levelData[row][col] == 1)
					{
						if (playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
						{
							init();
						}
					}
				}

				if (levelData[row][col] == 2)
				{
					if (playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
					{
						init();
					}
				}
			}
		}

		if (playerShape.getPosition().y > 600)
		{
			init();
		}
	}

	void renderGameplay()
	{
		window.clear();

		for (int row = 0; row < numRows; row++)
		{
			for (int col = 0; col < numCols; col++)
			{
				level[row][col].setOutlineColor(sf::Color::Transparent);
				window.draw(level[row][col]);
			}
		}
		window.draw(playerShape);

		window.display();
	}

	void updateMenu()
	{
		cursor.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));

		for (size_t i = 0; i < 3; i++)
		{
			if (cursor.getGlobalBounds().intersects(buttons[i].rectangle.getGlobalBounds()))
			{

				// Check if left mouse button is pressed
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					// Perform action based on button clicked
					if (i == 0) {
						// Start the game
						m_currentGamestate = GameState::Gameplay;
					}
					else if (i == 1) {
						// Switch to editor mode
						m_currentGamestate = GameState::Editor;
					}
					else if (i == 2) {
						// Exit the game
						window.close();
					}
				}
			}
			else
			{
				buttons[i].rectangle.setScale(1.0f, 1.0f);
				buttons[i].text.setScale(1.0f, 1.0f);
			}
		}
	}

	void renderMenu()
	{
		window.clear();

		for (auto& button : buttons)
		{
			window.draw(button.rectangle);
			window.draw(button.text);
		}

		window.draw(cursor);

		window.display();
	}

	void updateEditor()
	{
		// Handle tile placement
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			// Get the mouse position in the window
			sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

			// Adjust for the view's position
			mousePosition.x += static_cast<int>(view.getCenter().x - window.getSize().x / 2);
			mousePosition.y += static_cast<int>(view.getCenter().y - window.getSize().y / 2);

			int col = mousePosition.x / 70;
			int row = mousePosition.y / 30;

			// Place the selected tile at the mouse position
			if (row >= 0 && row < numRows && col >= 0 && col < numCols) {
				levelData[row][col] = selectedTileType;
				level[row][col].setFillColor(selectedTileColor);
			}
		}
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
			// Get the mouse position in the window
			sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

			// Adjust for the view's position
			mousePosition.x += static_cast<int>(view.getCenter().x - window.getSize().x / 2);
			mousePosition.y += static_cast<int>(view.getCenter().y - window.getSize().y / 2);

			int col = mousePosition.x / 70;
			int row = mousePosition.y / 30;

			// Remove the tile at the mouse position
			if (row >= 0 && row < numRows && col >= 0 && col < numCols) {
				levelData[row][col] = 0; // Set tile type to 0 (black)
				level[row][col].setFillColor(sf::Color::Black); // Set tile color to black
			}
		}

		// Handle horizontal movement with arrow keys
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			view.move(-10.0f, 0.0f);
			window.setView(view);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			view.move(10.0f, 0.0f);
			window.setView(view);
		}

		// Handle going back to the menu
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			m_currentGamestate = GameState::Menu; // Go back to the menu
		}
	}






	void renderEditor()
	{
		window.clear();

		for (int row = 0; row < numRows; row++)
		{
			for (int col = 0; col < numCols; col++)
			{
				level[row][col].setOutlineColor(sf::Color::White);
				window.draw(level[row][col]);
			}
		}


		window.display();
	}
};

int main()
{
	Game game;

	game.init();

	game.run();

	return 0;
}